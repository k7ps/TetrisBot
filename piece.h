#ifndef PIECE_H
#define PIECE_H

#include "point.h"

#include <iostream>
#include <vector>


using Piece = std::vector<std::vector<int8_t>>;

enum PieceType {
    I,
    J,
    L,
    S,
    Z,
    T,
    O
};

const std::vector<Piece>& GetAllRotations(PieceType type);
const Piece& GetPiece(PieceType type, unsigned int rotation);
const Piece& GetDefaultPiece(PieceType type);

struct PiecePosition {
    PiecePosition()
        : Type(static_cast<PieceType>(10)), Rotation(0) {}

    PiecePosition(const Point& p, PieceType t, unsigned int r = 0)
        : Pos(p), Type(t), Rotation(r) {}

    Point Pos;
    PieceType Type;
    unsigned int Rotation; 
};

#endif // PIECE_H

