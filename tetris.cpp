#include "tetris.h"
#include "settings.h"
#include "bot.h"

#include <chrono>
#include <ctime>
#include <stdlib.h>
#include <thread>


namespace {
    
    PieceType GetRandomPiece() {
        return static_cast<PieceType>(1 + rand() % 7);
    }

    int64_t GetCurrentTime() {
        using namespace std::chrono;

        auto now = system_clock::now();
        auto now_ms = time_point_cast<milliseconds>(now);
        return now_ms.time_since_epoch().count();
    }

}

Tetris::Tetris()
    : TetrisField(Settings::FieldSize)
    , Drawer(Settings::FieldSize, Settings::PixelSize)
{
    srandom(time(0));

    for (int i = 0; i < Settings::KnownPiecesCount; i++) {
        NextPieces.push_back(GetRandomPiece());
    }
}

void Tetris::Play() {
    DrawFrame();

    while (true) {

        NextPieces.push_back(GetRandomPiece());

        Drawer.UpdateNextPieces(NextPieces);
        DrawFrame();

        auto curPiece = NextPieces.front();
        NextPieces.pop_front();

        Drawer.UpdateNextPieces(NextPieces);

        TetrisField.PutAtStart(curPiece);
        DrawFrame();

        auto startTime = GetCurrentTime();
        auto piecePosition = Bot::GetBestPiecePosition(TetrisField, curPiece, NextPieces);
        auto endTime = GetCurrentTime();
        
        TetrisField.EraseLastAddedPiece();
        TetrisField.Put(piecePosition);
        
        Drawer.UpdateCalculationTime(endTime - startTime);
        DrawFrame();

        if (TetrisField.ClearFilledLines()) {
            Drawer.UpdateLineCount(TetrisField.GetLineCount());
            DrawFrame();
        }
    }
}

void Tetris::DrawFrameWithoutWait() {
    Drawer.DrawFrame(TetrisField);
}

void Tetris::DrawFrame() {
    DrawFrameWithoutWait();
    std::this_thread::sleep_for(std::chrono::milliseconds(Settings::FrameTime));
}