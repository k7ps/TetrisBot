#include "piece.h"

#include <algorithm>
#include <exception>
#include <string>


namespace {

    void ThrowIfNotInRange(int i, int l, int r, const std::string& msg) {
        if (i < l || i > r) {
            throw std::invalid_argument(msg + ": " + std::to_string(i));
        }
    }

}

Piece::Piece(PieceType type, std::vector<Point>&& data)
    : Type(type), Data(std::move(data)) 
{
    if (Data.size() != 4) {
        throw std::invalid_argument("Piece::Piece(): Data.size() != 4");
    }    
    for (const auto& point : Data) {
        Height = std::max(Height, point.y + 1);
        Width = std::max(Width, point.x + 1);
    }
}

const std::vector<Piece>& GetAllRotations(PieceType type) {
    static const std::vector<std::vector<Piece>> PiecesRotations = {
        {
            Piece(PieceType::I, {Point(0, 0), Point(1, 0), Point(2, 0), Point(3, 0)}),
            Piece(PieceType::I, {Point(0, 0), Point(0, 1), Point(0, 2), Point(0, 3)}),
        },
        {
            Piece(PieceType::J, {Point(2, 0), Point(0, 1), Point(1, 1), Point(2, 1)}),
            Piece(PieceType::J, {Point(0, 0), Point(1, 0), Point(1, 1), Point(1, 2)}),
            Piece(PieceType::J, {Point(0, 0), Point(1, 0), Point(2, 0), Point(0, 1)}),
            Piece(PieceType::J, {Point(0, 0), Point(0, 1), Point(0, 2), Point(1, 2)}),
        },
        {
            Piece(PieceType::L, {Point(0, 0), Point(0, 1), Point(1, 1), Point(2, 1)}),
            Piece(PieceType::L, {Point(1, 0), Point(1, 1), Point(0, 2), Point(1, 2)}),
            Piece(PieceType::L, {Point(0, 0), Point(1, 0), Point(2, 0), Point(2, 1)}),
            Piece(PieceType::L, {Point(0, 0), Point(1, 0), Point(0, 1), Point(0, 2)}),
        },
        {
            Piece(PieceType::S, {Point(0, 0), Point(1, 0), Point(1, 1), Point(2, 1)}),
            Piece(PieceType::S, {Point(1, 0), Point(0, 1), Point(1, 1), Point(0, 2)}),
        },
        {
            Piece(PieceType::Z, {Point(1, 0), Point(2, 0), Point(0, 1), Point(1, 1)}),
            Piece(PieceType::Z, {Point(0, 0), Point(0, 1), Point(1, 1), Point(1, 2)}),
        },
        {
            Piece(PieceType::T, {Point(1, 0), Point(0, 1), Point(1, 1), Point(2, 1)}),
            Piece(PieceType::T, {Point(1, 0), Point(0, 1), Point(1, 1), Point(1, 2)}),
            Piece(PieceType::T, {Point(0, 0), Point(1, 0), Point(2, 0), Point(1, 1)}),
            Piece(PieceType::T, {Point(0, 0), Point(0, 1), Point(1, 1), Point(0, 2)}),
        },
        {
            Piece(PieceType::O, {Point(0, 0), Point(1, 0), Point(0, 1), Point(1, 1)}),
        },
    };

    int i = type;
    ThrowIfNotInRange(i, 1, PiecesRotations.size(), "GetAllRotations(): no such type");

    return PiecesRotations[i - 1];
}

int GetRotationCount(PieceType type) {
    return GetAllRotations(type).size();
}

const Piece& GetPiece(PieceType type, unsigned int rotation) {
    const auto& rotations = GetAllRotations(type);
    ThrowIfNotInRange(rotation, 0, rotations.size() - 1, "GetPiece(): no such rotation");

    return rotations[rotation];
}

const Piece& GetDefaultPiece(PieceType type) {
    return GetPiece(type, 0);
}

int GetPieceHeight(PieceType type, unsigned int rotation) {
    return GetPiece(type, rotation).GetHeight();
}

int GetPieceWidth(PieceType type, unsigned int rotation) {
    return GetPiece(type, rotation).GetWidth();
}

