#include "tetris.h"

#include <iostream>
#include <csignal>
#include <exception>


struct ProgrammStoppedException {};

int main() {
    std::signal(SIGTSTP, [](int) {
        throw ProgrammStoppedException();
    });

    try {
        Tetris tetris;
        tetris.Play();
    } catch (ProgrammStoppedException err) {
        std::cout << "\rProgramm was stopped\n";
    } 

    return 0;
}

