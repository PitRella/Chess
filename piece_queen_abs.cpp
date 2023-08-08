#include "piece_queen_abs.h"


QueenFigure::QueenFigure(const char team[], const int position_x ,const int position_y) : MyOwnAbstractPiece("Queen", team, position_x,position_y, 64) {}

int QueenFigure::Move(const int &position) {
}

int* QueenFigure::CalculatingPossibleMoves() {
    // Реализовываем движения ладьи с 0 по 31 элемент массива possible_moves
    for (int i = 0; i < 64; ++i) possible_moves[i] = -1;
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
    // Реализовываем движения слона с 31 по 63 элементи массива possible_moves
    int current_position = ((position_y * 10) + position_x);
    // Высчитываем кол-во возможных движений по правой верхней диагонали
    possible_moves[32] = current_position - ONE_SQUARE_Y + ONE_SQUARE_X;
    for (int i = 33; i < 40; ++i) { possible_moves[i] = possible_moves[i - 1] - ONE_SQUARE_Y + ONE_SQUARE_X; }
    // Высчитываем кол-во возможных движений по левой верхней диагонали
    possible_moves[40] = current_position - ONE_SQUARE_Y - ONE_SQUARE_X;
    for (int i = 41; i < 48; ++i) { possible_moves[i] = possible_moves[i - 1] - ONE_SQUARE_Y - ONE_SQUARE_X; }

    // Высчитываем кол-во возможных движений по правой нижней диагонали
    possible_moves[48] = current_position + ONE_SQUARE_Y + ONE_SQUARE_X;
    for (int i = 49; i < 56; ++i) { possible_moves[i] = possible_moves[i - 1] + ONE_SQUARE_Y + ONE_SQUARE_X; }
    // Высчитываем кол-во возможных движений по левой нижней диагонали
    possible_moves[56] = current_position + ONE_SQUARE_Y - ONE_SQUARE_X;
    for (int i = 57; i < 64; ++i) { possible_moves[i] = possible_moves[i - 1] + ONE_SQUARE_Y - ONE_SQUARE_X; }


    // Проверяем значения правой верхней диагонали
    for (int i = 32; i < 40; ++i) {
        if (possible_moves[i] % 10 > 7 || possible_moves[i] / 10 > 7||possible_moves[i]<0) {
            for (int j = i; j < 40; ++j) {
                possible_moves[j] = -1;

            }
            break;
        }
    }
    // Проверяем значения левой верхней диагонали
    for (int i = 40; i < 48; ++i) {
        if (possible_moves[i] % 10 > 7 || possible_moves[i] / 10 > 7||possible_moves[i]<0) {
            for (int j = i; j < 48; ++j) {
                possible_moves[j] = -1;

            }
            break;
        }
    }
    // Проверяем значения правой нижней диагонали
    for (int i = 48; i < 56; ++i) {
        if (possible_moves[i] % 10 > 7 || possible_moves[i] / 10 > 7||possible_moves[i]<0) {
            for (int j = i; j < 56; ++j) {
                possible_moves[j] = -1;

            }
            break;
        }
    }
    // Проверяем значения левой нижней диагонали
    for (int i = 56; i < 64; ++i) {
        if (possible_moves[i] % 10 > 7 || possible_moves[i] / 10 > 7 ||possible_moves[i]<0 ) {
            for (int j = i; j < 64; ++j) {
                possible_moves[j] = -1;

            }
            break;
        }
    }
    return possible_moves;
}

