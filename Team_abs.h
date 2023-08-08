//
// Created by User on 5/4/2023.
//
#pragma once
#ifndef CHESSMEALL_TEAM_ABS_H
#define CHESSMEALL_TEAM_ABS_H
#include "piece_abs.h"
#include "piece_bishop_abs.h"
#include "piece_king_abs.h"
#include "piece_knight_abs.h"
#include "piece_pawn_abs.h"
#include "piece_queen_abs.h"
#include "piece_rook_abs.h"

class AbstractTeam {
protected:
    int amount_of_figures = 16;
    MyOwnAbstractPiece *own_figures[16];
    int captured_figures[16];
    int last_captured_figures=0;
public:
    int FindPiece(const int &current_position_X,const int &current_position_Y);

    ~AbstractTeam();

    int FigureWasCaptured(const int &position_y, const int &position_x);

    int CaptureEnemyFigure(const int &captured_figure_number);

    MyOwnAbstractPiece **GetMyFigures();
    int GetLastCapturedFigure();
    MyOwnAbstractPiece *GetMyFigure(const int index);
    void DeleteFigureByIndex(const int &index);
    int GetAmountOfFigures(){return amount_of_figures;}


};
#endif //CHESSMEALL_TEAM_ABS_H
