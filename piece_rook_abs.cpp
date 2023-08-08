#include "piece_rook_abs.h"

RookFigure::RookFigure(const char team[], const int position_x, const int position_y) : MyOwnAbstractPiece("Rook", team,
                                                                                                           position_x,
                                                                                                           position_y,
                                                                                                           32) {}

int RookFigure::Move(const int &position) {

}

int *RookFigure::CalculatingPossibleMoves() {
    for (int i = 0; i < amount_of_possible_moves; ++i) possible_moves[i] = -1;
    // C 0 ДО 7 элемента идут клетки вверх
    // С 8 ДО 15 элемента идут клетки вниз
    // С 16 ДО 23 элемента идут клетки влево
    // С 24 ДО 31 элемента идут клетки вправо
    //Считаем сколько у нас есть возможных ходов вверх
    if ((position_y - 1) >= 0) {
        possible_moves[0] = ((position_y * 10) + position_x) - ONE_SQUARE_Y;
        for (int i = 1; i < 8-(8 - position_y); ++i) {
            possible_moves[i] = possible_moves[i-1] - ONE_SQUARE_Y;
        }
    }
    //Считаем сколько у нас есть возможных ходов вниз
    if ((position_y + 1) < 8) {
        possible_moves[8] = ((position_y * 10) + position_x) + ONE_SQUARE_Y;
        for (int i = 9; i < (8 - position_y - 1) + 8; ++i) {
            possible_moves[i] = possible_moves[i-1] + ONE_SQUARE_Y;
        }
    }
    //Считаем сколько у нас есть возможных ходов влево
    if((position_x - 1) >= 0)
    {
        possible_moves[16] = ((position_y * 10) + position_x) - ONE_SQUARE_X;
        for (int i = 17; i < 8 - (8 - position_x) + 16; ++i) {
            possible_moves[i] = possible_moves[i-1] - ONE_SQUARE_X;
        }
    }
    //Считаем сколько у нас есть возможных ходов вправо
    if((position_x + 1) < 8)
    {
        possible_moves[24] = ((position_y * 10) + position_x) + ONE_SQUARE_X;
        for (int i = 25; i < (8 - position_x - 1) + 24; ++i) {
            possible_moves[i] = possible_moves[i-1] + ONE_SQUARE_X;
        }
    }


    return possible_moves;

}
