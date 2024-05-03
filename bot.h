#ifndef BOT_H
#define BOT_H

#include "piece.h"
#include "point.h"
#include "field.h"

#include <queue>

#include <vector>

struct Bot {
    Bot() {};
    static PiecePosition GetBestPiecePosition(Field&, PieceType, const std::queue<PieceType>&);
};



#endif // BOT_H