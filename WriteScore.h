#ifndef CHESSJEZZ_WRITESCORE_H
#define CHESSJEZZ_WRITESCORE_H


#include <iostream>
#include <fstream>
#include <string>

// Функция для обновления счета пользователя в файле
void updateScore(const std::string& name, int score) {
    std::ifstream fileIn("scores.txt");
    std::ofstream fileOut("temp.txt");
    std::string line;
    bool nameFound = false;

    while (std::getline(fileIn, line)) {
        if (line.substr(0, name.size()) == name) {
            // Нашли имя пользователя, обновляем счет
            nameFound = true;
            int currentScore = std::stoi(line.substr(name.size() + 1));
            if (score > currentScore) {
                fileOut << name << " " << score << std::endl;
            } else {
                fileOut << line << std::endl;
            }
        } else {
            fileOut << line << std::endl;
        }
    }

    if (!nameFound) {
        // Имя пользователя не найдено, добавляем новую запись
        fileOut << name << " " << score << std::endl;
    }

    fileIn.close();
    fileOut.close();

    // Заменяем исходный файл новым файлом с обновленными данными
    std::remove("scores.txt");
    std::rename("temp.txt", "scores.txt");
}

int StartWrite(const std::string& name1, int score1,const std::string& name2="SecondPlayer", int score2=0) {

    updateScore(name1, score1);
    updateScore(name2, score2);

    return 0;
}

#endif //CHESSJEZZ_WRITESCORE_H
