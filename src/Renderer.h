#pragma once

#include <array>
#include <iostream>
#include <iomanip>
#include "Block.h"
#include "Field.h"
#include "InputHandler.h"

class Renderer
{
public:
    void clearScreen() const
    {
        #ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        
        if (GetConsoleScreenBufferInfo(hConsole, &csbi)) 
        {
            DWORD cellCount = csbi.dwSize.X * csbi.dwSize.Y;
            DWORD cellsWritten;
            COORD topLeft = {0, 0};
            SetConsoleCursorPosition(hConsole, topLeft);
        }
        #else
            std::cout << "\033[2J\033[1;1H" << std::flush;
        #endif
    }
    
    void draw(const Field& field, const Block& block, int score, int level, int linesCleared) const
    {
        clearScreen();

        int width{field.getWidth()};
        int height{field.getHeight()};

        const auto& grid = field.getGrid(); 

        int bx{block.getX()};
        int by{block.getY()};

        const std::array<std::array<int, 4>, 4>& shape = block.getShape();

        for (int y{0}; y < height; ++y) 
        {
            for (int x{0}; x < width; ++x) 
            {
                bool isDrawn = false;
                int colorCode{};

                // 1. Сначала проверяем, есть ли тут застывший блок
                if (grid[y][x] != 0)
                {
                    isDrawn = true;
                    colorCode = grid[y][x];
                }
                // 2. Если нет, проверяем, попадает ли эта ячейка в падающий блок
                else 
                {
                    int localX{x - bx};
                    int localY{y - by};
                    
                    // Если координаты внутри матрицы 4x4 блока и ячейка активна
                    if (localX >= 0 && localX < 4 && localY >= 0 && localY < 4) 
                        if (shape[localY][localX] != 0)
                        {
                            isDrawn = true;
                            colorCode = block.getType() + 1;
                        }
                }
                
                // Выводим символ
                if (isDrawn)
                    std::cout << "\033[4" << colorCode << ";3" << colorCode << "m" << "# \033[0m";
                else
                    std::cout << " .";
                
            }
            std::cout << "\n";
        }
        std::cout << "\n";
        std::cout << "   \033[1;36m----------------------\033[0m\n";
        std::cout << "   \033[1;33m SCORE:\033[0m " << std::setw(6) << score 
                << "  \033[1;33mLEVEL:\033[0m " << level << "\n";
        std::cout << "   \033[1;33m LINES:\033[0m " << std::setw(5) << linesCleared << "\n";
        std::cout << "   \033[1;36m----------------------\033[0m\n";
        std::cout << "   \033[90m[A/D]\033[0m Move  \033[90m[W]\033[0m Rotate  \033[90m[S]\033[0m Drop  \033[90m[F]\033[0m Pause\n";
    }
};