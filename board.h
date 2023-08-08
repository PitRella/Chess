//
// Created by User on 5/6/2023.
//
#pragma once
#ifndef CHESSMEALL_BOARD_H
#define CHESSMEALL_BOARD_H

#include "White_team.h"
#include "Black_team.h"

class Board {
    int __square[8][8]{};
    MyOwnAbstractPiece *figures[32];
    BlackTeam *black_player;
    WhiteTeam *white_player;

    int FindPiece(const int &position_x, const int &position_y);

    int *CalculatePossiblePositions(const int &current_position_X, const int &current_position_Y, const int &index);

    void ChangePosition(const int &old_position_X, const int &old_position_Y, const int &next_position_X,

                        const int &next_position_Y,
                        const int index
    );
    void PrintWhiteTeamScore();

    void PrintBlackTeamScore();
public:
    Board(WhiteTeam &white_player, BlackTeam &black_player);




    ~Board();

    void PrintBoard();

    bool IsPositionFree(const int &position_X, const int &position_Y);

    bool
    FindNewPositionInPossiblesPositions(const int *possible_positions, const int &nex_position_X,
                                        const int &_nextposition_Y, const int &index);

    int makeMove(const int &current_position_X, const int &current_position_Y, const int &next_position_X,
                 const int &next_position_Y);
    int makeAIMove();
    bool IsEnemy(const int &current_team, const int &index);

    void CheckPossiblePositions(int *possible_positions, const int &index);

    int WhichTeam(const int &current_position_X, const int &current_position_Y);


    int FindClosestCoordinate(int current_closest, int maybe_next_closest, int king_coord);
    int* FindBestFigure();
    int FindBestMoveForFigure(int current_position_X, int current_position_Y, int index);
    int GetWhiteTeamScore();
    int GetBlackTeamScore();

};


#endif //CHESSMEALL_BOARD_H
