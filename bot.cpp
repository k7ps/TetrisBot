#include "bot.h"

#include <iostream>
#include <algorithm>

namespace {
    bool IsEpmtyRow(const Field& Field, int y){
        for (int x = 0; x < Field.GetSize().x; x++){
            if (Field[y][x] != 0) return false;
        }
        return true;
    }
    bool IsFullRow(const Field& Field, int y){
        for (int x = 0; x < Field.GetSize().x; x++){
            if (Field[y][x] == 0) return false;
        }
        return true;
    }
    bool IsTouch(const Field& Field, Point p, const Piece& CurrPiece){
        if (p.y == 0) return true;
        for (int u = 0; u < CurrPiece[0].size() && p.x+u < Field.GetSize().x; u++) {
            if (CurrPiece[0][u] && Field[p.y-1][p.x+u]) return true;
        }
        return false;
    }

    void FindSolution(Field& Field, std::deque<PieceType>& NextPieces, int number, bool first_object,
                        int& Best_number, PiecePosition& Best_Piece, PiecePosition& Curr_Piece){

        if (NextPieces.empty()){
            if (number > Best_number){
                Best_number = number;
                Best_Piece = Curr_Piece;
            }
            return;
        }
        PieceType currType = NextPieces.front();
        NextPieces.pop_front();
        const std::vector<Piece>& CurrRotations = GetAllRotations(currType);
        for (int rot = 0; rot < CurrRotations.size(); rot++) {
            const Piece& CurrPiece = CurrRotations[rot];

            for (int y = 0; y < Field.GetSize().y && (y == 0 || !IsEpmtyRow(Field, y-1)); y++) {
                for (int x = 0; x < Field.GetSize().x; x++) {
                    Point p(x, y);
                    if (Field.CanPut(p, CurrPiece) && IsTouch(Field, p, CurrPiece)) {
                        Field.Put(p, CurrPiece);
                        if (first_object) Best_Piece = Curr_Piece = PiecePosition(p, currType, rot);
                        for (int w = 0; w < CurrPiece.size() && y+w < Field.GetSize().y; w++){
                            if (IsFullRow(Field, y+w)) number++;
                        }
                        FindSolution(Field, NextPieces, number, false, Best_number, Best_Piece, Curr_Piece);
                        Field.Erase(p, CurrPiece);
                    }
                }
            }
        }
        NextPieces.push_front(currType);
    }
}

PiecePosition Bot::GetBestPiecePosition(Field& Field, PieceType Type, 
                                        const std::deque<PieceType>& NextPieces){
    std::deque<PieceType> NextPieces_Copy = NextPieces;
    std::cout << "ok" << std::endl;

    int Best_number = 0;
    PiecePosition Best_Piece;
    PiecePosition Curr_Piece;

    NextPieces_Copy.push_front(Type);
    FindSolution(Field, NextPieces_Copy, 0, true, Best_number, Best_Piece, Curr_Piece);

    return Best_Piece; // ? копия ли нужна
}