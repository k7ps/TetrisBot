#include "tetris.h"

#include <iostream>
#include <csignal>
#include <exception>


struct ProgramStoppedException {};

int main() {
    /*osm::Canvas c(5,5);
    for (int i=0;i<5;i++){
        c.clear();
        system("clear");
        osm::cout << "123123123\n" << std::flush;
        for (int y=0;y<5;y++)
            for(int x=0;x<5;x++)
                c.put(x,y,'0'+i);
        c.refresh();
        osm::cout << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    return 0;*/


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

