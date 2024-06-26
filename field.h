#ifndef FIELD_H
#define FIELD_H

#include "piece.h"
#include "point.h"

#include <exception>
#include <vector>
#include <stack>


struct Event {
    enum EventType {
        ADD_PIECE,
        CLEAR_LINES
    };

    Event(PiecePosition piecePos, bool isStart)
        : Type(ADD_PIECE), AddedPiece(piecePos), IsStart(isStart) {}

    Event(std::vector<int>&& y, std::vector<std::vector<int8_t>>&& lines)
        : Type(CLEAR_LINES), Heights(std::move(y)), ClearedLines(std::move(lines)) {}

    EventType Type;

    PiecePosition AddedPiece;
    bool IsStart;

    std::vector<int> Heights;
    std::vector<std::vector<int8_t>> ClearedLines;
};


class Field {
public:
    Field(const Point& size);
    Field(const Field&);

    Field& operator=(const Field&);

    const int8_t* operator[](size_t index) const {
        return Data[index].data(); 
    }        

    Point GetSize() const { return Size; }
    int GetLineCount() const { return LineCount;}
    int GetFirstEmptyRow() const { return std::min(FirstEmptyRow, Size.y - 1); }

    // return TRUE if action done, FALSE if not
    bool CanPut(const PiecePosition&) const;

    bool Put(const PiecePosition&);
    bool PutAndClearFilledLines(const PiecePosition&);
    bool PutAtStart(PieceType);

    bool ClearFilledLines();

    void EraseLastAddedPiece();

private:
    bool CanPutImpl(const PiecePosition&, bool isStart) const;
    bool PutImpl(const PiecePosition&, bool isStart);

    void Erase(const PiecePosition&, bool isStart);
    void RestoreClearedLines(const std::vector<int>& heights, const std::vector<std::vector<int8_t>>& lines);

private:
    Point Size;
    std::vector<std::vector<int8_t>> Data;

    bool HaveAtStart;
    PiecePosition PieceAtStart;

    int LineCount;
    int FirstEmptyRow;

    std::stack<Event> Events;
};

#endif // FIELD_H

