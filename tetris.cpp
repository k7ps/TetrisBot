#include "tetris.h"
#include "settings.h"

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
        NextPieces.push(GetRandomPiece());
    }
}

void Tetris::Play() {
    /*while (true) {
        PieceType curPiece = NextPieces.front();
        NextPiece.pop();
        NextPiece.push(GetRandomPiece());

        TetrisField.PutAtStart(curPiece);
        DrawFrameWithoutWait();

        auto startTime = GetCurrentTime();
        Point pos = Bot.GetBestPos(TetrisField, curPiece, NextPieces);
        auto endTime = GetCurrentTime();
        
        TetrisField.EraseFromStart();
        TetrisField.Put(pos, piece);
        DrawFrame(endTime - startTime);

        if (TetrisField.ClearFilledLines) {
            DrawFrame();
        }
    }*/

    std::vector<PieceType> a = {
        PieceType::I, PieceType::Z, PieceType::O, PieceType::Z, PieceType::T, PieceType::S, PieceType::L};
    std::vector<Point> b = {
        Point(0,0), Point(3,0), Point(0,1), Point(5,0), Point(7,0), Point(0,3), Point(2,1)};

    DrawFrame();

    for (int i=0; i<a.size(); i++) {
        auto piece = CreatePiece(a[i]);

        TetrisField.PutAtStart(piece);
        DrawFrame();

        TetrisField.EraseFromStart();
        TetrisField.Put(b[i], piece);
        DrawFrame(500 + rand() % 1500);

        if (TetrisField.ClearFilledLines()) {
            DrawFrame();
        }
    }
}

void Tetris::DrawFrameWithoutWait(int64_t time) {
    Drawer.DrawFrame(TetrisField, time);
}

void Tetris::DrawFrame(int64_t time) {
    DrawFrameWithoutWait(time);
    std::this_thread::sleep_for(std::chrono::milliseconds(Settings::FrameTime));
}

