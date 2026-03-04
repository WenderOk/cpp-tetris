#ifndef TETRIS_H
#define TETRIS_H

const int WIDTH = 10;
const int HEIGHT = 20;

extern int field[HEIGHT][WIDTH];

struct Piece
{
    int type;
    int rotation;
    int x, y;
    int** shape;
    int height;
    int width;
};

extern Piece currentPiece;

extern const int baseTetrominoes[7][4][4];
extern const int baseHeights[7];
extern const int baseWidths[7];

bool checkCollision(int x, int y, int** shape, int height, int width);
int** rotateShape(int** shape, int height, int width, int& newHeight, int& newWidth);
void newPiece();
void addPieceToField();
void clearLines();
void draw();
void freePiece(Piece& piece);

#endif