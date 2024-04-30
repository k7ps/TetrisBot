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

private:
    void DrawFrame();
    void DrawFrameWithoutWait();

private:
    Field TetrisField;
    TerminalDrawer Drawer;
    std::queue<PieceType> NextPieces;
};

#endif // TETRIS_H 
