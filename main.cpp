#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <string>

const int symbol_size = 2;
const std::string empty = "..";
const std::string fill = "██";
const std::string indent_left = "\t";
const std::string indent_up = "\n\n";

void clear_screen() {
    std::cout << "\x1B[2J\x1B[H";
    std::cout << std::flush;
}

void draw_field(const std::vector<std::vector<bool>>& field) {
    std::cout << indent_up;
    std::cout << indent_left << ' ';
    for (int i=0; i<field[0].size() * symbol_size; i++) std::cout << '_';
    std::cout << '\n';

    for (const auto& line : field) {
        std::cout << indent_left << '|';
        for (auto symbol : line)
            std::cout << (symbol ? fill : empty);
        std::cout << '|' << '\n';
    }

    std::cout << indent_left << ' ';
    for (int i=0; i<field[0].size() * symbol_size; i++) std::cout << "¯";
    std::cout << '\n';
    std::cout << std::flush;
}

int main(int argc, char* argv[]) {
    std::vector<std::vector<std::vector<bool>>> fields(4);
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

    for (const auto& field : fields) {
        clear_screen();
        draw_field(field);
        sleep(2);
    }
}

