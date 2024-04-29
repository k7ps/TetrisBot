#include "field.h"
#include "drawer.h"

#include <unistd.h>
#include <vector>
#include <string>
#include <ctime>
#include <stdlib.h>


int main(int argc, char* argv[]) {
    srandom(time(0));

    const Point fieldSize(10, 20);
    const Point pixelSize(2, 1);

    Field field(fieldSize);
    TerminalDrawer drawer(fieldSize, pixelSize); 

    std::vector<PieceType> a = {PieceType::I, PieceType::Z, PieceType::O, PieceType::Z, PieceType::T, PieceType::S, PieceType::L};
    std::vector<Point> b = {Point(0,0), Point(3,0), Point(0,1), Point(5,0), Point(7,0), Point(0,3), Point(2,1)};

    for (int i=0; i<=a.size(); i++) {
        drawer.DrawFrame(field, 500 + rand() % 2000);
        sleep(1);

        if (field.ClearFilledLines())
            i--;
        if (i < a.size())
            field.Put(b[i], CreatePiece(a[i]));
    }

    return 0;
}

