#include "tetris.h"
#include "console.h"
#include <iostream>
#include <cstdlib>

int field[HEIGHT][WIDTH]{};
Piece currentPiece;

const int baseTetrominoes[7][4][4] = {
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

bool checkCollision(int x, int y, int** shape, int height, int width)
{
    for (int i{}; i < height; i++)
    {
        for (int j{}; j < width; j++)
        {
            if (shape[i][j])
            {
                int newX = x + j;
                int newY = y + i;
                if (newX < 0 || newX >= WIDTH || newY >= HEIGHT)
                    return true;
                if (newY >= 0 && field[newY][newX])
                    return true;
            }
        }
    }
    return false;
}

int** rotateShape(int** shape, int height, int width, int& newHeight, int& newWidth)
{
    newHeight = width;
    newWidth = height;
    int** rotated = new int*[newHeight]{};
    for (int i{}; i < newHeight; i++)
    {
        rotated[i] = new int[newWidth]{};
    }
    for (int i{}; i < height; i++)
    {
        for (int j{}; j < width; j++)
        {
            if (shape[i][j])
            {
                rotated[j][height - i - 1] = shape[i][j];
            }
        }
    }
    return rotated;
}

void freePiece(Piece& piece)
{
    if (piece.shape)
    {
        for (int i{}; i < piece.height; i++)
        {
            delete[] piece.shape[i];
        }
        delete[] piece.shape;
        piece.shape = nullptr;
    }
}

void newPiece()
{
    currentPiece.type = rand() % 7;
    currentPiece.rotation = 0;
    currentPiece.x = WIDTH / 2 - baseWidths[currentPiece.type] / 2;
    currentPiece.y = 0;
    currentPiece.height = baseHeights[currentPiece.type];
    currentPiece.width = baseWidths[currentPiece.type];
    currentPiece.shape = new int*[currentPiece.height];
    for (int i{}; i < currentPiece.height; i++)
    {
        currentPiece.shape[i] = new int[currentPiece.width];
        for (int j{}; j < currentPiece.width; j++)
            currentPiece.shape[i][j] = baseTetrominoes[currentPiece.type][i][j];
    }
    if (checkCollision(currentPiece.x, currentPiece.y, currentPiece.shape, currentPiece.height, currentPiece.width))
    {
        freePiece(currentPiece);
        restoreConsole();
        exit(0);
    }
}

void addPieceToField()
{
    for (int i{}; i < currentPiece.height; i++)
    {
        for (int j{}; j < currentPiece.width; j++)
        {
            if (currentPiece.shape[i][j] && currentPiece.y + i >= 0)
                field[currentPiece.y + i][currentPiece.x + j] = 1;
        }
    }
}

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
    for (int i{}; i < currentPiece.height; i++)
    {
        for (int j{}; j < currentPiece.width; j++)
        {
            if (currentPiece.shape[i][j])
            {
                int y{currentPiece.y + i};
                int x{currentPiece.x + j};
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