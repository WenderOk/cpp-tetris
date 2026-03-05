#pragma once

const int WIDTH{10};
const int HEIGHT{20};

extern int field[HEIGHT][WIDTH];

struct Block
{
    int type;
    int rotation;
    int x, y;
    int** shape;
    int height;
    int width;
};

extern Block currentBlock;

extern const int baseFigures[7][4][4];
extern const int baseHeights[7];
extern const int baseWidths[7];

void clearLines();
void draw();