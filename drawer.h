#ifndef DRAWER_H
#define DRAWER_H

#include "field.h"

#include <osmanip/graphics/canvas.hpp>


const int NOT_GIVEN = 1;

class TerminalDrawer {
public:
    TerminalDrawer(const Point& fieldSize, const Point& pixelSize);

    void DrawFrame(const Field& field);

    void UpdateLineCount(int newLineCount);
    void UpdateCalculationTime(int time);

    ~TerminalDrawer();

private:
    void DrawLineCount();
    void DrawCalculationTime();
    void ClearScreen();

private:
    Point FieldSize;
    Point PixelSize;

    osm::Canvas Canvas;     

    int64_t LastCalculationTime; // ms
    int64_t SumOfCalculationTimes;
    int64_t CalculationCount;

    int LineCount;
};

#endif // DRAWER_H
