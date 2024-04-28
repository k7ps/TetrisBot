#ifndef POINT_H
#define POINT_H

struct Point {
    Point(int _x, int _y) 
        : x{_x}, y{_y} {}

    Point(const Point& p)
        : x{p.x}, y{p.y} {}

    int x = 0;
    int y = 0;
};

#endif // POINT_H
