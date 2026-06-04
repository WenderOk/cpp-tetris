#pragma once

#include <iostream>
#include "Block.h"
#include "Field.h"
#include "InputHandler.h"

class Renderer
{
    void clearScreen()
    {
        #ifdef _WIN32
            std::cout << "\033[H";
        #else
            std::cout << "\033[2J\033[1;1H" << std::flush;
        #endif
    }
public:
    void draw(Field& field, Block& block)
    {
        clearScreen();

        int width{field.getWidth()};
        int height{field.getHeight()};

        const auto& grid = field.getGrid(); 

        int bx{block.getX()};
        int by{block.getY()};

        std::array<std::array<int, 4>, 4> shape = block.getShape();

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                bool isDrawn = false;

                // 1. Сначала проверяем, есть ли тут застывший блок
                if (grid[y][x] != 0) {
                    isDrawn = true;
                } 
                // 2. Если нет, проверяем, попадает ли эта ячейка в падающий блок
                else {
                    int localX = x - bx;
                    int localY = y - by;
                    
                    // Если координаты внутри матрицы 4x4 блока и ячейка активна
                    if (localX >= 0 && localX < 4 && localY >= 0 && localY < 4) {
                        if (shape[localY][localX] != 0) {
                            isDrawn = true;
                        }
                    }
                }

                // Выводим символ
                if (isDrawn)
                    std::cout << "# "; // В будущем здесь можно использовать цвета на основе grid[y][x]
                else
                    std::cout << ". ";
                
            }
            std::cout << "\n";
        }
        std::cout << "Use A/D to move, W to rotate, S to drop.\n";
    }
};