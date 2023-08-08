#pragma once

#ifndef PAWNFIGURE_H
#define PAWNFIGURE_H

#include "piece_abs.h"

class PawnFigure : public MyOwnAbstractPiece {
private:
public:
    PawnFigure(const char team[], const int position_x ,const int position_y);

    ~PawnFigure();

    int Move(const int &position) override;

    int *CalculatingPossibleMoves() override;
};


#endif // PAWNFIGURE_H
