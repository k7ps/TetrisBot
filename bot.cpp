#include "bot.h"
#include "point.h"
#include "settings.h"

#include <omp.h>

#include <limits.h>
#include <vector>


namespace {

    int Score(const Field& field) {
        int score = 0;
        for (int y = 0; y < field.GetFirstEmptyRow(); y++) {
            for (int x = 0; x < field.GetSize().x; x++) {
                if (field[y][x]) {
                    score += y + 1;
                } else if (y + 1 < field.GetSize().y && field[y + 1][x]) {
                    score += (y + 2) * field.GetSize().x;
                }
            }
        }
        return score;
    }

    std::vector<PiecePosition> GetAllPiecePositions(const Field& field, PieceType type) {
        std::vector<PiecePosition> allPiecePositions;

        for (unsigned int rot = 0; rot < GetRotationCount(type); rot++) {
            int n = field.GetSize().x - GetPieceWidth(type, rot) + 1;
            int m = std::min(field.GetSize().y - GetPieceHeight(type, rot), field.GetFirstEmptyRow()) + 1;
            for (int x = 0; x < n; x++) {
                for (int y = m - 1; y >= 0; y--) {
                    PiecePosition currPiecePosition{Point(x, y), type, rot};
                    if (field.CanPut(currPiecePosition)) {
                        allPiecePositions.push_back(currPiecePosition);
                        break;
                    }
                }
            }
        }
        return allPiecePositions;
    }

    void GetBestScore(Field& field, std::deque<PieceType>& nextPieces, int& bestScore) {
        if (nextPieces.empty()) {
            bestScore = std::min(bestScore, Score(field));
            return;
        }
        PieceType type = nextPieces.front();
        nextPieces.pop_front();

        for (const auto& piecePosition : GetAllPiecePositions(field, type)) {
            field.PutAndClearFilledLines(piecePosition);
            GetBestScore(field, nextPieces, bestScore);
            field.EraseLastAddedPiece();
        }
        nextPieces.push_front(type);       
    }

}


PiecePosition Bot::GetBestPiecePosition(
    Field& field, 
    PieceType type, 
    std::deque<PieceType> nextPieces
) {
    int bestScore = INT_MAX;
    PiecePosition bestPiecePosition;

    #pragma omp parallel for firstprivate(field, nextPieces)
        for (const auto& piecePosition : GetAllPiecePositions(field, type)) {
            int currScore = INT_MAX;

            field.PutAndClearFilledLines(piecePosition);
            GetBestScore(field, nextPieces, currScore);
            field.EraseLastAddedPiece();

            #pragma omp critical
            {
                if (currScore < bestScore) {
                    bestScore = currScore;
                    bestPiecePosition = piecePosition;
                }
            }
        }  
    return bestPiecePosition;
}

