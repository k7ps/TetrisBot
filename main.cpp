#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <string>

#include <osmanip/utility/options.hpp>
#include <osmanip/utility/iostream.hpp>
#include <osmanip/manipulators/colsty.hpp>
#include <osmanip/graphics/canvas.hpp>

struct Point {
    Point(int _x, int _y) 
        : x{_x}, y{_y} {}

    int x = 0;
    int y = 0;
};

const std::vector<std::string> colors = {
    "black",
    "bg red",
    "bg green",
    "bg lt purple"
};

int main(int argc, char* argv[]) {
    const Point field_size(4,4);
    const Point symbol_size(2,1);

    std::vector<std::vector<std::vector<int8_t>>> fields(4);
    fields[0] = {
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0}
    };
    fields[1] = {
        {0,0,0,0},
        {0,0,0,0},
        {0,1,0,0},
        {1,1,1,0}
    };
    fields[2] = {
        {0,0,0,0},
        {2,2,2,0},
        {2,1,0,0},
        {1,1,1,0}
    };
    fields[3] = {
        {0,0,0,3},
        {2,2,2,3},
        {2,1,0,3},
        {1,1,1,3}
    };
    
    osm::Canvas canvas(field_size.x*symbol_size.x+2, field_size.y*symbol_size.y+2);
    canvas.enableFrame(true);
    canvas.setFrame(osm::FrameStyle::BOX);

    std::cout << std::endl;

    //osm::OPTION(osm::CURSOR::OFF);

    for (auto field : fields) {
        canvas.clear();
        for (int x=0; x<field_size.x; x++) {
            for (int y=0; y<field_size.y; y++) {
                for (int kx=0; kx<symbol_size.x; kx++) {
                    for (int ky=0; ky<symbol_size.y; ky++) {
                        canvas.put(x*symbol_size.x+kx+1, y*symbol_size.y+ky+1, ' ', osm::feat(osm::col, colors[field[y][x]]));
                    }
                }
            }
        }    
        canvas.refresh();
        osm::cout << std::flush;
        sleep(1);
    }

    //osm::OPTION(osm::CURSOR::ON);
}

