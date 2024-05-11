#include "drawer.h"
#include "settings.h"

#include <osmanip/manipulators/colsty.hpp>
#include <osmanip/manipulators/cursor.hpp>
#include <osmanip/utility/iostream.hpp>
#include <osmanip/utility/options.hpp>

#include <string>
#include <unistd.h>


namespace {

    std::string MillisecondsToString(int64_t ms) {
        const int minDigitsCount = 4;

        std::string res(std::to_string(ms));
        if (res.size() < minDigitsCount) {
            res = std::string(minDigitsCount - res.size(), '0') + res;
        }
        res.insert(res.size() - 3, ".");
        
        return res + "s";
    }

}


TerminalDrawer::TerminalDrawer(const Point& fieldSize, const Point& pixelSize)
    : FieldSize(fieldSize)
    , PixelSize(pixelSize)
    , LastCalculationTime(NOT_GIVEN)
    , SumOfCalculationTimes(0)
    , CalculationCount(0)
    , LineCount(0)
{
    //osm::OPTION(osm::CURSOR::OFF);
}

void TerminalDrawer::DrawFrame(const Field& field, bool isGameOver) {
    ClearScreen();
    DrawNextPieces();
    DrawField(field, isGameOver);
    DrawLineCount();
    DrawCalculationTime();
    osm::cout << '\n' << std::flush;
}

void TerminalDrawer::DrawScreen(const Field& field) {
    DrawFrame(field, false);
}

void TerminalDrawer::DrawGameOverScreen(const Field& field) {
    DrawFrame(field, true);
}

void TerminalDrawer::DrawNextPieces() {
    Point size((6 + NextPieces.size() * 7), 3);
    if (NextPieces.empty()) {
        osm::cout << std::string(size.y * PixelSize.y, '\n');
        return;
    }

    osm::Canvas canvas(size.x * PixelSize.x, size.y * PixelSize.y);
    
    Point pos((FieldSize.x - GetPieceWidth(NextPieces[0])) / 2, 0);
    for (auto type : NextPieces) {
        for (auto point : GetDefaultPiece(type)) {
            DrawPixel(canvas, pos.x + point.x, size.y - pos.y - point.y - 2, (int)type, true);
        }   

        pos.x += GetPieceWidth(type) + 2;
    }

    canvas.refresh();
}

void TerminalDrawer::DrawField(const Field& field, bool isGameOver) {
    osm::Canvas canvas(FieldSize.x * PixelSize.x + 2, FieldSize.y * PixelSize.y + 2);
    canvas.enableFrame(true);
    canvas.setFrame(osm::FrameStyle::BOX);

    for (int y = 0; y < FieldSize.y; y++) {
        for (int x = 0; x < FieldSize.x; x++) {
            DrawPixel(canvas, x, y, field[FieldSize.y - y - 1][x], canvas.isFrameEnabled());
        }
    }    

    if (isGameOver) {
        static const std::string label = "Game Over"; 
        int labelSize = label.size();
        Point start((canvas.getWidth() - labelSize) / 2 + 1, canvas.getHeight() / 2 + 1);
        for (int y = start.y - PixelSize.y; y <= start.y + PixelSize.y; y++) {
            for (int x = start.x - PixelSize.x; x < start.x + labelSize + PixelSize.x; x++) {
                if (y == start.y && start.x <= x && x < start.x + labelSize) {
                    canvas.put(x, y, label[x - start.x]);
                } else {
                    canvas.put(x, y, ' ');
                }
            }
        }
    }
    
    canvas.refresh();
}

void TerminalDrawer::DrawPixel(osm::Canvas& canvas, int x, int y, int color, bool haveBorder) {
    for (int py = 0; py < PixelSize.y; py++) {
        for (int px = 0; px < PixelSize.x; px++) {
            canvas.put(
                x * PixelSize.x + px + haveBorder, 
                y * PixelSize.y + py + haveBorder, 
                ' ',
                osm::feat(osm::col, Settings::PieceColors[color])
            );
        }
    }
}

void TerminalDrawer::UpdateLineCount(int newLineCount) {
    LineCount = newLineCount;
}

void TerminalDrawer::DrawLineCount() {
    osm::cout << "             Lines: " << LineCount << '\n'; 
}

void TerminalDrawer::UpdateCalculationTime(int time) {
    LastCalculationTime = time;
    SumOfCalculationTimes += time;
    ++CalculationCount;
}

void TerminalDrawer::DrawCalculationTime() {
    if (LastCalculationTime == NOT_GIVEN) {
        return;
    }

    osm::cout << "      " << MillisecondsToString(LastCalculationTime) << "\n"
              << "mean: " << MillisecondsToString(SumOfCalculationTimes / CalculationCount) << "\n";
}

void TerminalDrawer::UpdateNextPieces(const std::deque<PieceType>& nextPieces) {
    NextPieces = std::vector<PieceType>(nextPieces.begin(), nextPieces.end());
}

void TerminalDrawer::ClearScreen() {
    system("clear");
}

TerminalDrawer::~TerminalDrawer() {
    osm::OPTION(osm::CURSOR::ON);
}

