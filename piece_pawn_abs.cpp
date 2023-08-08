#include "piece_pawn_abs.h"


PawnFigure::PawnFigure(const char team[], const int position_x ,const int position_y) : MyOwnAbstractPiece("Pawn", team, position_x, position_y, 4) {}
PawnFigure::~PawnFigure() { delete[] possible_moves; }

int PawnFigure::Move(const int &position) {


}

int* PawnFigure::CalculatingPossibleMoves() {
    switch (team) {
        case 8:
            possible_moves[0] = ((position_y * 10) + position_x) + ONE_SQUARE_Y + ONE_SQUARE_Y;// Первый ход - возможен на 2 клетки
            possible_moves[1] = ((position_y * 10) + position_x) + ONE_SQUARE_Y; // Обычное движение
            possible_moves[2] = ((position_y * 10) + position_x) + ONE_SQUARE_Y + ONE_SQUARE_X; // ход по диагонали
            if(possible_moves[2]%10>7 || possible_moves[2]%10<0 || possible_moves[2]/10>7 ||possible_moves[2]/10<0)
                possible_moves[2]=-1;
            possible_moves[3] = ((position_y * 10) + position_x) + ONE_SQUARE_Y - ONE_SQUARE_X;
            if(possible_moves[3]%10>7 || possible_moves[3]%10<0 || possible_moves[3]/10>7 ||possible_moves[3]/10<0)
                possible_moves[3]=-1;
            break;
        case 16: // Ход белых
            possible_moves[0] = ((position_y * 10) + position_x) - ONE_SQUARE_Y - ONE_SQUARE_Y;// Первый ход - возможен на 2 клетки
            possible_moves[1] = ((position_y * 10) + position_x) - ONE_SQUARE_Y; // Обычное движение
            possible_moves[2] = ((position_y * 10) + position_x) - ONE_SQUARE_Y + ONE_SQUARE_X; // ход по диагонали
            if(possible_moves[2]%10>7 || possible_moves[2]%10<0 || possible_moves[2]/10>7 ||possible_moves[2]/10<0)
                possible_moves[2]=-1;
            possible_moves[3] = ((position_y * 10) + position_x) - ONE_SQUARE_Y - ONE_SQUARE_X;
            if(possible_moves[3]%10>7 || possible_moves[3]%10<0 || possible_moves[3]/10>7 ||possible_moves[3]/10<0)
                possible_moves[3]=-1;

            break;


    }

    return possible_moves;


}
