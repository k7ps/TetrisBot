#ifndef PIECE_H
#define PIECE_H

#include "point.h"

#include <iostream>
#include <vector>


enum PieceType {
    UNKNOWN,
    I,
    J,
    L,
    S,
    Z,
    T,
    O
};

class Piece {
public:
    Piece(PieceType type, std::vector<Point>&& data);

    const Point& operator[](size_t index) const { return Data[index]; }        

    int GetSize() const { return Data.size(); }

    const auto begin() const { return Data.begin(); } 
    const auto end() const { return Data.end(); }

    int GetHeight() const { return Height; }
    int GetWidth() const { return Width; }

public:
    const PieceType Type;

private:
    std::vector<Point> Data;
    int Height = 0;
    int Width = 0;
};

const std::vector<Piece>& GetAllRotations(PieceType type);
int GetRotationCount(PieceType type);
const Piece& GetPiece(PieceType type, unsigned int rotation);
const Piece& GetDefaultPiece(PieceType type);

struct PiecePosition {
    PiecePosition()
        : Type(PieceType::UNKNOWN), Rotation(0) {}

    PiecePosition(const Point& p, PieceType t, unsigned int r = 0)
        : Pos(p), Type(t), Rotation(r) {}

    Point Pos;
    PieceType Type;
    unsigned int Rotation; 
};

#endif // PIECE_H

