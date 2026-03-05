#include <iostream>
#include <thread>
#include <chrono>
#include "console.h"

#ifdef _WIN32
    #include <windows.h>
#else
    #include <termios.h>
    #include <unistd.h>
    #include <sys/select.h>
    #include <stdio.h>
#endif

void clearScreen()
{
    #ifdef _WIN32
        std::cout << "\033[H";
    #else
        std::cout << "\033[2J\033[1;1H" << std::flush;
    #endif
}

void sleepMillis(int ms)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

// Настройка термианала для Windows
#ifdef _WIN32
static HANDLE hStdin;
static DWORD originalMode;

void initConsole()
{
    std::cout << "\033[?25l";                                                // для скрытия курсора
    hStdin = GetStdHandle(STD_INPUT_HANDLE);                                 // получение ссылки для управления свойствами ввода
    GetConsoleMode(hStdin, &originalMode);                                   // считывание текущих настроек консоли для дальнейшего восстановления
    DWORD newMode = originalMode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT); // создаем новый режим побитово сбрасив Canonical mode (LINE_INPUT) и Echo (ECHO_INPUT)
    SetConsoleMode(hStdin, newMode);                                         // устанавливаем новый режим
}

// режим виртуального терминала для поддержки escape-последовательностей
void enableVirtualTerminal() 
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);  // получение дескриптора (ссылки) для управления свойствами вывода
    DWORD dwMode{};                                 // объявление переменной типа DWORD для хранения флаги режима консоли
    GetConsoleMode(hOut, &dwMode);                  // считывание текущих настроек консоли для дальнейшего изменения
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;   // добавляем к текущему режиму флаг ENABLE_VIRTUAL_TERMINAL_PROCESSING
    SetConsoleMode(hOut, dwMode);                   // устанавливаем обновленный режим с VIRTUAL_TERMINAL_PROCESSING
}

// возращение консоли в исходное состояние при выходе из игры
void restoreConsole() 
{
    system("cls");
    SetConsoleMode(hStdin, originalMode);
}

#else

// настройка терминала для Linux
static struct termios original_termios;     // сохранение текущих настроек

void initConsole()
{
    tcgetattr(0, &original_termios);            // считываем текущие настройки
    struct termios newTerm = original_termios;  // создаем копию текущих настроек для последующего измения
    newTerm.c_lflag &= ~(ICANON | ECHO);        // побитово сбрасываем Canonical mode (ICANON) и Echo (ECHO)
    tcsetattr(0, TCSANOW, &newTerm);            // применяем новые настройки
}

// возращение консоли в исходное состояние при выходе из игры
void restoreConsole()
{
    tcsetattr(0, TCSANOW, &original_termios);
    clearScreen();
}

bool kbhit()
{
    struct timeval tv = {0, 0};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    select(1, &fds, NULL, NULL, &tv);
    return FD_ISSET(0, &fds);
}

char getch()
{
    char ch;
    read(0, &ch, 1);
    return ch;
}
#endif