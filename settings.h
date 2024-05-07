#ifndef SETTINGS_H
#define SETTINGS_H

#include "point.h"

#include <string>
#include <vector>


namespace Settings {

    const Point FieldSize(10, 20);
    const Point PixelSize(2, 1);

    const int KnownPiecesCount = 2;
    
    const int FrameTime = 500; // ms

    const std::vector<std::string> PieceColors = {
        "black",
        "bg red",
        "bg white",
        "bg purple",
        "bg green",
        "bg blue",
        "bg orange",
        "bg cyan"
    };

}

#endif // SETTINGS_H
