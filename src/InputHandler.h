#pragma once

#include <thread>
#include <chrono>
#ifdef _WIN32
    #include <windows.h>
#else
    #include <termios.h>
#endif

class InputHandler
{
#ifdef _WIN32
    HANDLE hStdin;
    DWORD originalMode;
#else 
    struct termios original_termios;
#endif
    void restoreConsole();
    void initConsole();
    void enableVirtualTerminal();
public:
    InputHandler()
    {
        initConsole();
        enableVirtualTerminal();
    }
    ~InputHandler()
    { restoreConsole(); }
    
    
    bool kbhit();
    char getch();
    
    void sleepMillis(int ms)
    { std::this_thread::sleep_for(std::chrono::milliseconds(ms)); }
};
