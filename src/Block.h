#pragma once

#include <array>

class Block
{
    int type;
    int rotation;
    int x, y;
    std::array<std::array<int, 4>, 4> shape;

    static constexpr int SHAPES[7][4][4]{
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
    }};
    static constexpr int START_X_OFFSETS[7]{4,2,3,3,3,3,3};
    static constexpr int START_Y_OFFSETS[7]{1,2,2,2,2,2,2};

    Block(int type, int x, int y);
public:
    Block createRandom(int fieldWidth);
    Block rotate();
    void move();
    int getX()
    { return  x; }
    int getY()
    { return y; }
    std::array<std::array<int, 4>, 4>& getShape()
    { return shape; }
};