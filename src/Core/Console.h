#pragma once

#include "Machine.h"

namespace Console
{
#ifdef SNAKE_PLATFORM_WINDOWS
    void Init(int width, int height);
    void Draw(const wchar_t* buffer, int width, int height);
#endif
}

