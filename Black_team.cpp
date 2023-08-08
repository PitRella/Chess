#include "Black_team.h"

BlackTeam::BlackTeam() {

    own_figures[0] = new RookFigure("Black", 0, 0);
    own_figures[1] = new KnightFigure("Black", 1, 0);
    own_figures[2] = new BishopFigure("Black", 2, 0);
    own_figures[3] = new QueenFigure("Black", 3, 0);
    own_figures[4] = new KingFigure("Black", 4, 0);

    own_figures[5] = new BishopFigure("Black", 5, 0);
    own_figures[6] = new KnightFigure("Black", 6, 0);
    own_figures[7] = new RookFigure("Black", 7, 0);

    own_figures[8] = new PawnFigure("Black", 0, 1);
    own_figures[9] = new PawnFigure("Black", 1, 1);
    own_figures[10] = new PawnFigure("Black", 2, 1);
    own_figures[11] = new PawnFigure("Black", 3, 1);
    own_figures[12] = new PawnFigure("Black", 4, 1);
    own_figures[13] = new PawnFigure("Black", 5, 1);
    own_figures[14] = new PawnFigure("Black", 6, 1);
    own_figures[15] = new PawnFigure("Black", 7, 1);

}

void BlackTeam::ChangePawnIntoAnotherFigure(const int &position_y, const int &position_x) {
    int pawn_figure_index;
    for (int i = 0; i < amount_of_figures; ++i) {
        if (own_figures[i]->GetPositionY() == position_y &&
            own_figures[i]->GetPositionX() == position_x)
            pawn_figure_index = i;

    }
    int new_figure;
    std::cout << "Ви дійшли до кінця дошки - якою фігурою бажаєете стати?\n"
                 "Ферзь - 6\n"
                 "Тура - 5\n"
                 "Слон - 4\n"
                 "Кінь - 3\n";
    system("pause");
    std::cin >> new_figure;

    while (new_figure < 3 || new_figure > 6) {
        std::cout << "Ви ввели невірний тип фігури, повторіть спробу:";
        std::cin >> new_figure;
    }
    int pos_x = own_figures[pawn_figure_index]->GetPositionX();
    int pos_y = own_figures[pawn_figure_index]->GetPositionY();
    delete own_figures[pawn_figure_index];
    std::cin.ignore();
    switch (new_figure) {
        case 3:
            own_figures[pawn_figure_index] = new KnightFigure("Black", pos_x, pos_y);
            break;
        case 4:
            own_figures[pawn_figure_index] = new BishopFigure("Black", pos_x, pos_y);
            break;
        case 5:
            own_figures[pawn_figure_index] = new RookFigure("Black", pos_x, pos_y);
            break;
        case 6:
            own_figures[pawn_figure_index] = new QueenFigure("Black", pos_x, pos_y);
            break;


    }
}