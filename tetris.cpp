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
        //DrawFrame();

        auto curPiece = NextPieces.front();
        NextPieces.pop_front();

        //Drawer.UpdateNextPieces(NextPieces);

        //TetrisField.PutAtStart(curPiece);
        //DrawFrame();
        DrawFrameWithoutWait();

        auto startTime = GetCurrentTime();
        auto piecePosition = Bot::GetBestPiecePosition(TetrisField, curPiece, NextPieces);
        auto endTime = GetCurrentTime();
        
        //TetrisField.EraseLastAddedPiece();
        TetrisField.Put(piecePosition);
        
        Drawer.UpdateCalculationTime(endTime - startTime);
        DrawFrame();

        if (TetrisField.ClearFilledLines()) {
            Drawer.UpdateLineCount(TetrisField.GetLineCount());
            DrawFrame();
        }
    }

    // std::vector<PieceType> a = {
    //     PieceType::I, PieceType::Z, PieceType::O, PieceType::Z, PieceType::T, PieceType::S, PieceType::L};
    // std::vector<Point> b = {
    //     Point(0,0), Point(3,0), Point(0,1), Point(5,0), Point(7,0), Point(0,3), Point(2,1)};

    // NextPieces.clear();
    // for (int i=0; i < Settings::KnownPiecesCount; i++)
    //    NextPieces.push_back(a[i]); 

    // Drawer.UpdateNextPieces(NextPieces);
    // DrawFrame();

    // for (int i=0; i<a.size(); i++) {
    //     NextPieces.pop_front();
    //     if (i + Settings::KnownPiecesCount < a.size())
    //         NextPieces.push_back(a[i + Settings::KnownPiecesCount]);
    //     Drawer.UpdateNextPieces(NextPieces);

    //     TetrisField.PutAtStart(a[i]);
    //     DrawFrame();

    //     TetrisField.EraseLastAddedPiece();
    //     TetrisField.Put(PiecePosition(b[i], a[i]));
    //     Drawer.UpdateCalculationTime(500 + rand() % 1500);
    //     DrawFrame();

    //     if (TetrisField.ClearFilledLines()) {
    //         Drawer.UpdateLineCount(TetrisField.GetLineCount());
    //         DrawFrame();
    //     }
    // }

    // TetrisField.EraseLastAddedPiece();
    // DrawFrame();
}

void Tetris::DrawFrameWithoutWait() {
    Drawer.DrawFrame(TetrisField);
}

void Tetris::DrawFrame() {
    DrawFrameWithoutWait();
    std::this_thread::sleep_for(std::chrono::milliseconds(Settings::FrameTime));
}

