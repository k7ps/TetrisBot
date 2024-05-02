#include "piece.h"

#include <exception>
#include <string>


namespace {

    void ThrowIfNotInRange(int i, int l, int r, const std::string& msg) {
        if (i < l || i > r) {
            throw std::invalid_argument(msg);
        }
    }

}


const std::vector<Piece>& GetAllRotations(PieceType type) {
    static const std::vector<std::vector<Piece>> PiecesRotations = {
        // I
        {
            {{1,1,1,1},
             {0,0,0,0},
             {0,0,0,0},
             {0,0,0,0}},
            {{1,0,0,0},
             {1,0,0,0},
             {1,0,0,0},
             {1,0,0,0}}, 
        },
        // J
        {
            {{0,0,2,0},
             {2,2,2,0},
             {0,0,0,0},
             {0,0,0,0}}, 
            {{2,2,0,0},
             {0,2,0,0},
             {0,2,0,0},
             {0,0,0,0}}, 
            {{2,2,2,0},
             {2,0,0,0},
             {0,0,0,0},
             {0,0,0,0}}, 
            {{2,0,0,0},
             {2,0,0,0},
             {2,2,0,0},
             {0,0,0,0}}, 
        },
        // L
        {
            {{3,0,0,0},
             {3,3,3,0},
             {0,0,0,0},
             {0,0,0,0}}, 
            {{0,3,0,0},
             {0,3,0,0},
             {3,3,0,0},
             {0,0,0,0}}, 
            {{3,3,3,0},
             {0,0,3,0},
             {0,0,0,0},
             {0,0,0,0}}, 
            {{3,3,0,0},
             {3,0,0,0},
             {3,0,0,0},
             {0,0,0,0}} 
        },
        // S
        {
            {{4,4,0,0},
             {0,4,4,0},
             {0,0,0,0},
             {0,0,0,0}}, 
            {{0,4,0,0},
             {4,4,0,0},
             {4,0,0,0},
             {0,0,0,0}}, 
        },
        // Z
        {
            {{0,5,5,0},
             {5,5,0,0},
             {0,0,0,0},
             {0,0,0,0}}, 
            {{5,0,0,0},
             {5,5,0,0},
             {0,5,0,0},
             {0,0,0,0}}, 
        },
        // T
        {
            {{0,6,0,0},
             {6,6,6,0},
             {0,0,0,0},
             {0,0,0,0}}, 
            {{0,6,0,0},
             {6,6,0,0},
             {0,6,0,0},
             {0,0,0,0}}, 
            {{6,6,6,0},
             {0,6,0,0},
             {0,0,0,0},
             {0,0,0,0}}, 
            {{6,0,0,0},
             {6,6,0,0},
             {6,0,0,0},
             {0,0,0,0}}, 
        },
        // O
        {
            {{7,7,0,0},
             {7,7,0,0},
             {0,0,0,0},
             {0,0,0,0}},
        },
    };
    
    int i = type;
    ThrowIfNotInRange(i, 0, PiecesRotations.size() - 1, "GetAllRotations(): no such type");

    return PiecesRotations[i];
}

const Piece& GetPiece(PieceType type, unsigned int rotation) {
    const auto& rotations = GetAllRotations(type);
    ThrowIfNotInRange(rotation, 0, rotations.size() - 1, "GetPiece(): no such rotation");

    return rotations[rotation];
}

const Piece& GetDefaultPiece(PieceType type) {
    return GetPiece(type, 0);
}

