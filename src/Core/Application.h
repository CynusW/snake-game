#pragma once

#include <memory>

class Application
{
public:
    Application(int width, int height);
    ~Application();

    void Run();

private:
    const float FPS = 1 / 20.f;

    const int m_width;
    const int m_height;

    bool m_exit;

    std::unique_ptr<wchar_t[]> m_buffer;
};
