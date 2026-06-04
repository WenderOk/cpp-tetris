#include <array>
#include <cstdlib>
#include "Block.h"

Block Block::createRandom(int fieldWidth)
{
    int randomType{ rand() % 7 };
    int startX{ fieldWidth / 2 - START_X_OFFSETS[randomType] };
    int startY{};
    return Block{randomType, startX, startY};
}

Block::Block(int typep, int xp, int yp)
: type{typep}, rotation{}, x{xp}, y{yp}
{    
    for (int i{}; i < 4; i++)
        for (int j{}; j < 4; j++)
            shape[i][j] = SHAPES[type][i][j];
}

Block Block::getRotated() const
{
    std::array<std::array<int, 4>, 4> rotated = std::array<std::array<int, 4>, 4>{};
    
    for (int i{}; i < 4; i++)
    {
        for (int j{}; j < 4; j++)
            if (shape[i][j])
                rotated[j][4 - i - 1] = shape[i][j];
    }
    Block rotatedBlock{Block{type, x, y}};
    rotatedBlock.shape = rotated;
    return rotatedBlock;
}