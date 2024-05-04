#include "field.h"

#include <algorithm>


Field::Field(const Point& size)
    : Size(size)
    , Data(Size.y, std::vector<int8_t>(Size.x)) 
    , HaveAtStart(false)
    , LineCount(0)
{}

bool Field::CanPut(const Point& pos, const Piece& piece) const { 
    for (const auto& point : piece) {
        Point p(pos.x + point.x, pos.y + point.y);  
        if (p.x >= Size.x || p.y >= Size.y || Data[p.y][p.x] != 0) {
            return false;
        }
    }
    return true;
}

bool Field::Put(const Point& pos, const Piece& piece) {
    if (!CanPut(pos, piece)) {
        return false;
    }

    for (const auto& point : piece) {
        Data[pos.y + point.y][pos.x + point.x] = piece.Type;
    }
    return true;
}

bool Field::PutAtStart(PieceType type) {
    const auto& piece = GetDefaultPiece(type);

    PieceAtStart = PiecePosition(
        Point((Size.x - piece.GetWidth() - 1) / 2, Size.y - piece.GetHeight() - 1), 
        piece.Type
    );

    HaveAtStart = Put(PieceAtStart);
    return HaveAtStart;
}

bool Field::CanErase(const Point& pos, const Piece& piece) const {
    for (const auto& point : piece) {
        Point p(pos.x + point.x, pos.y + point.y);  
        if (p.x >= Size.x || p.y >= Size.y || Data[p.y][p.x] == 0) {
            return false;
        }
    }
    return true;
}

bool Field::Erase(const Point& pos, const Piece& piece) {
    if (!CanErase(pos, piece)) {
        return false;
    }

    for (const auto& point : piece) {
        Data[pos.y + point.y][pos.x + point.x] = 0;
    }
    return true;
}

bool Field::EraseFromStart() {
    if (!HaveAtStart) {
        return false;
    }

    return Erase(PieceAtStart);
}


bool Field::CanPut(const PiecePosition& piecePos) const {
    return CanPut(piecePos.Pos, GetPiece(piecePos.Type, piecePos.Rotation));
}

bool Field::Put(const PiecePosition& piecePos) {
    return Put(piecePos.Pos, GetPiece(piecePos.Type, piecePos.Rotation));
}

bool Field::CanErase(const PiecePosition& piecePos) const {
    return CanErase(piecePos.Pos, GetPiece(piecePos.Type, piecePos.Rotation));
}

bool Field::Erase(const PiecePosition& piecePos) {
    return Erase(piecePos.Pos, GetPiece(piecePos.Type, piecePos.Rotation));
}

bool Field::ClearFilledLines() {
    std::vector<int> filledLines;
    for (int y = 0; y < Size.y; y++) {
        bool isFilled = 1;
        for (int x = 0; x < Size.x; x++) {
            if (Data[y][x] == 0) {
                isFilled = 0;
            }    
        }

        if (isFilled) {
            filledLines.push_back(y);
            ++LineCount;
        }
    }

    if (filledLines.empty())
        return false;

    int cur = 0;
    for (int y = 0; y < Size.y; y++) {
        if (filledLines[cur] == y) {
            for (int x = 0; x < Size.x; x++) {
                Data[y][x] = 0;
            }
            ++cur;
        } else if (cur > 0){
            for (int x = 0; x < Size.x; x++) {
                Data[y - cur][x] = Data[y][x];
                Data[y][x] = 0;
            }
        }
    }
    return true;
}

