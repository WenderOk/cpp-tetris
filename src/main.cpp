#ifdef _WIN32
    #include <windows.h>
    #include <conio.h>
#endif

#include "Game.h"

int main() {
    Game game;
    game.run();
    return 0; // Деструктор InputHandler автоматически восстановит консоль!
}