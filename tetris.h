#ifndef TETRIS_H
#define TETRIS_H

#include "drawer.h"
#include "field.h"
#include "piece.h"

#include <queue>


class Tetris {
public:
    Tetris();

    void Play();

    void DrawFrame(int64_t time = NOT_GIVEN);
    void DrawFrameWithoutWait(int64_t time = NOT_GIVEN);

private:
    Field TetrisField;
    TerminalDrawer Drawer;
    std::queue<PieceType> NextPieces;
};

#endif 
