#ifndef TETRIS_H
#define TETRIS_H

#include "drawer.h"
#include "field.h"
#include "piece.h"

#include <deque>


class Tetris {
public:
    Tetris();

    void Play();

private:
    void DrawScreen();
    void DrawScreenWithoutWait();

private:
    Field TetrisField;
    TerminalDrawer Drawer;
    std::deque<PieceType> NextPieces;
};

#endif // TETRIS_H 

