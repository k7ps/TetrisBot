#ifndef DRAWER_H
#define DRAWER_H

#include "field.h"

#include <osmanip/graphics/canvas.hpp>

#include <vector>


const int NOT_GIVEN = 1;

class TerminalDrawer {
public:
    TerminalDrawer(const Point& fieldSize, const Point& pixelSize);

    void DrawScreen(const Field&);
    void DrawGameOverScreen(const Field&);

    void UpdateLineCount(int);
    void UpdateCalculationTime(int);
    void UpdateNextPieces(const std::deque<PieceType>&);

    ~TerminalDrawer();

private:
    void DrawFrame(const Field&, bool isGameOver);
    void DrawNextPieces();
    void DrawField(const Field&, bool isGameOver);
    void DrawLineCount();
    void DrawCalculationTime();

    void ClearScreen();

    void DrawPixel(osm::Canvas&, int x, int y, int color, bool haveBorder);

private:
    Point FieldSize;
    Point PixelSize;

    int64_t LastCalculationTime; // ms
    int64_t SumOfCalculationTimes;
    int64_t CalculationCount;

    int LineCount;

    std::vector<PieceType> NextPieces;
};

#endif // DRAWER_H

