#include "Team_abs.h"

int AbstractTeam::FindPiece(const int &current_position_X, const int &current_position_Y) {
    for (int i = 0; i < 16; ++i) {
        if (own_figures[i]->GetPositionX() == current_position_X &&
            own_figures[i]->GetPositionY() == current_position_Y)
            return i;
    }
}

AbstractTeam::~AbstractTeam() {
    for (int i = 0; i < amount_of_figures; i++)
        delete own_figures[i];

}

int AbstractTeam::FigureWasCaptured(const int &position_y, const int &position_x) {
    //Находим фигуру в списке по координатам
    int captured_figure_index;
    for (int i = 0; i < amount_of_figures; ++i) {
        if (own_figures[i]->GetPositionY() == position_y &&
            own_figures[i]->GetPositionX() == position_x)
            captured_figure_index = i;

    }
    // Перемещаем фигуру за границу доски
    own_figures[captured_figure_index]->SetPositionX(-1);
    own_figures[captured_figure_index]->SetPositionY(-1);
    return own_figures[captured_figure_index]->GetFigure();

    // Возвращаем тип фигуры который мы убрали
    // 2 - Пешка.
}

int AbstractTeam::CaptureEnemyFigure(const int &captured_figure_number) {
    // Эта функция принимает тип захваченной фигуры. 2 - Пешка, и тд.
    switch (captured_figure_number) {
        case 1: // Если мы захватили короля - игра окончена.
        {
            std::cout<<"Короля захопили. Гра завершєна."<<std::endl;
            system("pause");
            return 0;
        }
        default:
        {
            captured_figures[last_captured_figures] = captured_figure_number;
            last_captured_figures++;
            return 1;
        }
    }

}

MyOwnAbstractPiece **AbstractTeam::GetMyFigures() { return own_figures; }

MyOwnAbstractPiece *AbstractTeam::GetMyFigure(const int index) { return own_figures[index]; }

int AbstractTeam::GetLastCapturedFigure(){return last_captured_figures;}

