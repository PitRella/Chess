#pragma once
#ifndef CHESSMEALL_WHITE_TEAM_H
#define CHESSMEALL_WHITE_TEAM_H
#include "Team_abs.h"

class WhiteTeam : public AbstractTeam {
public:
    WhiteTeam();
    void ChangePawnIntoAnotherFigure(const int &position_y, const int &position_x);
};
#endif //CHESSMEALL_WHITE_TEAM_H
