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
        {0,0,0,0},
        {1,1,1,1},
        {0,0,0,0},
        {0,0,0,0} },
    // O
    {
        {0,0,0,0},
        {0,1,1,0},
        {0,1,1,0},
        {0,0,0,0} },
    // T
    {
        {0,0,0,0},
        {0,1,0,0},
        {1,1,1,0},
        {0,0,0,0} },
    // S
    {
         {0,0,0,0},
         {0,1,1,0},
         {1,1,0,0},
         {0,0,0,0} },
    // Z
    {
        {0,0,0,0},
        {1,1,0,0},
        {0,1,1,0},
        {0,0,0,0} },
    // J
    {
        {0,0,0,0},
        {1,0,0,0},
        {1,1,1,0},
        {0,0,0,0} },
    // L
    {
        {0,0,0,0},
        {0,0,1,0},
        {1,1,1,0},
        {0,0,0,0} }
};
    static constexpr int START_X_OFFSETS[7]{2,2,1,1,1,1,1};

    Block(int type, int x, int y);
public:
    Block();
    static Block createRandom(int fieldWidth);
    Block getRotated() const;
    void move(int dx, int dy)
    {
        x += dx;
        y += dy;
    }

    int getType() const
    { return type; }
    int getX() const
    { return  x; }
    int getY() const
    { return y; }
    const std::array<std::array<int, 4>, 4>& getShape() const
    { return shape; }
};