#ifndef CONSOLE_H
#define CONSOLE_H

void initConsole();
void restoreConsole();
void clearScreen();
bool kbhit();
char getch();
void sleepMillis(int ms);

#endif