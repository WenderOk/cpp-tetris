#pragma once

void initConsole();
void enableVirtualTerminal();
void restoreConsole();
void clearScreen();
#ifndef _WIN32
    bool kbhit();
    char getch();
#endif
void sleepMillis(int ms);