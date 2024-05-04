#include "bot.h"


namespace {

    int CountRow(const Field& Field, int y){
        int count = 0;
        for (int x = 0; x < Field.GetSize().x; x++){
            if (Field[y][x]) count++;
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
    bool IsFullRow(const Field& Field, int y){
        for (int x = 0; x < Field.GetSize().x; x++){
            if (!Field[y][x]) { 
                return false;
            }
        }
        return true;
    }

    bool IsTouch(const Field& Field, Point p, const Piece& CurrPiece){
        for (int y = 0; y < CurrPiece.size(); y++) {
            for (int x = 0; x < CurrPiece[y].size(); x++) {
                if (CurrPiece[y][x] && (y == 0 || !CurrPiece[y-1][x])) {
                    if (p.y + y == 0 || Field[p.y + y - 1][p.x + x]) return true;
                }
            }
        }
        return false;
    }

    double Score(const Field& Field){
        double score = 0;
        for (int y = 0; y < Field.GetSize().y; y++){
            double k = 1.0 + 0.05 * (Field.GetSize().y - y);
            double count = CountRow(Field, y);
            score += k * (1.0 + count) * count / 2.0;
            if (IsFullRow(Field, y)) score += k * 4;
        }
        return score;
    }

    void FindSolution(Field& Field, std::deque<PieceType>& NextPieces, bool first_object,
                        double& Best_number, PiecePosition& Best_Piece, PiecePosition Curr_Piece){

        if (NextPieces.empty()){
            double number = Score(Field);
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
                        if (first_object){
                            Curr_Piece = PiecePosition(p, currType, rot);
                        } 
                        FindSolution(Field, NextPieces, false, Best_number, Best_Piece, Curr_Piece);
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

    double Best_number = 0.0;
    PiecePosition Best_Piece;
    PiecePosition Curr_Piece;

    NextPieces_Copy.push_front(Type);
    FindSolution(Field, NextPieces_Copy, true, Best_number, Best_Piece, Curr_Piece);

    return Best_Piece;
}