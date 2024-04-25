#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <string>

#include <osmanip/utility/options.hpp>
#include <osmanip/utility/iostream.hpp>

const int symbol_size = 2;
const std::string empty = "..";
const std::string fill = "██";
const std::string indent_left = "\t";
const std::string indent_up = "\n\n";

void clear_screen() {
    osm::cout << "\x1B[2J\x1B[H";
    osm::cout << std::flush;
}

void draw_field(const std::vector<std::vector<int8_t>>& field) {
    osm::cout << indent_up << indent_left << ' ';
    for (int i=0; i<field[0].size() * symbol_size; i++) osm::cout << '_';
    osm::cout << '\n';

    for (const auto& line : field) {
        osm::cout << indent_left << '|';
        for (auto symbol : line)
            osm::cout << (symbol ? fill : empty);
        osm::cout << '|' << '\n';
    }

    osm::cout << indent_left << ' ';
    for (int i=0; i<field[0].size() * symbol_size; i++) osm::cout << "¯";
    osm::cout << '\n' << std::flush;
}

int main(int argc, char* argv[]) {
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
        {1,1,1,0},
        {1,1,0,0},
        {1,1,1,0}
    };
    fields[3] = {
        {0,0,0,1},
        {1,1,1,1},
        {1,1,0,1},
        {1,1,1,1}
    };

    osm::OPTION(osm::CURSOR::OFF);
    for (const auto& field : fields) {
        clear_screen();
        draw_field(field);
        sleep(2);
    }
    osm::OPTION(osm::CURSOR::ON);
}

