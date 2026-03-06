#include <cstdlib>
#include "field.h"
#include "console.h"
#include "figures.h"

#ifdef _WIN32
    #include <windows.h>
    #include <conio.h>
#endif

#include <chrono>
#include <thread>

int main()
{
    // Если Windows очищаем экран при запуске и включаем поддержку вирутуального терминала
    #ifdef _WIN32
    system("cls");
    enableVirtualTerminal();
    #endif
    srand(time(nullptr));
    initConsole();
    newBlock();

    const int fallInterval{500}; // миллисекунд между падениями
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
                if (!checkCollision(currentBlock.x - 1, currentBlock.y,
                                    currentBlock.shape, currentBlock.height, currentBlock.width))
                    currentBlock.x -= 1;
            }
            else if (key == 'd' || key == 'D')
            {
                if (!checkCollision(currentBlock.x + 1, currentBlock.y,
                                    currentBlock.shape, currentBlock.height, currentBlock.width))
                    currentBlock.x += 1;
            }
            else if (key == 'w' || key == 'W')
            {
                int newH{};
                int newW{};
                int** rotated = rotateShape(currentBlock.shape, currentBlock.height,
                                             currentBlock.width, newH, newW);
                if (!checkCollision(currentBlock.x, currentBlock.y, rotated, newH, newW))
                {
                    freeBlock(currentBlock);
                    currentBlock.shape = rotated;
                    currentBlock.height = newH;
                    currentBlock.width = newW;
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
                while (!checkCollision(currentBlock.x, currentBlock.y + 1, currentBlock.shape, currentBlock.height, currentBlock.width))
                    currentBlock.y += 1;
                
                addBlockToField();
                clearLines();
                freeBlock(currentBlock);
                newBlock();
                lastFallTime = std::chrono::steady_clock::now(); // сброс таймера
            }
        }

        // Проверка времени для автоматического падения
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastFallTime).count(); // вычисляет интервал с последнего тика и преобразует его сначала в миллесекунды а потом в число
        if (elapsed >= fallInterval)
        {
            if (!checkCollision(currentBlock.x, currentBlock.y + 1, currentBlock.shape, currentBlock.height, currentBlock.width))
                currentBlock.y += 1;
            else
            {
                addBlockToField();
                clearLines();
                freeBlock(currentBlock);
                newBlock();
            }
            lastFallTime = now;
        }

        // Короткая задержка для снижения нагрузки на процессор
        sleepMillis(20);
    }

    restoreConsole();
    return 0;
}