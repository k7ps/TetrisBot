#include "bot.h"


namespace {

    bool IsEpmtyRow(const Field& field, int y){
        for (int x = 0; x < field.GetSize().x; x++){
            if (field[y][x]) {
                 return false;
            }
        }
        return true;
    }


    int Score(const Field& field) {
        int score = 0;
        for (int y = 0; y < field.GetSize().y && !IsEpmtyRow(field, y); y++) {
            for (int x = 0; x < field.GetSize().x; x++) {
                if (field[y][x]) {
                    score += y + 1;
                } else if (y + 1 < field.GetSize().y && field[y+1][x]) {
                    score += y + 1;
                }
            }
        }
        return score;
    }


    std::vector<PiecePosition> GetAllPiecePositions(const Field& field, PieceType type) {
        std::vector<PiecePosition> allPiecePositions;

        for (unsigned int rot = 0; rot < GetRotationCount(type); rot++) {
            for (int x = 0; x < field.GetSize().x; x++) {
                for (int y = 0; y < field.GetSize().y; y++) {
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

        for (const auto& currPiecePosition: GetAllPiecePositions(field, type)) {
            field.PutAndClearFilledLines(currPiecePosition);
            GetBestScore(field, nextPieces, bestScore);
            field.EraseLastAddedPiece();
        }
        nextPieces.push_front(type);       
    }
}


PiecePosition Bot::GetBestPiecePosition(const Field& field, PieceType type, 
                                        const std::deque<PieceType>& nextPieces) {
    std::deque<PieceType> nextPiecesCopy = nextPieces;

    int bestScore = 10000.0;
    int currScore = 10000.0;
    PiecePosition bestPiecePosition;

    Field fieldCopy{field};
    for (const auto& firstPiecePosition : GetAllPiecePositions(field, type)) {
        fieldCopy.PutAndClearFilledLines(firstPiecePosition);

        GetBestScore(fieldCopy, nextPiecesCopy, currScore);
        fieldCopy.EraseLastAddedPiece();

        if (currScore < bestScore) {
            bestScore = currScore;
            bestPiecePosition = firstPiecePosition;
        }
        currScore = 10000.0;
    }
    return bestPiecePosition;
}