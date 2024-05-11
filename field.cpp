#include "field.h"

#include <algorithm>


Field::Field(const Point& size)
    : Size(size)
    , Data(Size.y, std::vector<int8_t>(Size.x)) 
    , HaveAtStart(false)
    , LineCount(0)
    , FirstEmptyRow(0)
{}

Field::Field(const Field& field)
    : Size(field.Size)
    , Data(field.Data)
    , FirstEmptyRow(field.FirstEmptyRow)
{}

Field& Field::operator=(const Field& field) {
    Size = field.Size;
    Data = field.Data;
    FirstEmptyRow = field.FirstEmptyRow;
    return *this;
}

bool Field::CanPut(const PiecePosition& piecePos) const {
    return CanPutImpl(piecePos, false);
}

bool Field::Put(const PiecePosition& piecePos) {
    return PutImpl(piecePos, false);
}

bool Field::PutAtStart(PieceType type) {
    PieceAtStart = PiecePosition(
        Point((Size.x - GetPieceWidth(type)) / 2, Size.y - GetPieceHeight(type)), 
        type
    );

    HaveAtStart = PutImpl(PieceAtStart, true);
    return HaveAtStart;
}

bool Field::CanPutImpl(const PiecePosition& piecePos, bool isStart) const {
    if (piecePos.Pos.y < 0 || piecePos.Pos.x < 0) {
        return false;
    }

    bool isTouch = isStart;
    for (const auto& point : GetPiece(piecePos.Type, piecePos.Rotation)) {
        Point p(piecePos.Pos.x + point.x, piecePos.Pos.y + point.y);  
        if (p.x >= Size.x || p.y >= Size.y || Data[p.y][p.x] != 0) {
            return false;
        }
        if (isTouch || p.y == 0 || Data[p.y - 1][p.x] != 0) {
            isTouch = true;
        }
    }
    return isTouch;
}

bool Field::PutImpl(const PiecePosition& piecePos, bool isStart) {
    if (!CanPutImpl(piecePos, isStart)) {
        return false;
    }

    for (const auto& point : GetPiece(piecePos.Type, piecePos.Rotation)) {
        Data[piecePos.Pos.y + point.y][piecePos.Pos.x + point.x] = piecePos.Type;
    }

    if (!isStart) {
        FirstEmptyRow = std::max(
            FirstEmptyRow, 
            piecePos.Pos.y + GetPieceHeight(piecePos.Type, piecePos.Rotation)
        );
    }

    Events.push(Event(piecePos, isStart));
    return true;
}

bool Field::PutAndClearFilledLines(const PiecePosition& piecePos) {
    if (!Put(piecePos)) {
        return false;
    }
    ClearFilledLines();
    return true;
}

void Field::Erase(const PiecePosition& piecePos, bool isStart) {
    for (const auto& point : GetPiece(piecePos.Type, piecePos.Rotation)) {
        Data[piecePos.Pos.y + point.y][piecePos.Pos.x + point.x] = 0;
    }
    if (!isStart && piecePos.Pos.y + GetPieceHeight(piecePos.Type, piecePos.Rotation) >= FirstEmptyRow) {
        for (int y = std::min(FirstEmptyRow, Size.y - 1); y >= 0; y--) {
            bool isEmpty = true;
            for (int x = 0; x < Size.x; x++) {
                if (Data[y][x] != 0) {
                    isEmpty = false;
                    break;
                }
            }
            if (isEmpty) {
                FirstEmptyRow = y;
            } else {
                break;
            }
        }
    }
}

void Field::EraseLastAddedPiece() {
    if (Events.empty()) {
        return;
    }

    while (Events.top().Type != Event::ADD_PIECE) {
        const auto& top = Events.top();
        RestoreClearedLines(top.Heights, top.ClearedLines);
        Events.pop();
        if (Events.empty()) {
            return;
        }
    }

    const auto& top = Events.top();
    Erase(top.AddedPiece, top.IsStart);
    Events.pop();
}

bool Field::ClearFilledLines() {
    std::vector<int> heights;
    for (int y = 0; y < Size.y; y++) {
        bool isFilled = 1;
        for (int x = 0; x < Size.x; x++) {
            if (Data[y][x] == 0) {
                isFilled = 0;
            }    
        }

        if (isFilled) {
            heights.push_back(y);
        }
    }

    if (heights.empty()) {
        return false;
    }

    std::vector<std::vector<int8_t>> newData(Size.y, std::vector<int8_t>(Size.x));
    std::vector<std::vector<int8_t>> filledLines;  

    int linesIdx = 0;
    int newDataIdx = 0;
    for (int y = 0; y < Size.y; y++) {
        if (linesIdx < heights.size() && heights[linesIdx] == y) {
            filledLines.emplace_back(std::vector<int8_t>(Size.x));
            for (int x = 0; x < Size.x; x++) {
                filledLines[linesIdx][x] = Data[y][x];
            } 
            ++linesIdx;
        } else {
            for (int x = 0; x < Size.x; x++) {
                newData[newDataIdx][x] = Data[y][x];
            } 
            ++newDataIdx;
        }
    }
    Data = newData;

    FirstEmptyRow -= heights.size();
    LineCount += heights.size();
    Events.push(Event(std::move(heights), std::move(filledLines)));
    return true;
}

void Field::RestoreClearedLines(
    const std::vector<int>& heights, 
    const std::vector<std::vector<int8_t>>& lines
) {
    std::vector<std::vector<int8_t>> newData(Size.y, std::vector<int8_t>(Size.x));

    int linesIdx = 0;
    int oldDataIdx = 0;
    for (int y = 0; y < Size.y; y++) {
        if (linesIdx < heights.size() && heights[linesIdx] == y) {
            for (int x = 0; x < Size.x; x++) {
                newData[y][x] = lines[linesIdx][x];
            } 
            ++linesIdx;
        } else {
            for (int x = 0; x < Size.x; x++) {
                newData[y][x] = Data[oldDataIdx][x];
            } 
            ++oldDataIdx;
        }
    }

    Data = newData;

    FirstEmptyRow += heights.size();
    LineCount -= heights.size();
}

