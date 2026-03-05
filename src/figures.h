#pragma once

int** rotateShape(int** shape, int height, int width, int& newHeight, int& newWidth);
bool checkCollision(int x, int y, int** shape, int height, int width);
void freeBlock(Block& block);
void newBlock();
void addBlockToField();