#include "drawer.h"
#include "settings.h"

#include <osmanip/manipulators/colsty.hpp>
#include <osmanip/manipulators/cursor.hpp>
#include <osmanip/utility/iostream.hpp>
#include <osmanip/utility/options.hpp>

#include <string>
#include <unistd.h>

namespace {

    std::string TimeMsToString(int ms) {
        const int minDigitsCount = 4;

        std::string res(std::to_string(ms));
        if (res.size() < minDigitsCount) {
            res = std::string(minDigitsCount - res.size(), '0') + res;
        }
        res.insert(res.size() - 3, 1, '.');
        
        return res + "s";
    }

}

TerminalDrawer::TerminalDrawer(const Point& fieldSize, const Point& pixelSize)
    : FieldSize(fieldSize)
    , PixelSize(pixelSize)
    , Canvas(FieldSize.x * PixelSize.x + 2, FieldSize.y * PixelSize.y + 2)
    , LastTimeMs(NOT_GIVEN)
{
    Canvas.enableFrame(true);
    Canvas.setFrame(osm::FrameStyle::BOX);

    //osm::OPTION(osm::CURSOR::OFF);
}

void TerminalDrawer::DrawFrame(const Field& field, int time) {
    ClearScreen();
    for (int y = 0; y < FieldSize.y; y++) {
        for (int x = 0; x < FieldSize.x; x++) {
            for (int py = 0; py < PixelSize.y; py++) {
                for (int px = 0; px < PixelSize.x; px++) {
                    Canvas.put(
                        x * PixelSize.x + px + 1, 
                        y * PixelSize.y + py + 1, 
                        ' ',
                        osm::feat(osm::col, Settings::PieceColors[field[FieldSize.y - y - 1][x]])
                    );
                }
            }
        }
    }    
    Canvas.refresh();

    DrawTime(time);
    osm::cout << std::flush;
}

void TerminalDrawer::DrawTime(int ms) {
    static int sumTimes = 0;
    static int calculationsCount = 0;
    if (ms != NOT_GIVEN) {
        LastTimeMs = ms;
        ++calculationsCount;
        sumTimes += ms;
    }
    if (LastTimeMs == NOT_GIVEN) {
        return;
    }

    osm::cout << "      " << TimeMsToString(LastTimeMs) << "\n"
              << "mean: " << TimeMsToString(sumTimes / calculationsCount) << "\n";
}

void TerminalDrawer::ClearScreen() {
    system("clear");
    Canvas.clear();
}
    
TerminalDrawer::~TerminalDrawer() {
    osm::OPTION(osm::CURSOR::ON);
}

