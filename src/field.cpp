#include <iostream>
#include <cstdlib>
#include "field.h"
#include "console.h"
#include "figures.h"

int field[HEIGHT][WIDTH]{};
Block currentBlock;

const int baseFigures[7][4][4] = {
    // I
    {
        {1,1,1,1},
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0}
    },
    // O
    {
        {1,1,0,0},
        {1,1,0,0},
        {0,0,0,0},
        {0,0,0,0}
    },
    // T
    {
        {0,1,0,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    },
    // S
    {
        {0,1,1,0},
        {1,1,0,0},
        {0,0,0,0},
        {0,0,0,0}
    },
    // Z
    {
        {1,1,0,0},
        {0,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    },
    // J
    {
        {1,0,0,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    },
    // L
    {
        {0,0,1,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    }
};

const int baseHeights[7] = {1,2,2,2,2,2,2};
const int baseWidths[7] = {4,2,3,3,3,3,3};

void clearLines()
{
    for (int i{HEIGHT - 1}; i >= 0; )
    {
        bool full{true};
        for (int j{}; j < WIDTH; j++)
        {
            if (!field[i][j])
            {
                full = false;
                break;
            }
        }
        if (full)
        {
            for (int k{i}; k > 0; k--)
            {
                for (int j{}; j < WIDTH; j++)
                    field[k][j] = field[k-1][j];
            }
            for (int j{}; j < WIDTH; ++j)
                field[0][j] = 0;
        }
        else i--;
    }
}

void draw()
{
    clearScreen();
    // Создаём временную копию поля для отрисовки с текущей фигурой
    int tempField[HEIGHT][WIDTH]{};
    for (int i{}; i < HEIGHT; i++)
        for (int j{}; j < WIDTH; j++)
            tempField[i][j] = field[i][j];

    // Накладываем текущую фигуру
    for (int i{}; i < currentBlock.height; i++)
    {
        for (int j{}; j < currentBlock.width; j++)
        {
            if (currentBlock.shape[i][j])
            {
                int y{currentBlock.y + i};
                int x{currentBlock.x + j};
                if (y >= 0 && y < HEIGHT && x >= 0 && x < WIDTH)
                    tempField[y][x] = 1; // отмечаем клетку как занятую
            }
        }
    }

    // Выводим временное поле
    for (int i{}; i < HEIGHT; i++)
    {
        for (int j{}; j < WIDTH; j++)
        {
            if (tempField[i][j])
                std::cout << "# ";
            else
                std::cout << ". ";
        }
        std::cout << "\n";
    }
    std::cout << "Use A/D to move, W to rotate, S to drop.\n";
}