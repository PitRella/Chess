#pragma once

#ifndef QUEEN_FIGURE_H
#define QUEEN_FIGURE_H

#include "piece_abs.h"

class QueenFigure : public MyOwnAbstractPiece {
public:
    QueenFigure(const char team[], const int position_x ,const int position_y);
    int Move(const int& position) override;
    int *CalculatingPossibleMoves() override;
};

#endif // QUEEN_FIGURE_H