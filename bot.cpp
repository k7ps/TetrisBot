#include "bot.h"
#include <stdio.h>
#include <omp.h>


namespace {

    int Count_of_Filled_Point_In_Row(const Field& Field, int y) {
        int count = 0;
        for (int x = 0; x < Field.GetSize().x; x++) {
            if (Field[y][x]) {
                count++;
            }
        }
        return count;
    }

    int Count_of_Holded_Point_In_Row(const Field& Field, int y) {
        if (y >= Field.GetSize().y - 1) {
            return 0;
        }
        int count = 0;
        for (int x = 0; x < Field.GetSize().x; x++) {
            if (!Field[y][x] && Field[y+1][x]) {
                count++;
            }
        }
        return count;
    }


    bool IsEpmtyRow(const Field& Field, int y){
        for (int x = 0; x < Field.GetSize().x; x++){
            if (Field[y][x]) {
                 return false;
            }
        }
        return true;
    }
    // bool IsFullRow(const Field& Field, int y){
    //     for (int x = 0; x < Field.GetSize().x; x++){
    //         if (!Field[y][x]) { 
    //             return false;
    //         }
    //     }
    //     return true;
    // }

    // bool IsTouch(const Field& Field, Point p, const Piece& CurrPiece){
    //     for (int y = 0; y < CurrPiece.size(); y++) {
    //         for (int x = 0; x < CurrPiece[y].size(); x++) {
    //             if (CurrPiece[y][x] && (y == 0 || !CurrPiece[y-1][x])) {
    //                 if (p.y + y == 0 || Field[p.y + y - 1][p.x + x]) return true;
    //             }
    //         }
    //     }
    //     return false;
    // }

    double Score(const Field& Field) {
        double score = 0;
        for (int y = 0; y < Field.GetSize().y && !IsEpmtyRow(Field, y); y++) {
            score += Count_of_Filled_Point_In_Row(Field, y) * y;
            score += Count_of_Holded_Point_In_Row(Field, y) * y;
        }
        return score;
    }


    std::vector<PiecePosition> GetAllPiecePositions(Field& Field, PieceType Type) {
        std::vector<PiecePosition> All_Piece_Positions;

        for (unsigned int rot = 0; rot < GetRotationCount(Type); rot++) {
            for (int x = 0; x < Field.GetSize().x; x++) {
                for (int y = 0; y < Field.GetSize().y; y++) {
                    PiecePosition Curr_Piece_Position{Point(x, y), Type, rot};
                    if (Field.CanPut(Curr_Piece_Position)) {
                        All_Piece_Positions.push_back(Curr_Piece_Position);
                        break;
                    }
                }
            }
        }
        return All_Piece_Positions;
    }


    void Get_Best_score(Field& Field, std::deque<PieceType>& NextPieces, double& Best_Score) {
        if (NextPieces.empty()) {
            Best_Score = std::min(Best_Score, Score(Field));
            return;
        }

        PieceType Type = NextPieces.front();
        NextPieces.pop_front();

        for (const auto& Curr_Piece_Position: GetAllPiecePositions(Field, Type)) {
            Field.Put(Curr_Piece_Position);
            Get_Best_score(Field, NextPieces, Best_Score);
            Field.EraseLastAddedPiece();
        }
        NextPieces.push_front(Type);       
    }
}


PiecePosition Bot::GetBestPiecePosition(Field& Field, PieceType Type, 
                                        const std::deque<PieceType>& NextPieces) {
    std::deque<PieceType> NextPieces_Copy = NextPieces;

    double Best_score = 10000.0;
    double Curr_score = 10000.0;
    PiecePosition Best_Piece_Position;

    omp_set_num_threads(5);

    #pragma omp parallel for
    for (const auto& First_Piece_Position: GetAllPiecePositions(Field, Type)) {
        Field.Put(First_Piece_Position);

        Get_Best_score(Field, NextPieces_Copy, Curr_score);
        Field.EraseLastAddedPiece();

        if (Curr_score < Best_score) {
            Best_score = Curr_score;
            Best_Piece_Position = First_Piece_Position;
        }
        Curr_score = 10000.0;
    }
    

    return Best_Piece_Position;
}