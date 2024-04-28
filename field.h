#ifndef FIELD_H
#define FIELD_H

#include "piece.h"

#include <vector>


struct Point {
    Point(int _x, int _y) 
        : x{_x}, y{_y} {}

    Point(const Point& p)
        : x{p.x}, y{p.y} {}

    int x = 0;
    int y = 0;
};

class Field {
    public:
        Field(const Point& size);

        const int8_t* operator[](size_t index) const {
            return Data[index].data(); 
        }        

        int8_t* operator[](size_t index) {
            return Data[index].data(); 
        }        
        
        bool CanPut(const Point& pos, const Piece& piece);
        bool Put(const Point& pos, const Piece& piece);
        
        bool ClearFilledLines();

    private:
        Point Size;
        std::vector<std::vector<int8_t>> Data;

};

#endif // FIELD_H
