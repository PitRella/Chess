#pragma once

#ifndef KINGFIGURE_H
#define KINGFIGURE_H

#include "piece_abs.h"

class KingFigure : public MyOwnAbstractPiece{
public:
    KingFigure(const char team[], const int position_x ,const int position_y);
    int Move(const int& position) override;
    int *CalculatingPossibleMoves() override;
};

#endif /* KINGFIGURE_H */
