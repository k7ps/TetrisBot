#ifndef PIECE_H
#define PIECE_H

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

#endif // PIECE_H

