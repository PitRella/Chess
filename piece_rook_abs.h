#pragma once

#ifndef ROOK_FIGURE_H
#define ROOK_FIGURE_H

#include "piece_abs.h"

class RookFigure : public MyOwnAbstractPiece {
public:
    RookFigure(const char team[], const int position_x ,const int position_y);
    int Move(const int &position) override;
    int *CalculatingPossibleMoves() override;
};

#endif // ROOK_FIGURE_H