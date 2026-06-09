#pragma once
#include <fstream>
#include <string>
#include <algorithm>

namespace HighScoreManager 
{
    const std::string FILENAME = "highscore";

    // Загружает рекорд из файла. Если файла нет, возвращает 0.
    inline int load() 
    {
        std::ifstream file(FILENAME);
        int score{};
        if (file.is_open()) 
        {
            file >> score;
            file.close();
        }
        return score;
    }

    // Сохраняет новый рекорд, если он больше старого
    inline void saveIfHigher(int newScore) 
    {
        int currentHigh = load();
        if (newScore > currentHigh) 
        {
            std::ofstream file(FILENAME);
            if (file.is_open()) 
            {
                file << newScore;
                file.close();
            }
        }
    }
}