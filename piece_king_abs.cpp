#include "piece_king_abs.h"

KingFigure::KingFigure(const char team[], const int position_x, const int position_y) : MyOwnAbstractPiece("King", team,
                                                                                                           position_x,
                                                                                                           position_y,
                                                                                                           8) {}

int KingFigure::Move(const int &position) {
    return 1;
}

int *KingFigure::CalculatingPossibleMoves() {
    int current_position = ((position_y * 10) + position_x);
    possible_moves[0] = current_position - ONE_SQUARE_Y;
    possible_moves[1] = current_position - ONE_SQUARE_Y + ONE_SQUARE_X;
    possible_moves[2] = current_position - ONE_SQUARE_Y - ONE_SQUARE_X;

    possible_moves[3] = current_position + ONE_SQUARE_X;
    possible_moves[4] = current_position - ONE_SQUARE_X;

    possible_moves[5] = current_position + ONE_SQUARE_Y;
    possible_moves[6] = current_position + ONE_SQUARE_Y + ONE_SQUARE_X;
    possible_moves[7] = current_position + ONE_SQUARE_Y - ONE_SQUARE_X;
    for (int i = 0; i < amount_of_possible_moves; ++i) {
        if (possible_moves[i] % 10 > 7 || possible_moves[i] / 10 > 7)
            possible_moves[i] = -1;

    }
    return possible_moves;
}