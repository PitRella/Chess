//
// Created by artazol on 10.04.2023.
//

#ifndef NEWCHESSGAME_INPUT_PARSER_H
#define NEWCHESSGAME_INPUT_PARSER_H

int letterToInt(char letter) {
    switch (letter) {
        case 'a':
        case 'A':
            return 0;
        case 'b':
        case 'B':
            return 1;
        case 'c':
        case 'C':
            return 2;
        case 'd':
        case 'D':
            return 3;
        case 'e':
        case 'E':
            return 4;
        case 'f':
        case 'F':
            return 5;
        case 'g':
        case 'G':
            return 6;
        case 'h':
        case 'H':
            return 7;
        default:
            return -1;
    }
}
int InvertInt(int number){
    switch (number) {
        case 8:
            return 0;
        case 7:
            return 1;
        case 6:
            return 2;
        case 5:
            return 3;
        case 4:
            return 4;
        case 3:
            return 5;
        case 2:
            return 6;
        case 1:
            return 7;

    }
}
int *parseInput(const char input[]) {
    int *result = new int[2]{};
    result[0] = letterToInt(input[0]);
    result[1] = InvertInt(atoi(&input[1]));

    if (result[0] > 7 || result[0] < 0 || result[1] > 7 || result[1] < 0) return nullptr;

    return result;
}


#endif //NEWCHESSGAME_INPUT_PARSER_H