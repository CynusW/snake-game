#pragma once

#ifdef SNAKE_PLATFORM_WINDOWS
    #define UNICODE
    #include <windows.h>
#else
    #error This software only supports Windows!
#endif
