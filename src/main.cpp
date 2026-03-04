#include "tetris.h"
#include "console.h"
#include <cstdlib>
#include <ctime>

#include <chrono>
#include <thread>

int main()
{
    srand(time(nullptr));
    initConsole();
    newPiece();

    const int fallInterval = 500; // миллисекунд между падениями
    auto lastFallTime = std::chrono::steady_clock::now();

    while (true)
    {
        draw();

        // Обработка ввода
        while (kbhit())
        {
            char key = getch();
            if (key == 'a' || key == 'A')
            {
                if (!checkCollision(currentPiece.x - 1, currentPiece.y,
                                    currentPiece.shape, currentPiece.height, currentPiece.width))
                    currentPiece.x -= 1;
            }
            else if (key == 'd' || key == 'D')
            {
                if (!checkCollision(currentPiece.x + 1, currentPiece.y,
                                    currentPiece.shape, currentPiece.height, currentPiece.width))
                    currentPiece.x += 1;
            }
            else if (key == 'w' || key == 'W')
            {
                int newH, newW;
                int** rotated = rotateShape(currentPiece.shape, currentPiece.height,
                                             currentPiece.width, newH, newW);
                if (!checkCollision(currentPiece.x, currentPiece.y, rotated, newH, newW))
                {
                    freePiece(currentPiece);
                    currentPiece.shape = rotated;
                    currentPiece.height = newH;
                    currentPiece.width = newW;
                }
                else
                {
                    for (int i = 0; i < newH; ++i)
                        delete[] rotated[i];
                    delete[] rotated;
                }
            }
            else if (key == 's' || key == 'S')
            {
                // Мгновенное падение (drop)
                while (!checkCollision(currentPiece.x, currentPiece.y + 1,
                                       currentPiece.shape, currentPiece.height, currentPiece.width))
                {
                    currentPiece.y += 1;
                }
                addPieceToField();
                clearLines();
                freePiece(currentPiece);
                newPiece();
                lastFallTime = std::chrono::steady_clock::now(); // сброс таймера
            }
        }

        // Проверка времени для автоматического падения
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastFallTime).count();
        if (elapsed >= fallInterval)
        {
            if (!checkCollision(currentPiece.x, currentPiece.y + 1,
                                currentPiece.shape, currentPiece.height, currentPiece.width))
            {
                currentPiece.y += 1;
            }
            else
            {
                addPieceToField();
                clearLines();
                freePiece(currentPiece);
                newPiece();
            }
            lastFallTime = now;
        }

        // Короткая задержка для снижения нагрузки на процессор
        sleepMillis(20);
    }

    restoreConsole();
    return 0;
}