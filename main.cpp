#include "tetris.h"

#include <iostream>
#include <csignal>
#include <exception>


struct ProgramStoppedException {};

int main() {
    std::signal(SIGTSTP, [](int) {
        throw ProgramStoppedException();
    });

    try {
        Tetris tetris;
        tetris.Play();
    } catch (ProgramStoppedException err) {
        std::cout << "\rProgram was stopped\n";
    } 

    return 0;
}

