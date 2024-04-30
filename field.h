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

    Point GetSize() const {
        return Size;
    }

    int GetLineCount() const {
        return LineCount;
    }

    // return TRUE if action done, FALSE if not
    bool CanPut(const Point& pos, const Piece& piece) const;
    bool Put(const Point& pos, const Piece& piece);
    bool PutAtStart(PieceType type);

    bool CanErase(const Point& pos, const Piece& piece) const;
    bool Erase(const Point& pos, const Piece& piece);
    bool EraseFromStart();

    bool ClearFilledLines();

private:
    Point Size;
    std::vector<std::vector<int8_t>> Data;

    bool HaveAtStart;
    PiecePosition PieceAtStart;

    int LineCount;
};

#endif // FIELD_H
