//
// Created by User on 5/4/2023.
//
#pragma once
#ifndef CHESSMEALL_BLACK_TEAM_H
#define CHESSMEALL_BLACK_TEAM_H
#include "Team_abs.h"

class BlackTeam : public AbstractTeam {
public:
    BlackTeam();
    void ChangePawnIntoAnotherFigure(const int &position_y, const int &position_x);

};
#endif //CHESSMEALL_BLACK_TEAM_H
