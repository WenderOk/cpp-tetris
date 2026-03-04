#include "console.h"
#include <iostream>
#include <thread>
#include <chrono>

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
    std::cout << "\033[2J\033[1;1H" << std::flush;
}

void sleepMillis(int ms)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

#ifdef _WIN32
static HANDLE hStdin;
static DWORD originalMode;

void initConsole()
{
    hStdin = GetStdHandle(STD_INPUT_HANDLE);
    GetConsoleMode(hStdin, &originalMode);
    DWORD newMode = originalMode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);
    SetConsoleMode(hStdin, newMode);
}

void restoreConsole()
{
    SetConsoleMode(hStdin, originalMode);
}

bool kbhit()
{
    DWORD events;
    GetNumberOfConsoleInputEvents(hStdin, &events);
    return events > 0;
}

char getch()
{
    char ch;
    DWORD read;
    ReadConsole(hStdin, &ch, 1, &read, NULL);
    return ch;
}

#else
static struct termios original_termios;

void initConsole()
{
    tcgetattr(0, &original_termios);
    struct termios newt = original_termios;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(0, TCSANOW, &newt);
}

void restoreConsole()
{
    tcsetattr(0, TCSANOW, &original_termios);
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