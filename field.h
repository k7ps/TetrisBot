#ifndef FIELD_H
#define FIELD_H

#include "piece.h"
#include "point.h"

#include <vector>


class Field {
public:
    Field(const Point& size);

    const int8_t* operator[](size_t index) const {
        return Data[index].data(); 
    }        

    bool CanPut(const Point& pos, const Piece& piece);
    bool Put(const Point& pos, const Piece& piece);
    bool PutAtStart(const Piece& piece);

    bool CanErase(const Point& pos, const Piece& piece);
    bool Erase(const Point& pos, const Piece& piece);
    bool EraseFromStart();

    bool ClearFilledLines();

private:
    Point Size;
    std::vector<std::vector<int8_t>> Data;

    bool HaveAtStart;
    Piece PieceAtStart;
    Point PieceAtStartPos;
};

#endif // FIELD_H
