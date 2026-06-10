#pragma once

#include <array>
#include <iostream>
#include <iomanip>
#include "Block.h"
#include "Field.h"
#include "InputHandler.h"
#include "Colors.h"

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

        std::cout << "\n   ";
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
            std::cout << "\n   ";
        }

        std::cout << "\n";
        
        std::cout << "   " << CYAN << std::setfill('=') << std::setw(22) << "" << RESET << "\n";
        
        std::cout << std::setfill(' ');

        std::cout << "   " << YELLOW << "SCORE:" << RESET << " " 
                << std::left  << std::setw(5) << score 
                << YELLOW << "LEVEL:" << RESET << " " 
                << std::right << std::setw(2) << level << "\n";
                
        std::cout << "   " << YELLOW << "LINES:" << RESET << " " 
                << std::left  << std::setw(5) << linesCleared << "\n";
                
        std::cout << "   " << CYAN << std::setfill('=') << std::setw(22) << "" << RESET << "\n";
        
        std::cout << std::setfill(' ');
        std::cout << "   " 
                << GRAY << "[A/D]" << RESET << " Mv " 
                << GRAY << "[W]"   << RESET << " Rot " 
                << GRAY << "[S]"   << RESET << " Drp " 
                << GRAY << "[F]"   << RESET << " Psz\n";
    }
};