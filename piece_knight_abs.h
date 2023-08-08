#pragma once

#ifndef KNIGHT_FIGURE_H
#define KNIGHT_FIGURE_H

#include "piece_abs.h"


class KnightFigure : public MyOwnAbstractPiece {
public:
    KnightFigure(const char team[], const int position_x ,const int position_y);
    int Move(const int& position) override;
    int *CalculatingPossibleMoves() override;

};

#endif /* KNIGHT_FIGURE_H */
