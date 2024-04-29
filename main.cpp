#include "field.h"
#include "drawer.h"
#include "settings.h"

#include <unistd.h>
#include <vector>
#include <string>
#include <ctime>
#include <stdlib.h>
#include <chrono>
#include <thread>


int main(int argc, char* argv[]) {
    srandom(time(0));

    Field field(Settings::FieldSize);
    TerminalDrawer drawer(Settings::FieldSize, Settings::PixelSize); 

    std::vector<PieceType> a = {
        PieceType::I, PieceType::Z, PieceType::O, PieceType::Z, PieceType::T, PieceType::S, PieceType::L};
    std::vector<Point> b = {
        Point(0,0), Point(3,0), Point(0,1), Point(5,0), Point(7,0), Point(0,3), Point(2,1)};

    auto drawFrame = [&drawer, &field](int time = NOT_GIVEN) {
        drawer.DrawFrame(field, time);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    };

    drawFrame();

    for (int i=0; i<a.size(); i++) {
        auto piece = CreatePiece(a[i]);

        field.PutAtStart(piece);
        drawFrame();

        field.EraseFromStart();
        field.Put(b[i], piece);
        drawFrame(500 + rand() % 1500);

        if (field.ClearFilledLines()) {
            drawFrame();
        }
    }

    return 0;
}

