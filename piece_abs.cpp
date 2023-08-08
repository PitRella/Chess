#include "piece_abs.h"

MyOwnAbstractPiece::MyOwnAbstractPiece() {
    this->figure = 0;
    this->team = 0;
    this->position_x = -1;
    this->position_y = -1;
    this->amount_of_possible_moves = 0;
}

MyOwnAbstractPiece::~MyOwnAbstractPiece() {}

MyOwnAbstractPiece::MyOwnAbstractPiece(const char figure[], const char team[], const int &x_position,
                                       const int &y_position,
                                       const int &amount_of_possible_moves) {
    switch (djb2Hash(figure)) {

        case djb2Hash("King"):
            this->figure = 1;
            break;
        case djb2Hash("Pawn"):
            this->figure = 2;
            break;
        case djb2Hash("Knight"):
            this->figure = 3;
            break;
        case djb2Hash("Bishop"):
            this->figure = 4;
            break;
        case djb2Hash("Rook"):
            this->figure = 5;
            break;
        case djb2Hash("Queen"):
            this->figure = 6;
            break;


    }
    switch (djb2Hash(team)) {
        case djb2Hash("Black"):
            this->team = 8;
            break;
        case djb2Hash("White"):
            this->team = 16;
            break;


    }
    this->position_x = x_position;
    this->position_y = y_position;
    this->amount_of_possible_moves = amount_of_possible_moves;
    possible_moves = new int[this->amount_of_possible_moves];
    for (int i = 0; i < amount_of_possible_moves; ++i)possible_moves[i] = -1;
    this->isFirstMove = true;

}


int MyOwnAbstractPiece::GetFigure() const { return figure; }

int MyOwnAbstractPiece::GetTeam() const { return team; }

int MyOwnAbstractPiece::GetColor(const int &piece) const { return piece & colorMask; }

int MyOwnAbstractPiece::GetType(const int &piece) const { return piece & typeMask; }

int MyOwnAbstractPiece::GetPositionX() { return this->position_x; }
int MyOwnAbstractPiece::GetPositionY() { return this->position_y; }

int MyOwnAbstractPiece::GetAmountOfPossibleMoves() { return this->amount_of_possible_moves; }

void MyOwnAbstractPiece::SetPositionX(const int position_x) { this->position_x = position_x; }
void MyOwnAbstractPiece::SetPositionY(const int position_y) { this->position_y = position_y; }

int MyOwnAbstractPiece::Move(const int &position) {}

int *MyOwnAbstractPiece::CalculatingPossibleMoves() {}
bool MyOwnAbstractPiece::IsItFirstMove() {return isFirstMove;}
void MyOwnAbstractPiece::SetNotFirstMove(){isFirstMove = false;}
void MyOwnAbstractPiece::SetFirstMove(){isFirstMove = true;}
