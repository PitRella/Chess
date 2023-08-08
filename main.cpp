#include "pch.h"
#include "board.cpp"
#include "input_parser.h"
#include "White_team.h"
#include "Black_team.h"
#include "WriteScore.h"
int main() {
    SetConsoleOutputCP(CP_UTF8);
    char name1[50];
    char name2[50] = "SecondPlayer";
    std::cout << "Введіть ім'я: ";
    std::cin >> name1;
    while (strlen(name1) < 4) {
        system("cls");
        std::cout << "Вибачте, але ви ввели невірне ім'я. Воно має утримувати хоча б чотири букви. А ви ввели "
                  << strlen(name1) << std::endl;
        std::cout << "Спробуйте ще:";
        std::cin >> name1;
    }
    system("cls");
    char charPlayerOrPc;
    int player_or_pc = 0;
    std::cout << BWHT << "=========== ШАХИ ===========" << CRESET << std::endl;
    std::cout << "Ласкаво просимо, " << name1 << "\n"
                                                "Для коректної роботи цієї гри\n"
                                                "необхідна підтримка керуючої \n"
                                                "послідовності для кольору\n"
                                                "у вашому емуляторі терміналу.\n"
                                                "Найкращий вибір: Windows Terminal.\n"
                                                "" << std::endl;
    system("pause");
    system("cls");
    std::cout << "Ви хочете грати з людиною чи з комп'ютером?\n"
                 "1 - Людина\n"
                 "2 - Комп'ютер\n"
                 ": ";
    std::cin >> charPlayerOrPc;
    while (!isdigit(charPlayerOrPc) || atoi(&charPlayerOrPc) < 1 ||  atoi(&charPlayerOrPc) > 2) {
        system("cls");
        std::cin.ignore();
        std::cout << "Ви зробили невірний вибір. Нагадую, що обрати можна або 1, або 2." << std::endl;
        std::cout << "Спробуйте ще:";
        std::cin >> charPlayerOrPc;
    }
    player_or_pc = atoi(&charPlayerOrPc);
    std::cin.ignore();
    WhiteTeam white_player;
    BlackTeam black_player;
    Board mainBoard(white_player, black_player);
    int turn{1};
    int *figurePosition;
    int *wantToMove;
    switch (player_or_pc) {
        case 1: { // Гра з іншим гравцем
            std::cout << "Введіть ім'я ішного гравця: ";
            std::cin >> name2;
            while (strlen(name2) < 4) {
                system("cls");
                std::cout << "Вибачте, але ви ввели невірне ім'я для іншого гравця. Воно має утримувати хоча б чотири букви. А ви ввели "
                          << strlen(name2) << std::endl;
                std::cout << "Спробуйте ще:";
                std::cin >> name2;
            }
            while (true) {
                std::cin.ignore();
                system("cls");
                mainBoard.PrintBoard();
                char input[2];
                switch (turn) {
                    case 1: {
                        std::cout << "Хід білих" << std::endl;
                        std::cout << "Виберіть фігуру якої хочете бути схожим:";
                        std::cin.getline(input,50);
                        while (isdigit(input[0]) || !isdigit(input[1])) {
                            std::cin.ignore();
                            std::cin.clear();
                            memset(input, 0, sizeof(input));
                            std::cout << "Неправильне введення, спробуйте ще: ";
                            std::cin.getline(input, 50);
                        }
                        figurePosition = parseInput(input);
                        while (figurePosition == nullptr ||
                               mainBoard.IsPositionFree(figurePosition[0], (figurePosition[1])) ||
                               mainBoard.WhichTeam(figurePosition[0], (figurePosition[1])) != 16) {
                            system("cls");
                            mainBoard.PrintBoard();

                            std::cout << "Неправильне введення, спробуйте ще: ";
                            std::cin.getline(input, 50);
                            figurePosition = parseInput(input);
                        }
                        mainBoard.PrintBoard();
                        std::cout << "Оберіть клітинку куди хочете походити:";
                        std::cin.getline(input, 3);
                        wantToMove = parseInput(input);
                        while (wantToMove == nullptr) {
                            system("cls");
                            mainBoard.PrintBoard();
                            std::cout << "Неправильне введення, спробуйте ще: " << std::endl;
                            std::cin.getline(input, 2);
                            wantToMove = parseInput(input);
                        }
                        int operation_code = mainBoard.makeMove(figurePosition[0], figurePosition[1], wantToMove[0],
                                                                wantToMove[1]);
                        switch (operation_code) {
                            case 0: // Король захвачен - игра окончена
                            {
                                system("cls");
                                std::cout << REDB << "Гра завершена" << CRESET << std::endl;
                                std::cout << "Рахунок білих:" << white_player.GetLastCapturedFigure() << std::endl;
                                std::cout << "Рахунок чорних:" << black_player.GetLastCapturedFigure() << std::endl;
                                StartWrite(name1, mainBoard.GetWhiteTeamScore(),name2, mainBoard.GetBlackTeamScore());
                                system("pause");
                                exit(0);
                            }
                            case 1: // Успешно выполненный ход
                                turn = 2;
                                break;
                            case 2:
                                system("cls");
                                std::cout << REDB << "Невірний ход." << CRESET << std::endl;
                                system("pause");
                                break;

                        }

                        break;
                    }
                    case 2: {
                        std::cout << "Хід чорних" << std::endl;
                        std::cout << "Оберіть фігуру якою хочете ходити: ";
                        std::cin.getline(input, 3);
                        figurePosition = parseInput(input);
                        while (figurePosition == nullptr ||
                               mainBoard.IsPositionFree(figurePosition[0], (figurePosition[1])) ||
                               mainBoard.WhichTeam(figurePosition[0], (figurePosition[1])) != 8) {
                            system("cls");
                            mainBoard.PrintBoard();
                            std::cout << "Неправильне введення, спробуйте ще: ";
                            std::cin.getline(input, 3);
                            figurePosition = parseInput(input);
                        }
                        system("cls");
                        mainBoard.PrintBoard();
                        std::cout << "Оберіть клітинку куди хочете походити:";
                        std::cin.getline(input, 3);
                        wantToMove = parseInput(input);
                        while (wantToMove == nullptr) {
                            system("cls");
                            mainBoard.PrintBoard();
                            std::cout << "Неправильне введення, спробуйте ще: " << std::endl;
                            std::cin.getline(input, 2);
                            wantToMove = parseInput(input);
                        }
                        int operation_code = mainBoard.makeMove(figurePosition[0], figurePosition[1], wantToMove[0],
                                                                wantToMove[1]);
                        switch (operation_code) {
                            case 0: // Король захвачен - игра окончена
                            {
                                system("cls");
                                std::cout << REDB << "Гра завершєна" << CRESET;
                                std::cout << "Рахунок білих:" << white_player.GetLastCapturedFigure() << std::endl;
                                std::cout << "Рахунок чорних:" << black_player.GetLastCapturedFigure() << std::endl;
                                StartWrite(name1, mainBoard.GetWhiteTeamScore(),name2, mainBoard.GetBlackTeamScore());
                                system("pause");
                                exit(0);
                            }
                            case 1: // Успешно выполненный ход
                                turn = 1;
                                break;
                            case 2:
                                system("cls");
                                std::cout << REDB << "Невірний ход." << CRESET << std::endl;
                                system("pause");
                                break;

                        }
                        break;
                    }

                    default:
                        exit(0);
                }


                delete[] figurePosition;
                delete[] wantToMove;


            }
            break;
        } // Игра с человеком
        case 2: // Игра с ботом
            while (true) {
                system("cls");
                mainBoard.PrintBoard();
                char input[2]{};
                switch (turn) {
                    case 1: {
                        std::cout << "Хід білих" << std::endl;
                        std::cout << "Оберіть фігуру якою хочете ходити: ";
                        std::cin.getline(input, 50);
                        while (isdigit(input[0]) || !isdigit(input[1])) {
                            std::cin.ignore();
                            std::cin.clear();
                            memset(input, 0, sizeof(input));
                            std::cout << "Неправильне введення, спробуйте ще: ";
                            std::cin.getline(input, 50);
                        }
                        figurePosition = parseInput(input);
                        while (figurePosition == nullptr ||
                               mainBoard.IsPositionFree(figurePosition[0], (figurePosition[1])) ||
                               mainBoard.WhichTeam(figurePosition[0], (figurePosition[1])) != 16) {
                            system("cls");
                            mainBoard.PrintBoard();
                            std::cout << "Неправильне введення, спробуйте ще: ";
                            std::cin.getline(input, 50);
                            figurePosition = parseInput(input);
                        }
                        system("cls");
                        mainBoard.PrintBoard();
                        std::cout << "Оберіть клітинку куди хочете походити:";
                        std::cin.getline(input, 3);
                        wantToMove = parseInput(input);
                        while (wantToMove == nullptr) {
                            system("cls");
                            mainBoard.PrintBoard();
                            std::cout << "Неправильне введення, спробуйте ще: " << std::endl;
                            std::cin.getline(input, 2);
                            wantToMove = parseInput(input);
                        }
                        int operation_code = mainBoard.makeMove(figurePosition[0], figurePosition[1], wantToMove[0],
                                                                wantToMove[1]);
                        switch (operation_code) {
                            case 0: // Король захвачен - игра окончена
                            {
                                system("cls");
                                std::cout << REDB << "Гра завершена" << CRESET << std::endl;
                                std::cout << "Рахунок білих:" << white_player.GetLastCapturedFigure() << std::endl;
                                std::cout << "Рахунок чорних:" << black_player.GetLastCapturedFigure() << std::endl;
                                StartWrite(name1, mainBoard.GetWhiteTeamScore(),name2, mainBoard.GetBlackTeamScore());
                                system("pause");
                                exit(0);
                            }
                            case 1: // Успешно выполненный ход
                                turn = 2;
                                break;
                            case 2:
                                system("cls");
                                std::cout << REDB << "Невірний ход." << CRESET << std::endl;
                                system("pause");
                                break;

                        }

                        break;
                    }
                    case 2: {
                        std::cout << "Хід чорних" << std::endl;
                        mainBoard.PrintBoard();
                        int operation_code = mainBoard.makeAIMove();

                        switch (operation_code) {
                            case 0: // Король захвачен - игра окончена
                            {
                                system("cls");
                                std::cout << REDB << "Гра завершена" << CRESET << std::endl;
                                std::cout << "Рахунок білих:" << white_player.GetLastCapturedFigure() << std::endl;
                                std::cout << "Рахунок чорних:" << black_player.GetLastCapturedFigure() << std::endl;
                                StartWrite(name1, mainBoard.GetWhiteTeamScore(),name2, mainBoard.GetBlackTeamScore());
                                system("pause");
                                exit(0);
                            }
                            case 1: // Успешно выполненный ход
                                turn = 1;
                                break;
                            case 2:
                                system("cls");
                                std::cout << REDB << "Невірний ход." << CRESET << std::endl;
                                system("pause");
                                break;
                        }


                        break;
                    }

                    default:
                        exit(0);
                }


            }
            break;
            delete[] figurePosition;
            delete[] wantToMove;

    }

    return 0;
}

