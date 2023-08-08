# include "piece_bishop_abs.h"

BishopFigure::BishopFigure(const char team[], const int position_x, const int position_y) : MyOwnAbstractPiece("Bishop",
                                                                                                               team,
                                                                                                               position_x,
                                                                                                               position_y,
                                                                                                               32) {}

int *BishopFigure::CalculatingPossibleMoves() {
    int current_position = ((position_y * 10) + position_x);
    // Высчитываем кол-во возможных движений по правой верхней диагонали
    possible_moves[0] = current_position - ONE_SQUARE_Y + ONE_SQUARE_X;
    for (int i = 1; i < 8; ++i) { possible_moves[i] = possible_moves[i - 1] - ONE_SQUARE_Y + ONE_SQUARE_X; }
    // Высчитываем кол-во возможных движений по левой верхней диагонали
    possible_moves[8] = current_position - ONE_SQUARE_Y - ONE_SQUARE_X;
    for (int i = 9; i < 16; ++i) { possible_moves[i] = possible_moves[i - 1] - ONE_SQUARE_Y - ONE_SQUARE_X; }

    // Высчитываем кол-во возможных движений по правой нижней диагонали
    possible_moves[16] = current_position + ONE_SQUARE_Y + ONE_SQUARE_X;
    for (int i = 17; i < 24; ++i) { possible_moves[i] = possible_moves[i - 1] + ONE_SQUARE_Y + ONE_SQUARE_X; }
    // Высчитываем кол-во возможных движений по левой нижней диагонали
    possible_moves[25] = current_position + ONE_SQUARE_Y - ONE_SQUARE_X;
    for (int i = 26; i < 32; ++i) { possible_moves[i] = possible_moves[i - 1] + ONE_SQUARE_Y - ONE_SQUARE_X; }


    // Проверяем значения правой верхней диагонали
    for (int i = 0; i < 8; ++i) {
        if (possible_moves[i] % 10 > 7 || possible_moves[i] / 10 > 7 || possible_moves[i] < 0) {
            for (int j = i; j < 8; ++j) {
                possible_moves[j] = -1;

            }
            break;
        }
    }
    // Проверяем значения левой верхней диагонали
    for (int i = 8; i < 16; ++i) {
        if (possible_moves[i] % 10 > 7 || possible_moves[i] / 10 > 7|| possible_moves[i] < 0) {
            for (int j = i; j < 16; ++j) {
                possible_moves[j] = -1;

            }
            break;
        }
    }
    // Проверяем значения правой нижней диагонали
    for (int i = 16; i < 24; ++i) {
        if (possible_moves[i] % 10 > 7 || possible_moves[i] / 10 > 7|| possible_moves[i] < 0) {
            for (int j = i; j < 24; ++j) {
                possible_moves[j] = -1;

            }
            break;
        }
    }
    // Проверяем значения левой нижней диагонали
    for (int i = 24; i < 32; ++i) {
        if (possible_moves[i] % 10 > 7 || possible_moves[i] / 10 > 7|| possible_moves[i] < 0) {
            for (int j = i; j < 24; ++j) {
                possible_moves[j] = -1;

            }
            break;
        }
    }
    return possible_moves;

}
