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
    DrawScreen();

    while (true) {
        auto currPiece = NextPieces.front();
        NextPieces.pop_front();
        NextPieces.push_back(GetRandomPiece());

        if (!TetrisField.PutAtStart(currPiece)) {
            Drawer.DrawGameOverScreen(TetrisField);
            break;
        }
        Drawer.UpdateNextPieces(NextPieces);
        DrawScreen();

        TetrisField.EraseLastAddedPiece();

        auto startTime = GetCurrentTime();
        auto piecePosition = Bot::GetBestPiecePosition(TetrisField, currPiece, NextPieces);
        auto endTime = GetCurrentTime();
        
        TetrisField.Put(piecePosition);
        
        Drawer.UpdateCalculationTime(endTime - startTime);
        DrawScreen();

        if (TetrisField.ClearFilledLines()) {
            Drawer.UpdateLineCount(TetrisField.GetLineCount());
            DrawScreen();
        }
    }
}

void Tetris::DrawScreenWithoutWait() {
    Drawer.DrawScreen(TetrisField);
}

void Tetris::DrawScreen() {
    DrawScreenWithoutWait();
    std::this_thread::sleep_for(std::chrono::milliseconds(Settings::FrameTime));
}

