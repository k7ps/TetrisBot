#ifndef BOT_H
#define BOT_H

#include "piece.h"
#include "field.h"

#include <deque>


class Bot {
public:
    static PiecePosition GetBestPiecePosition(const Field&, PieceType, std::deque<PieceType>);
};


#endif // BOT_H