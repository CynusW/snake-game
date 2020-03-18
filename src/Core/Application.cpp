#include "Application.h"

#include "Console.h"

#include "../Snake/Snake.h"

#include <chrono>
#include <algorithm>

#define KEY_PRESSED(x) (GetAsyncKeyState(x) & 0x8000)
#define KEY_A 0x41
#define KEY_D 0x44

Application::Application(int width, int height)
    : m_width(width), m_height(height)
{
    Console::Init(width, height);
    m_buffer = std::make_unique<wchar_t[]>(width * height);
    m_exit = false;
}

Application::~Application()
{

}

void Application::Run()
{
    using snake::Direction;

    bool keyPressed = false;
    snake::Snake snake({ m_width / 4.f, m_height / 2.f });

    auto prev = std::chrono::steady_clock::now();
    while (!m_exit)
    {
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<float> dt = now - prev;

        if (dt.count() < FPS)
        {
            continue;
        }

        prev = now;

        if (!keyPressed)
        {
            if (KEY_PRESSED(VK_LEFT) || KEY_PRESSED(KEY_A))
            {
                snake.Turn(Direction::Left);
                keyPressed = true;
            }

            if (KEY_PRESSED(VK_RIGHT) || KEY_PRESSED(KEY_D))
            {
                snake.Turn(Direction::Right);
                keyPressed = true;
            }
        }

        else
        {
            if (!(KEY_PRESSED(VK_LEFT)  ||
                  KEY_PRESSED(KEY_A)    ||
                  KEY_PRESSED(VK_RIGHT) ||
                  KEY_PRESSED(KEY_D)))
            {
                keyPressed = false;
            }
        }

        snake.Move();

        std::fill_n(m_buffer.get(), m_width * m_height, L' ');

        auto body = snake.GetHead();
        while (body != nullptr)
        {
            m_buffer[(int)body->position.y * m_width + (int)body->position.x] = L'\u2B1C';
            body = body->next;
        }

        Console::Draw(m_buffer.get(), m_width, m_height);
    }
}
