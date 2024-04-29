#ifndef DRAWER_H
#define DRAWER_H

#include "field.h"

#include <osmanip/graphics/canvas.hpp>


const int NOT_GIVEN = -1;

class TerminalDrawer {
public:
    TerminalDrawer(const Point& fieldSize, const Point& pixelSize);

    void DrawFrame(const Field& field, int time = NOT_GIVEN);

    ~TerminalDrawer();

private:
    void DrawTime(int ms);
    void ClearScreen();

private:
    Point FieldSize;
    Point PixelSize;

    osm::Canvas Canvas;     

    int LastTimeMs;
};

#endif // DRAWER_H
