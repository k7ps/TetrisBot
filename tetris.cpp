#include "tetris.h"
#include "settings.h"
#include "bot.h"

#include <chrono>
#include <ctime>
#include <stdlib.h>
#include <thread>


namespace {
    
    PieceType GetRandomPiece() {
        return static_cast<PieceType>(rand() % 7);
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
        auto curPiece = NextPieces.front();
        NextPieces.pop_front();
        NextPieces.push_back(GetRandomPiece());

        TetrisField.PutAtStart(curPiece);
        DrawFrameWithoutWait();

        auto startTime = GetCurrentTime();
        auto piecePosition = Bot::GetBestPiecePosition(TetrisField, curPiece, NextPieces);
        auto endTime = GetCurrentTime();
        
        TetrisField.EraseFromStart();
        TetrisField.Put(piecePosition);
        Drawer.UpdateCalculationTime(endTime - startTime);
        DrawFrame();

        if (TetrisField.ClearFilledLines()) {
            Drawer.UpdateLineCount(TetrisField.GetLineCount());
            DrawFrame();
        }
    }

    // std::vector<PieceType> a = {PieceType::T, PieceType::T};
    // std::vector<Point> b = {
    //     Point(0,0), Point(2,1)};

    // DrawFrame();

    // for (int i=0; i<a.size(); i++) {
    //     TetrisField.PutAtStart(a[i]);
    //     DrawFrame();

    //     TetrisField.EraseFromStart();
    //     TetrisField.Put(b[i], GetPiece(a[i], 2));
    //     Drawer.UpdateCalculationTime(500 + rand() % 1500);
    //     DrawFrame();

    //     if (TetrisField.ClearFilledLines()) {
    //         Drawer.UpdateLineCount(TetrisField.GetLineCount());
    //         DrawFrame();
    //     }
    //     
    // }
}

void Tetris::DrawFrameWithoutWait() {
    Drawer.DrawFrame(TetrisField);
}

void Tetris::DrawFrame() {
    DrawFrameWithoutWait();
    std::this_thread::sleep_for(std::chrono::milliseconds(Settings::FrameTime));
}

