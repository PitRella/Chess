#include "piece_knight_abs.h"

KnightFigure::KnightFigure(const char team[], const int position_x, const int position_y) : MyOwnAbstractPiece("Knight",
                                                                                                               team,
                                                                                                               position_x,
                                                                                                               position_y,
                                                                                                               8) {}
int KnightFigure::Move(const int &position) {
    return 1;
}


int *KnightFigure::CalculatingPossibleMoves() {
    int my_position = ((GetPositionY() * 10) + GetPositionX());
    // 0, 1 - Движение коня вверх
    possible_moves[0] = my_position - ONE_SQUARE_Y - ONE_SQUARE_Y + ONE_SQUARE_X; // Вверх-вправо
    possible_moves[1] = my_position - ONE_SQUARE_Y - ONE_SQUARE_Y - ONE_SQUARE_X; // Вверх-влево
    if (possible_moves[0] < 0) possible_moves[0] = -1;
    if (possible_moves[1] < 0) possible_moves[1] = -1;


    // 2, 3 - Движение коня вниз
    possible_moves[2] = my_position + ONE_SQUARE_Y + ONE_SQUARE_Y + ONE_SQUARE_X; // Вниз-вправо
    possible_moves[3] = my_position + ONE_SQUARE_Y + ONE_SQUARE_Y - ONE_SQUARE_X; // Вниз-влево
    if (possible_moves[2] > 77) possible_moves[2] = -1;
    if (possible_moves[3] > 77) possible_moves[3] = -1;


    // 4, 5 - Движение коня влево
    possible_moves[4] = my_position - ONE_SQUARE_X - ONE_SQUARE_X + ONE_SQUARE_Y; // Влево-вверх
    possible_moves[5] = my_position - ONE_SQUARE_X - ONE_SQUARE_X - ONE_SQUARE_Y; // Влево-вниз
    if ((possible_moves[4] % 10 > 7) || possible_moves[4] < 0) possible_moves[4] = -1;
    if (possible_moves[5] % 10 > 7 || possible_moves[5] < 0) possible_moves[5] = -1;


    // 6, 7 - Движение коня вправо
    possible_moves[6] = my_position + ONE_SQUARE_X + ONE_SQUARE_X + ONE_SQUARE_Y; // Вправо-вверх
    possible_moves[7] = my_position + ONE_SQUARE_X + ONE_SQUARE_X - ONE_SQUARE_Y; // Вправо-вниз
    if (possible_moves[6] / 10 > 7 || possible_moves[6] < 0) possible_moves[6] = -1;
    if (possible_moves[7] / 10 > 7 || possible_moves[6] < 0) possible_moves[7] = -1;

    return possible_moves;

}
