#pragma once

#ifndef BISHOPFIGURE_H
#define BISHOPFIGURE_H

#include "piece_abs.h"

class BishopFigure : public MyOwnAbstractPiece {
public:
    BishopFigure(const char team[], const int position_x ,const int position_y);
    int *CalculatingPossibleMoves() override;

};

#endif /* BISHOPFIGURE_H */