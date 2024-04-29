#ifndef DRAWER_H
#define DRAWER_H

#include "field.h"

#include <osmanip/graphics/canvas.hpp>


const int64_t NOT_GIVEN = -1;

class TerminalDrawer {
public:
    TerminalDrawer(const Point& fieldSize, const Point& pixelSize);

    void DrawFrame(const Field& field, int64_t time = NOT_GIVEN);

    ~TerminalDrawer();

private:
    void DrawTime(int ms);
    void ClearScreen();

private:
    Point FieldSize;
    Point PixelSize;

    osm::Canvas Canvas;     

    int64_t LastCalculationTime; // ms
};

#endif // DRAWER_H
