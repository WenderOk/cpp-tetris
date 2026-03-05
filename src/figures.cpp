#include <cstdlib>
#include "field.h"
#include "console.h"

int** rotateShape(int** shape, int height, int width, int& newHeight, int& newWidth)
{
    newHeight = width;
    newWidth = height;
    int** rotated = new int*[newHeight]{};
    for (int i{}; i < newHeight; i++)
        rotated[i] = new int[newWidth]{};
    
    for (int i{}; i < height; i++)
    {
        for (int j{}; j < width; j++)
            if (shape[i][j])
                rotated[j][height - i - 1] = shape[i][j];
    }
    return rotated;
}

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

void freeBlock(Block& block)
{
    if (block.shape)
    {
        for (int i{}; i < block.height; i++)
            delete[] block.shape[i];
        
        delete[] block.shape;
        block.shape = nullptr;
    }
}

void newBlock()
{
    currentBlock.type = rand() % 7;
    currentBlock.rotation = 0;
    currentBlock.x = WIDTH / 2 - baseWidths[currentBlock.type] / 2;
    currentBlock.y = 0;
    currentBlock.height = baseHeights[currentBlock.type];
    currentBlock.width = baseWidths[currentBlock.type];
    currentBlock.shape = new int*[currentBlock.height];

    for (int i{}; i < currentBlock.height; i++)
    {
        currentBlock.shape[i] = new int[currentBlock.width];
        for (int j{}; j < currentBlock.width; j++)
            currentBlock.shape[i][j] = baseFigures[currentBlock.type][i][j];
    }

    if (checkCollision(currentBlock.x, currentBlock.y, currentBlock.shape, currentBlock.height, currentBlock.width))
    {
        freeBlock(currentBlock);
        restoreConsole();
        exit(0);
    }
}

void addBlockToField()
{
    for (int i{}; i < currentBlock.height; i++)
        for (int j{}; j < currentBlock.width; j++)
            if (currentBlock.shape[i][j] && currentBlock.y + i >= 0)
                field[currentBlock.y + i][currentBlock.x + j] = 1;        
}

