#pragma once

// Created by User on 5/3/2023.
//

#ifndef NEWCHESSGAME_PIECE_ABS_H
#define NEWCHESSGAME_PIECE_ABS_H
#define ONE_SQUARE_Y 10
#define ONE_SQUARE_X 1
#include <iostream>
constexpr unsigned int djb2Hash(const char* str, int index = 0)
{
    return !str[index] ? 0x1505 : (djb2Hash(str, index + 1) * 0x21) ^ str[index];
}
class MyOwnAbstractPiece {
public:

    MyOwnAbstractPiece();

    virtual ~

    MyOwnAbstractPiece();

    MyOwnAbstractPiece(const char figure[], const char team[], const int &x_position,const int &y_position,
                       const int &amount_of_possible_moves);

    int GetFigure() const;

    int GetTeam() const;

    int GetColor(const int &piece) const;

    int GetType(const int &piece) const;

    int GetPositionX();
    int GetPositionY();

    int GetAmountOfPossibleMoves();

    void SetPositionX(const int position_x);
    void SetPositionY(const int position_y);

    virtual int Move(const int &position);

    virtual int *CalculatingPossibleMoves();
    bool IsItFirstMove();
    void SetNotFirstMove();
    void SetFirstMove();

protected:
    bool isFirstMove=true;
    int *possible_moves;
    int amount_of_possible_moves;
    int figure;
    int team;
    int position_x;
    int position_y;
    const int blackMask = 0b10000;
    const int whiteMask = 0b01000;
    const int typeMask = 0b00111;
    const int colorMask = whiteMask | blackMask;
};

#endif //NEWCHESSGAME_PIECE_ABS_H
