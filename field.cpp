#include "field.h"

#include <algorithm>


Field::Field(const Point& size)
    : Size(size)
    , Data(Size.y, std::vector<int8_t>(Size.x)) 
    , HaveAtStart(false)
    , LineCount(0)
{}

bool Field::PutAtStart(PieceType type) {
    PieceAtStart = PiecePosition(
        Point((Size.x - GetPieceWidth(type) - 1) / 2, Size.y - GetPieceHeight(type) - 1), 
        type
    );

    HaveAtStart = Put(PieceAtStart);
    return HaveAtStart;
}

bool Field::CanPut(const PiecePosition& piecePos) const {
    for (const auto& point : GetPiece(piecePos.Type, piecePos.Rotation)) {
        Point p(piecePos.Pos.x + point.x, piecePos.Pos.y + point.y);  
        if (p.x >= Size.x || p.y >= Size.y || Data[p.y][p.x] != 0) {
            return false;
        }
    }
    return true;
}

bool Field::Put(const PiecePosition& piecePos) {
    if (!CanPut(piecePos)) {
        return false;
    }

    for (const auto& point : GetPiece(piecePos.Type, piecePos.Rotation)) {
        Data[piecePos.Pos.y + point.y][piecePos.Pos.x + point.x] = piecePos.Type;
    }

    Events.push(Event(piecePos));
    return true;
}

bool Field::PutAndClearFilledLines(const PiecePosition& piecePos) {
    if (!Put(piecePos)) {
        return false;
    }
    ClearFilledLines();
    return true;
}

void Field::Erase(const PiecePosition& piecePos) {
    for (const auto& point : GetPiece(piecePos.Type, piecePos.Rotation)) {
        Data[piecePos.Pos.y + point.y][piecePos.Pos.x + point.x] = 0;
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

    Erase(Events.top().AddedPiece);
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
            ++LineCount;
        }
    }

    if (heights.empty()) {
        return false;
    }
    std::vector<std::vector<int8_t>> filledLines;  

    int cur = 0;
    for (int y = 0; y < Size.y; y++) {
        if (heights[cur] == y) {
            filledLines.emplace_back(Data[y].begin(), Data[y].end());
            for (int x = 0; x < Size.x; x++) {
                Data[y][x] = 0;
            }
            ++cur;
        } else if (cur > 0){
            for (int x = 0; x < Size.x; x++) {
                Data[y - cur][x] = Data[y][x];
                Data[y][x] = 0;
            }
        }
    }

    Events.push(Event(std::move(heights), std::move(filledLines)));
    return true;
}

void Field::RestoreClearedLines(
    const std::vector<int>& heights, 
    const std::vector<std::vector<int8_t>>& lines
) {
    int n = heights.size();
    LineCount -= n;

    int cur = n - 1;
    for (int y = Size.y - 1; y >= 0; y--) {
        if (y + cur + 1 < Size.y) {
            for (int x = 0; x < Size.x; x++) {
                Data[y + cur + 1][x] = Data[y][x];
                Data[y][x] = 0;
            }
        }
        if (heights[cur] == y) {
            for (int x = 0; x < Size.x; x++) {
                Data[y][x] = lines[cur][x];
            }
            if (--cur == -1) {
                break;
            }
        }
    }
}

