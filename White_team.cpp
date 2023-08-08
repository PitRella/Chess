#include "White_team.h"


WhiteTeam::WhiteTeam() {
    // Инициализируем позиции белых пешек
    own_figures[0] = new PawnFigure("White", 0,6);
    own_figures[1] = new PawnFigure("White", 1, 6);
    own_figures[2] = new PawnFigure("White",2, 6);
    own_figures[3] = new PawnFigure("White", 3, 6);
    own_figures[4] = new PawnFigure("White", 4, 6);
    own_figures[5] = new PawnFigure("White", 5, 6);
    own_figures[6] = new PawnFigure("White", 6, 6);
    own_figures[7] = new PawnFigure("White", 7, 6);
    // Инициализируем позиции остальных фигур
    own_figures[8] = new RookFigure("White", 0,7);
    own_figures[9] = new KnightFigure("White", 1,7);
    own_figures[10] = new BishopFigure("White", 2,7);
    own_figures[11] = new QueenFigure("White",3, 7);
    own_figures[12] = new KingFigure("White", 4,7);
    own_figures[13] = new BishopFigure("White",5, 7);
    own_figures[14] = new KnightFigure("White",6, 7);
    own_figures[15] = new RookFigure("White", 7,7);

}
void WhiteTeam::ChangePawnIntoAnotherFigure(const int &position_y, const int &position_x) {
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
            own_figures[pawn_figure_index] = new KnightFigure("White", pos_x, pos_y);
            break;
        case 4:
            own_figures[pawn_figure_index] = new BishopFigure("White", pos_x, pos_y);
            break;
        case 5:
            own_figures[pawn_figure_index] = new RookFigure("White", pos_x, pos_y);
            break;
        case 6:
            own_figures[pawn_figure_index] = new QueenFigure("White", pos_x, pos_y);
            break;


    }
    system("pause");
}