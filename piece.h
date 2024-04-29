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
Piece CreatePiece(PieceType type);

struct PiecePosition {
    PiecePosition()
        : piece(4, std::vector<int8_t>(4)) {}

    PiecePosition(const Point& position, const Piece& p)
        : pos(position), piece(p) {}

    Point pos;
    Piece piece;
};

#endif // PIECE_H

