#pragma once

#include "Block.h"
#include <array>

class Field
{
    static constexpr int WIDTH{10};
    static constexpr int HEIGHT{20};
    std::array<std::array<int, WIDTH>, HEIGHT> grid;
public:
    int clearLines();
    void lockBlock(Block& block);
    bool hasCollision(Block& block, int offsetX, int offsetY) const;

    int getWidth() const
    { return WIDTH; }
    int getHeight()
    { return HEIGHT; }
    const std::array<std::array<int, WIDTH>, HEIGHT>& getGrid() const
    { return grid; }
};

