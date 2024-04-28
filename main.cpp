#include "field.h"

#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <string>

#include <osmanip/utility/options.hpp>
#include <osmanip/utility/iostream.hpp>
#include <osmanip/manipulators/colsty.hpp>
#include <osmanip/graphics/canvas.hpp>

const std::vector<std::string> colors = {
    "black",
    "bg red",
    "bg white",
    "bg purple",
    "bg green",
    "bg blue",
    "bg orange",
    "bg cyan"
};

int main(int argc, char* argv[]) {
    const Point field_size(10, 20);
    const Point symbol_size(2, 1);

    Field field(field_size);
    
    osm::Canvas canvas(field_size.x*symbol_size.x+2, field_size.y*symbol_size.y+2);
    canvas.enableFrame(true);
    canvas.setFrame(osm::FrameStyle::BOX);

    std::vector<PieceType> a = {PieceType::I, PieceType::Z, PieceType::O, PieceType::Z, PieceType::T, PieceType::S, PieceType::L};
    std::vector<Point> b = {Point(0,0), Point(3,0), Point(0,1), Point(5,0), Point(7,0), Point(0,3), Point(2,1)};

    osm::OPTION(osm::CURSOR::OFF);

    for (int i=0; i<=a.size(); i++) {
        system("clear");
        canvas.clear();
        for (int y = 0; y < field_size.y; y++) {
            for (int x = 0; x < field_size.x; x++) {
                for (int kx = 0; kx < symbol_size.x; kx++) {
                    for (int ky = 0; ky < symbol_size.y; ky++) {
                        canvas.put(
                            x * symbol_size.x + kx + 1, 
                            y * symbol_size.y + ky + 1, 
                            ' ',
                            osm::feat(osm::col, colors[field[field_size.y - y - 1][x]])
                        );
                    }
                }
            }
        }    
        canvas.refresh();
        osm::cout << std::flush;
        sleep(1);

        if (field.ClearFilledLines())
            i--;
        if (i < a.size())
            field.Put(b[i], CreatePiece(a[i]));
    }

    osm::OPTION(osm::CURSOR::ON);
}

