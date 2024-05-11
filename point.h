#ifndef POINT_H
#define POINT_H

struct Point {
    Point()
        : x{0}, y{0} {}

    Point(int _x, int _y) 
        : x{_x}, y{_y} {}

    Point(const Point& p)
        : x{p.x}, y{p.y} {}

    int x;
    int y;
};

#endif // POINT_H

