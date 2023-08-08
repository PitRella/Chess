#include "board.h"
#include "ansi_color_codes.h"

Board::Board(WhiteTeam &white_player, BlackTeam &black_player) {
    this->white_player = &white_player;
    this->black_player = &black_player;
    for (int i = 0; i < 16; ++i) figures[i] = white_player.GetMyFigure(i);
    for (int i = 0; i < 16; ++i) figures[i + 16] = black_player.GetMyFigure(i);
    for (int i = 0; i < 32; i++)
        __square[figures[i]->GetPositionY()][figures[i]->GetPositionX()] =
                figures[i]->GetFigure() | figures[i]->GetTeam();

}

int Board::WhichTeam(const int &current_position_X, const int &current_position_Y) {
    figures[FindPiece(current_position_X, current_position_Y)]->GetTeam();
}

int Board::FindPiece(const int &position_x, const int &position_y) {
    for (int i = 0; i < 32; ++i) {
        if (figures[i]->GetPositionX() == position_x && figures[i]->GetPositionY() == position_y)
            return i;
    }
}

bool Board::IsEnemy(const int &current_team, const int &index) {

    if (figures[index]->GetTeam() != current_team) {
        return true;
    }
    return false;
}

void Board::CheckPossiblePositions(int *possible_moves, const int &index) {
    switch (figures[index]->GetFigure()) {
        case 2: // Пешка(Pawn)
        {
            //Идём на 2 клетки прямо. Проверки на фигуру на этой клетке смысла делать нету т.к. - первый ход
            switch (figures[index]->GetTeam()) {
                case 8:
                    if (!figures[index]->IsItFirstMove()) possible_moves[0] = -1;

                    break;
                case 16:
                    if (!figures[index]->IsItFirstMove()) possible_moves[0] = -1;

                    break;
            }
            //Проверка на наличие пустую клетку впереди
            if (!IsPositionFree(possible_moves[1] % 10, possible_moves[1] / 10))
                possible_moves[1] = -1;
            //Проверка на наличие вражеской фигуры по диагонали справа
            if (IsPositionFree(possible_moves[2] % 10, possible_moves[2] / 10) ||
                (IsPositionFree(possible_moves[2] % 10, possible_moves[2] / 10)) &&
                (!IsEnemy(figures[index]->GetTeam(), possible_moves[2])))
                possible_moves[2] = -1;

            //Проверка на наличие вражеской фигуры по диагонали слева
            if (IsPositionFree(possible_moves[3] % 10, possible_moves[3] / 10) ||
                (IsPositionFree(possible_moves[3] % 10, possible_moves[3] / 10)) &&
                (!IsEnemy(figures[index]->GetTeam(), possible_moves[3])))
                possible_moves[3] = -1;

            figures[index]->SetNotFirstMove();
            break;
        }
        case 3: // Конь(Knight)
        {
            int position_x_from_possible_moves, position_y_from_possible_moves;

            for (int i = 0; i < figures[index]->GetAmountOfPossibleMoves(); ++i) {
                position_x_from_possible_moves = possible_moves[i] % 10;
                position_y_from_possible_moves = possible_moves[i] / 10;

                if (!IsPositionFree(position_x_from_possible_moves, position_y_from_possible_moves) &&
                    !IsEnemy(figures[index]->GetTeam(),
                             FindPiece(position_x_from_possible_moves, position_y_from_possible_moves)))
                    possible_moves[i] = -1;

            }
            break;
        }
        case 4: // Слон(Bishop)
        {
            int position_x_from_possible_moves, position_y_from_possible_moves;
            for (int i = 0; i < 8; ++i) {
                position_x_from_possible_moves = possible_moves[i] % 10;
                position_y_from_possible_moves = possible_moves[i] / 10;
                if (!IsPositionFree(position_x_from_possible_moves, position_y_from_possible_moves) &&
                    IsEnemy(figures[index]->GetTeam(),
                            FindPiece(position_x_from_possible_moves, position_y_from_possible_moves)))
                    continue;
                if (!IsPositionFree(position_x_from_possible_moves, position_y_from_possible_moves) &&
                    !IsEnemy(figures[index]->GetTeam(),
                             FindPiece(position_x_from_possible_moves, position_y_from_possible_moves))) {
                    for (int j = i; j < 8; ++j) possible_moves[j] = -1;
                    break;
                }
            }
            for (int i = 8; i < 16; ++i) {
                position_x_from_possible_moves = possible_moves[i] % 10;
                position_y_from_possible_moves = possible_moves[i] / 10;
                if (!IsPositionFree(position_x_from_possible_moves, position_y_from_possible_moves) &&
                    IsEnemy(figures[index]->GetTeam(),
                            FindPiece(position_x_from_possible_moves, position_y_from_possible_moves)))
                    continue;

                if (!IsPositionFree(position_x_from_possible_moves, position_y_from_possible_moves) &&
                    !IsEnemy(figures[index]->GetTeam(),
                             FindPiece(position_x_from_possible_moves, position_y_from_possible_moves))) {
                    for (int j = i; j < 16; ++j) possible_moves[j] = -1;
                    break;
                }
            }
            // Если на пути влево мы встретили фигуру, то все клетки за ней становятся недоступны для ходьбы

            for (int i = 16; i < 24; ++i) {
                position_x_from_possible_moves = possible_moves[i] % 10;
                position_y_from_possible_moves = possible_moves[i] / 10;
                if (!IsPositionFree(position_x_from_possible_moves, position_y_from_possible_moves) &&
                    IsEnemy(figures[index]->GetTeam(),
                            FindPiece(position_x_from_possible_moves, position_y_from_possible_moves)))
                    continue;

                if (!IsPositionFree(position_x_from_possible_moves, position_y_from_possible_moves) &&
                    !IsEnemy(figures[index]->GetTeam(),
                             FindPiece(position_x_from_possible_moves, position_y_from_possible_moves))) {
                    for (int j = i; j < 24; ++j) possible_moves[j] = -1;
                    break;
                }
            }
            // Если на пути вправо мы встретили фигуру, то все клетки за ней становятся недоступны для ходьбы

            for (int i = 24; i < 32; ++i) {
                position_x_from_possible_moves = possible_moves[i] % 10;
                position_y_from_possible_moves = possible_moves[i] / 10;
                if (!IsPositionFree(position_x_from_possible_moves, position_y_from_possible_moves) &&
                    IsEnemy(figures[index]->GetTeam(),
                            FindPiece(position_x_from_possible_moves, position_y_from_possible_moves)))
                    continue;

                if (!IsPositionFree(position_x_from_possible_moves, position_y_from_possible_moves) &&
                    !IsEnemy(figures[index]->GetTeam(),
                             FindPiece(position_x_from_possible_moves, position_y_from_possible_moves))) {
                    for (int j = i; j < 32; ++j) possible_moves[j] = -1;
                    break;
                }
            }
            break;

        }
        case 5: // Ладья(Rook)
        {
            int position_x_from_possible_moves, position_y_from_possible_moves;
            // Если на пути вверх мы встретили фигуру, то все клетки за ней становятся недоступны для ходьбы
            for (int i = 0; i < 8; ++i) {
                position_x_from_possible_moves = possible_moves[i] % 10;
                position_y_from_possible_moves = possible_moves[i] / 10;
                if (!IsPositionFree(position_x_from_possible_moves, position_y_from_possible_moves) &&
                    IsEnemy(figures[index]->GetTeam(),
                            FindPiece(position_x_from_possible_moves, position_y_from_possible_moves))) {

                    for (int j = i + 1; j < 8; ++j) possible_moves[j] = -1;
                    break;
                }
                if (!IsPositionFree(position_x_from_possible_moves, position_y_from_possible_moves) &&
                    !IsEnemy(figures[index]->GetTeam(),
                             FindPiece(position_x_from_possible_moves, position_y_from_possible_moves))) {
                    for (int j = i; j < 8; ++j) possible_moves[j] = -1;
                    break;
                }
            }
            // Если на пути вниз мы встретили фигуру, то все клетки за ней становятся недоступны для ходьбы

            for (int i = 8; i < 16; ++i) {
                position_x_from_possible_moves = possible_moves[i] % 10;
                position_y_from_possible_moves = possible_moves[i] / 10;
                if (!IsPositionFree(position_x_from_possible_moves, position_y_from_possible_moves) &&
                    IsEnemy(figures[index]->GetTeam(),
                            FindPiece(position_x_from_possible_moves, position_y_from_possible_moves))) {
                    for (int j = i + 1; j < 16; ++j) possible_moves[j] = -1;
                    break;
                }
                if (!IsPositionFree(position_x_from_possible_moves, position_y_from_possible_moves) &&
                    !IsEnemy(figures[index]->GetTeam(),
                             FindPiece(position_x_from_possible_moves, position_y_from_possible_moves))) {
                    for (int j = i; j < 16; ++j) possible_moves[j] = -1;
                    break;
                }
            }
            // Если на пути влево мы встретили фигуру, то все клетки за ней становятся недоступны для ходьбы

            for (int i = 16; i < 24; ++i) {
                position_x_from_possible_moves = possible_moves[i] % 10;
                position_y_from_possible_moves = possible_moves[i] / 10;
                if (!IsPositionFree(position_x_from_possible_moves, position_y_from_possible_moves) &&
                    IsEnemy(figures[index]->GetTeam(),
                            FindPiece(position_x_from_possible_moves, position_y_from_possible_moves))) {
                    for (int j = i + 1; j < 24; ++j) possible_moves[j] = -1;
                    break;
                }
                if (!IsPositionFree(position_x_from_possible_moves, position_y_from_possible_moves) &&
                    !IsEnemy(figures[index]->GetTeam(),
                             FindPiece(position_x_from_possible_moves, position_y_from_possible_moves))) {
                    for (int j = i; j < 24; ++j) possible_moves[j] = -1;
                    break;
                }
            }
            // Если на пути вправо мы встретили фигуру, то все клетки за ней становятся недоступны для ходьбы

            for (int i = 24; i < 32; ++i) {
                position_x_from_possible_moves = possible_moves[i] % 10;
                position_y_from_possible_moves = possible_moves[i] / 10;
                if (!IsPositionFree(position_x_from_possible_moves, position_y_from_possible_moves) &&
                    IsEnemy(figures[index]->GetTeam(),
                            FindPiece(position_x_from_possible_moves, position_y_from_possible_moves)))
                {
                    for (int j = i + 1; j < 32; ++j) possible_moves[j] = -1;
                    break;
                }
                if (!IsPositionFree(position_x_from_possible_moves, position_y_from_possible_moves) &&
                    !IsEnemy(figures[index]->GetTeam(),
                             FindPiece(position_x_from_possible_moves, position_y_from_possible_moves))) {
                    for (int j = i; j < 32; ++j) possible_moves[j] = -1;
                    break;
                }
            }
            break;
        }
        case 6: // Королева (Queen)
        {
            int position_x_from_possible_moves, position_y_from_possible_moves;
            // Если на пути вверх мы встретили фигуру, то все клетки за ней становятся недоступны для ходьбы
            for (int i = 0; i < 8; ++i) {
                position_x_from_possible_moves = possible_moves[i] % 10;
                position_y_from_possible_moves = possible_moves[i] / 10;
                if (!IsPositionFree(position_x_from_possible_moves, position_y_from_possible_moves) &&
                    IsEnemy(figures[index]->GetTeam(),
                            FindPiece(position_x_from_possible_moves, position_y_from_possible_moves))) {

                    for (int j = i + 1; j < 8; ++j) possible_moves[j] = -1;
                    break;
                }
                if (!IsPositionFree(position_x_from_possible_moves, position_y_from_possible_moves) &&
                    !IsEnemy(figures[index]->GetTeam(),
                             FindPiece(position_x_from_possible_moves, position_y_from_possible_moves))) {
                    for (int j = i; j < 8; ++j) possible_moves[j] = -1;
                    break;
                }
            }
            // Если на пути вниз мы встретили фигуру, то все клетки за ней становятся недоступны для ходьбы

            for (int i = 8; i < 16; ++i) {
                position_x_from_possible_moves = possible_moves[i] % 10;
                position_y_from_possible_moves = possible_moves[i] / 10;
                if (!IsPositionFree(position_x_from_possible_moves, position_y_from_possible_moves) &&
                    IsEnemy(figures[index]->GetTeam(),
                            FindPiece(position_x_from_possible_moves, position_y_from_possible_moves))) {
                    for (int j = i + 1; j < 16; ++j) possible_moves[j] = -1;
                    break;
                }
                if (!IsPositionFree(position_x_from_possible_moves, position_y_from_possible_moves) &&
                    !IsEnemy(figures[index]->GetTeam(),
                             FindPiece(position_x_from_possible_moves, position_y_from_possible_moves))) {
                    for (int j = i; j < 16; ++j) possible_moves[j] = -1;
                    break;
                }
            }
            // Если на пути влево мы встретили фигуру, то все клетки за ней становятся недоступны для ходьбы

            for (int i = 16; i < 24; ++i) {
                position_x_from_possible_moves = possible_moves[i] % 10;
                position_y_from_possible_moves = possible_moves[i] / 10;
                if (!IsPositionFree(position_x_from_possible_moves, position_y_from_possible_moves) &&
                    IsEnemy(figures[index]->GetTeam(),
                            FindPiece(position_x_from_possible_moves, position_y_from_possible_moves))) {
                    for (int j = i + 1; j < 24; ++j) possible_moves[j] = -1;
                    break;
                }
                if (!IsPositionFree(position_x_from_possible_moves, position_y_from_possible_moves) &&
                    !IsEnemy(figures[index]->GetTeam(),
                             FindPiece(position_x_from_possible_moves, position_y_from_possible_moves))) {
                    for (int j = i; j < 24; ++j) possible_moves[j] = -1;
                    break;
                }
            }
            // Если на пути вправо мы встретили фигуру, то все клетки за ней становятся недоступны для ходьбы

            for (int i = 24; i < 32; ++i) {
                position_x_from_possible_moves = possible_moves[i] % 10;
                position_y_from_possible_moves = possible_moves[i] / 10;
                if (!IsPositionFree(position_x_from_possible_moves, position_y_from_possible_moves) &&
                    IsEnemy(figures[index]->GetTeam(),
                            FindPiece(position_x_from_possible_moves, position_y_from_possible_moves)))
                {
                    for (int j = i + 1; j < 32; ++j) possible_moves[j] = -1;
                    break;
                }
                if (!IsPositionFree(position_x_from_possible_moves, position_y_from_possible_moves) &&
                    !IsEnemy(figures[index]->GetTeam(),
                             FindPiece(position_x_from_possible_moves, position_y_from_possible_moves))) {
                    for (int j = i; j < 32; ++j) possible_moves[j] = -1;
                    break;
                }
            }


            //============

            for (int i = 32; i < 40; ++i) {
                position_x_from_possible_moves = possible_moves[i] % 10;
                position_y_from_possible_moves = possible_moves[i] / 10;
                if (!IsPositionFree(position_x_from_possible_moves, position_y_from_possible_moves) &&
                    IsEnemy(figures[index]->GetTeam(),
                            FindPiece(position_x_from_possible_moves, position_y_from_possible_moves)))
                    continue;
                if (!IsPositionFree(position_x_from_possible_moves, position_y_from_possible_moves) &&
                    !IsEnemy(figures[index]->GetTeam(),
                             FindPiece(position_x_from_possible_moves, position_y_from_possible_moves))) {
                    for (int j = i; j < 40; ++j) possible_moves[j] = -1;
                    break;
                }
            }
            for (int i = 40; i < 48; ++i) {
                position_x_from_possible_moves = possible_moves[i] % 10;
                position_y_from_possible_moves = possible_moves[i] / 10;
                if (!IsPositionFree(position_x_from_possible_moves, position_y_from_possible_moves) &&
                    IsEnemy(figures[index]->GetTeam(),
                            FindPiece(position_x_from_possible_moves, position_y_from_possible_moves)))
                    continue;
                if (!IsPositionFree(position_x_from_possible_moves, position_y_from_possible_moves) &&
                    !IsEnemy(figures[index]->GetTeam(),
                             FindPiece(position_x_from_possible_moves, position_y_from_possible_moves))) {
                    for (int j = i; j < 48; ++j) possible_moves[j] = -1;
                    break;
                }
            }
            // Если на пути влево мы встретили фигуру, то все клетки за ней становятся недоступны для ходьбы
            for (int i = 48; i < 56; ++i) {
                position_x_from_possible_moves = possible_moves[i] % 10;
                position_y_from_possible_moves = possible_moves[i] / 10;
                if (!IsPositionFree(position_x_from_possible_moves, position_y_from_possible_moves) &&
                    IsEnemy(figures[index]->GetTeam(),
                            FindPiece(position_x_from_possible_moves, position_y_from_possible_moves)))
                    continue;
                if (!IsPositionFree(position_x_from_possible_moves, position_y_from_possible_moves) &&
                    !IsEnemy(figures[index]->GetTeam(),
                             FindPiece(position_x_from_possible_moves, position_y_from_possible_moves))) {
                    for (int j = i; j < 56; ++j) possible_moves[j] = -1;
                    break;
                }
            }
            // Если на пути вправо мы встретили фигуру, то все клетки за ней становятся недоступны для ходьбы
            for (int i = 56; i < 64; ++i) {
                position_x_from_possible_moves = possible_moves[i] % 10;
                position_y_from_possible_moves = possible_moves[i] / 10;
                if (!IsPositionFree(position_x_from_possible_moves, position_y_from_possible_moves) &&
                    IsEnemy(figures[index]->GetTeam(),
                            FindPiece(position_x_from_possible_moves, position_y_from_possible_moves)))
                    continue;
                if (!IsPositionFree(position_x_from_possible_moves, position_y_from_possible_moves) &&
                    !IsEnemy(figures[index]->GetTeam(),
                             FindPiece(position_x_from_possible_moves, position_y_from_possible_moves))) {
                    for (int j = i; j < 64; ++j) possible_moves[j] = -1;
                    break;
                }
            }
            break;
        }
    }
}


int *Board::CalculatePossiblePositions(const int &current_position_X, const int &current_position_Y, const int &index) {
    int *possible_moves = figures[index]->CalculatingPossibleMoves();
    switch (figures[index]->GetFigure()) {
        case 1: // Король(King)
        {
            // Проверяем на выход за границы доски
            int position_x_from_possible_moves, position_y_from_possible_moves;
            for (int i = 0; i < figures[index]->GetAmountOfPossibleMoves(); ++i) {
                position_x_from_possible_moves = possible_moves[i] % 10;
                position_y_from_possible_moves = possible_moves[i] / 10;
                if (!IsPositionFree(position_x_from_possible_moves, position_y_from_possible_moves) &&
                    !IsEnemy(figures[index]->GetTeam(),
                             FindPiece(position_x_from_possible_moves, position_y_from_possible_moves)))
                    possible_moves[i] = -1;
            }

            // Получаем значение текущей команды короля
            int current_king_team = figures[index]->GetTeam();
            int size_of_all_enemy_moves = 0; // Размер массива в котором будут храниться все вражеские клетки

            // Инициализируем массив размеру равному сумме всех возможных движений вражеских фигур
            for (int i = 0; i < white_player->GetAmountOfFigures() + black_player->GetAmountOfFigures(); ++i) {
                if (figures[i]->GetTeam() != current_king_team &&
                    figures[i]->GetPositionY() != -1) // Если фигура вражеская по отношению к королю
                    size_of_all_enemy_moves += figures[i]->GetAmountOfPossibleMoves();
            }
            int *all_enemy_moves = new int[size_of_all_enemy_moves]{}; // Массив, который будет в себе содержать все возможные ходы врагов

            // У каждой вражеской фигуры формируем массив клеток куда она может пойти
            // - затем записываем эти клетки в общий массив
            int *temp_possible_moves; // Массив для хранения клеток
            int temp_size; // Размер этого массива
            int previous_index = 0;

            for (int i = 0; i < white_player->GetAmountOfFigures() + black_player->GetAmountOfFigures(); ++i) {
                if (figures[i]->GetTeam() != current_king_team) {
                    temp_size = figures[i]->GetAmountOfPossibleMoves();
                    temp_possible_moves = figures[i]->CalculatingPossibleMoves();

                    if (figures[i]->GetFigure() != 2) CheckPossiblePositions(temp_possible_moves, i);
                    else
                        temp_possible_moves[0] = temp_possible_moves[1] = -1;


                    int little_index = 0;
                    for (int j = previous_index; j < previous_index + temp_size; ++j) {
                        all_enemy_moves[j] = temp_possible_moves[little_index];
                        little_index++;
                    }
                    std::cout << std::endl;
                    previous_index += temp_size;
                }
            }

            // Проверяем есть ли среди тех клекток куда король может пойти - клетки, которые могут быть атакованы
            for (int i = 0; i < figures[i]->GetAmountOfPossibleMoves(); ++i) {
                for (int j = 0; j < size_of_all_enemy_moves; ++j) {
                    if (possible_moves[i] == all_enemy_moves[j])
                        possible_moves[i] = -1;

                }
            }

            break;
        }
        default:
            CheckPossiblePositions(possible_moves, index);

    }
    return possible_moves;
}

void Board::ChangePosition(const int &old_position_X, const int &old_position_Y, const int &next_position_X,
                           const int &next_position_Y,
                           const int index
) {

    __square[old_position_Y][old_position_X] = 0;
    figures[index]->SetPositionX(next_position_X);
    figures[index]->SetPositionY(next_position_Y);
    if (figures[index]->GetFigure() == 2) {
        switch (figures[index]->GetTeam()) {
            case 8: // Чёрные
                if (next_position_Y == 7)
                    black_player->ChangePawnIntoAnotherFigure(figures[index]->GetPositionY(),
                                                              figures[index]->GetPositionX());
                for (int i = 0; i < 16; ++i) figures[i + 16] = black_player->GetMyFigure(i);

                break;
            case 16:
                if (next_position_Y == 0) {
                    white_player->ChangePawnIntoAnotherFigure(figures[index]->GetPositionY(),
                                                              figures[index]->GetPositionX());
                    for (int i = 0; i < 16; ++i) figures[i] = white_player->GetMyFigure(i);

                }


        }
    }
    __square[next_position_Y][next_position_X] = figures[index]->GetFigure() | figures[index]->GetTeam();


}

Board::~Board() {
    for (int i = 0; i < 32; i++) {
        delete figures[i];
    }
}

void Board::PrintWhiteTeamScore() {
    std::cout << "Счёт:" << "\t     " << white_player->GetLastCapturedFigure()
              << std::endl;

}

void Board::PrintBlackTeamScore() {
    std::cout << "Счёт:" << "\t     " << black_player->GetLastCapturedFigure()
              << std::endl;

}

void Board::PrintBoard() {
    PrintBlackTeamScore();
    for (int i = 0; i < 8; i++) {
        std::cout << 8 - i << " ";

        for (int j = 0; j < 8; j++) {
            if ((i + j) % 2 == 0)
                std::cout << REDB;
            else
                std::cout << YELB;
            int color = figures[i]->GetColor(__square[i][j]);
            if (color == 8)
                std::cout << BBLK;
            if (color == 16)
                std::cout << BWHT;

            switch (figures[i]->GetType(__square[i][j])) {
                case 0:
                    std::cout << "   ";
                    break;
                case 1:
                    std::cout << " ♕ ";
                    break;
                case 2:
                    std::cout << " ♙ ";
                    break;
                case 3:
                    std::cout << " ♘ ";
                    break;
                case 4:
                    std::cout << " ♗ ";
                    break;
                case 5:
                    std::cout << " ♖ ";
                    break;
                case 6:
                    std::cout << " ♔ ";
                    break;
            }
        }
        std::cout << CRESET;
        std::cout << std::endl;
    }
    std::cout << "  ";
    for (char letter = 'A'; letter <= 'H'; letter++)
        std::cout << " " << letter << " ";
    std::cout << ' ' << std::endl;
    PrintWhiteTeamScore();
}

bool Board::IsPositionFree(const int &position_X, const int &position_Y) {
    if (__square[position_Y][position_X] == 0) return true;
    return false;

}

bool
Board::FindNewPositionInPossiblesPositions(const int *possible_positions, const int &next_position_X,
                                           const int &next_position_Y, const int &index) {
    for (int i = 0; i < figures[index]->GetAmountOfPossibleMoves(); ++i)
        if (possible_positions[i] / 10 == next_position_Y && possible_positions[i] % 10 == next_position_X)
            return true;

    return false;
}

int Board::makeMove(const int &current_position_X, const int &current_position_Y, const int &next_position_X,
                    const int &next_position_Y) {
    int index = FindPiece(current_position_X, current_position_Y);
    int *possible_positions = CalculatePossiblePositions(current_position_X, current_position_Y, index);
    if (FindNewPositionInPossiblesPositions(possible_positions, next_position_X, next_position_Y, index)) {
        if (!IsPositionFree(next_position_X, next_position_Y) &&
            IsEnemy(figures[index]->GetTeam(), FindPiece(next_position_X, next_position_Y))) {
            switch (figures[index]->GetTeam()) {

                case 8: // Чёрные
                    std::cout << "Команда чёрных захватила фигуру!" << std::endl;
                    if (black_player->CaptureEnemyFigure(
                            white_player->FigureWasCaptured(next_position_Y, next_position_X)) == 1) {
                        ChangePosition(current_position_X, current_position_Y, next_position_X, next_position_Y, index);

                        return 1;
                    }
                    return 0;
                case 16: // Белые
                    std::cout << "Команда белых захватила фигуру!" << std::endl;
                    if (white_player->CaptureEnemyFigure(
                            black_player->FigureWasCaptured(next_position_Y, next_position_X)) == 1) {
                        ChangePosition(current_position_X, current_position_Y, next_position_X, next_position_Y, index);
                        return 1;

                    }
                    return 0; // Если вернули код 0 - значит захватили короля, и игра окончена

            }
            system("pause");
        }
        ChangePosition(current_position_X, current_position_Y, next_position_X, next_position_Y, index);
        return 1;

    }
    return 2;

    system("pause");
}

int* Board::FindBestFigure() {
    int *BestFiguresToMove = new int[16];
    int best_figure_position = (figures[16]->GetPositionY() * 10) + figures[16]->GetPositionX();
    for (int i = 16; i < 32; ++i) {
        if (figures[i]->GetTeam() == 8 && figures[i]->GetFigure() != 1) {
            BestFiguresToMove[i-16] = (figures[i]->GetPositionY() * 10) + figures[i]->GetPositionX();

        }
    }
    for (int i = 0; i < 16-1; ++i) {
        for (int j = 0; j < 16-1; ++j) {
            int current_position = BestFiguresToMove[j];
            int next_position = BestFiguresToMove[j+1];
            int best_position = FindClosestCoordinate(current_position, next_position,
                                                      (figures[12]->GetPositionY() * 10) +
                                                      figures[12]->GetPositionX());
            if(best_position == next_position)
                std::swap(BestFiguresToMove[j],BestFiguresToMove[j+1]);

        }
    }
    return BestFiguresToMove;
}

int Board::FindBestMoveForFigure(int current_position_X, int current_position_Y, int index) {

    // Генерируем для неё список ходов куда она может пойти
    int *possible_positions= CalculatePossiblePositions(current_position_X, current_position_Y, index);



    // Проверяем эти ходы на рентабельность
    CheckPossiblePositions(possible_positions, index);
    // Ищем лучший ход
    int best_position_to_move = possible_positions[0];
    for (int i = 0; i < figures[index]->GetAmountOfPossibleMoves(); ++i) {
        int maybe_best_position_to_move = possible_positions[i];
        best_position_to_move = FindClosestCoordinate(best_position_to_move, maybe_best_position_to_move,
                                                      (figures[12]->GetPositionY() * 10) + figures[12]->GetPositionX());
    }
    return best_position_to_move;
}
int Board::makeAIMove() {

    int current_position_X;
    int current_position_Y;
    int index;

    int best_position_to_move;

    int  best_pos = 0;
    while(true)
    {
        // Сначала ищем фигуру которая обладает лучшей позицией
        int* best_figures_positions = FindBestFigure();
        int best_figure_position = best_figures_positions[best_pos];
        // Затем находим эту фигуру в массиве фигур figures, получая её индекс
        current_position_X = best_figure_position % 10;
        current_position_Y = best_figure_position / 10;
        index = FindPiece(current_position_X, current_position_Y);


        best_position_to_move = FindBestMoveForFigure(current_position_X, current_position_Y, index);
        if(best_position_to_move == -1) {
            best_pos++;
            continue;
        }
        break;

    }

    int next_position_X = best_position_to_move % 10;
    int next_position_Y = best_position_to_move / 10;
    if (!IsPositionFree(next_position_X, next_position_Y) &&
        IsEnemy(figures[index]->GetTeam(), FindPiece(next_position_X, next_position_Y))) {
        std::cout << "Команда чёрных захватила фигуру!" << std::endl;
        system("pause");
        if (black_player->CaptureEnemyFigure(
                white_player->FigureWasCaptured(next_position_Y, next_position_X)) == 1) {
            ChangePosition(current_position_X, current_position_Y, next_position_X, next_position_Y, index);

            return 1;
        }
        return 0; // Если вернули код 0 - значит захватили короля, и игра окончена
        system("pause");
    }
    ChangePosition(current_position_X, current_position_Y, next_position_X, next_position_Y, index);
    return 1;
    system("pause");
}

int Board::FindClosestCoordinate(int current_closest, int maybe_next_closest, int king_coord) {
    // Проверка на неверное значение
    if (maybe_next_closest < 0 || current_closest == maybe_next_closest) return current_closest;
    if (maybe_next_closest == king_coord) return maybe_next_closest;
    // Формируем Х У для каждого числа
    int king_y = king_coord / 10;
    int king_x = king_coord % 10;
    int maybe_y = maybe_next_closest / 10;
    int maybe_x = maybe_next_closest % 10;
    int curr_y = current_closest / 10;
    int curr_x = current_closest % 10;

    // Если по У следующая позиция ближе к королю
    if (abs(king_y - maybe_y) < abs(king_y - curr_y) || (king_y - maybe_y)) {
        if (abs(king_x - maybe_x) < abs(king_x - curr_x) || curr_x == maybe_x)
            return maybe_next_closest;


    }
    return current_closest;

}
int Board::GetBlackTeamScore() {return black_player->GetLastCapturedFigure();}
int Board::GetWhiteTeamScore() {return white_player->GetLastCapturedFigure();}