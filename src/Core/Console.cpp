#include "Console.h"

#include <iostream>

#if SNAKE_PLATFORM_WINDOWS
    static HANDLE hConsole;

    void Console::Init(int width, int height)
    {
        hConsole = CreateConsoleScreenBuffer(
            GENERIC_READ | GENERIC_WRITE,
            0,
            NULL,
            CONSOLE_TEXTMODE_BUFFER,
            NULL
        );

        if (hConsole == INVALID_HANDLE_VALUE)
        {
            std::cerr << "Failed to create console screen buffer!" << std::endl;
        }

        SetConsoleScreenBufferSize(
            hConsole,
            { (SHORT)width, (SHORT)height }
        );

        SetConsoleActiveScreenBuffer(hConsole);
    }

    void Console::Draw(const wchar_t* buffer, int width, int height)
    {
        DWORD dWritten;
        WriteConsoleOutputCharacter(
            hConsole,
            buffer,
            width * height,
            { 0, 0 },
            &dWritten
        );
    }
#endif
