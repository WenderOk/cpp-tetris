#include "Field.h"
#include "Block.h"


int Field::clearLines()
{
    int linesCleared{};
    for (int i{HEIGHT - 1}; i >= 0; )
    {
        bool full{true};
        for (int j{}; j < WIDTH; j++)
        {
            if (!grid[i][j])
            {
                full = false;
                break;
            }
        }
        if (full)
        {
            linesCleared++;
            for (int k{i}; k > 0; k--)
                for (int j{}; j < WIDTH; j++)
                    grid[k][j] = grid[k-1][j];
            
            for (int j{}; j < WIDTH; ++j)
                grid[0][j] = 0;
        }
        else i--;
    }
    return linesCleared;
}

void Field::lockBlock(Block& block)
{
    for (int i{}; i < 4; i++)
    {
        for (int j{}; j < 4; j++)
        {
            if (block.getShape()[i][j])
            {
                int y{block.getY() + i};
                int x{block.getX() + j};
                if (y >= 0 && y < HEIGHT && x >= 0 && x < WIDTH)
                    grid[y][x] = block.getType() + 1; // отмечаем клетку как занятую
            }
        }
    }
}

bool Field::hasCollision(Block& block, int offsetX, int offsetY) const
{
    for (int i{}; i < 4; i++)
    {
        for (int j{}; j < 4; j++)
        {
            if (block.getShape()[i][j])
            {
                int newX = block.getX() + offsetX + j;
                int newY = block.getY() + offsetY + i;
                if (newX < 0 || newX >= WIDTH || newY >= HEIGHT)
                    return true;
                if (newY >= 0 && grid[newY][newX])
                    return true;
            }
        }
    }
    return false;
}

