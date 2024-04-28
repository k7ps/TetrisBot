#include "field.h"

Field::Field(const Point& size)
    : Size(size),  Data(Size.y, std::vector<int8_t>(Size.x)) {}

bool Field::CanPut(const Point& pos, const Piece& piece) {
    for (int y = 0; y < piece.size(); y++) {
        for (int x = 0; x < piece[0].size(); x++) {
            if (piece[y][x] != 0) {
                Point p(x + pos.x, y + pos.y);
                if (p.x >= Size.x || p.y >= Size.y || Data[p.y][p.x] != 0) {
                    return false;
                }
            }
        }
    }
    return true;
}

bool Field::Put(const Point& pos, const Piece& piece) {
    if (!CanPut(pos, piece)) {
        return false;
    }

    for (int y = 0; y < piece.size(); y++) {
        for (int x = 0; x < piece[0].size(); x++) {
            if (piece[y][x]) {
                Data[pos.y + y][pos.x + x] = piece[y][x];
            }
        }
    }
    return true;
}

bool Field::ClearFilledLines() {
    std::vector<int> filledLines;
    for (int y = 0; y < Size.y; y++) {
        bool isFilled = 1;
        for (int x = 0; x < Size.x; x++) {
            if (Data[y][x] == 0) {
                isFilled = 0;
            }    
        }
        
        if (isFilled) {
            filledLines.push_back(y);
        }
    }

    if (filledLines.empty())
        return false;

    int cur = 0;
    for (int y = 0; y < Size.y; y++) {
        if (filledLines[cur] == y) {
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
    return true;
}

