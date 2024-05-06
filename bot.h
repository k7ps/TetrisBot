#ifndef BOT_H
#define BOT_H

#include "piece.h"
#include "point.h"
#include "field.h"

#include <deque>
#include <stdio.h>
#include <omp.h>

#include <vector>

struct Bot {
    static PiecePosition GetBestPiecePosition(const Field&, PieceType, const std::deque<PieceType>&);
};



#endif // BOT_H