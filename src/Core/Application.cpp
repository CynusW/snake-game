#include "Application.h"

#include "Machine.h"
#include "Console.h"

#if SNAKE_DEBUG == 1
    #include "Logger.h"
#endif

#include <chrono>
#include <algorithm>

#ifdef SNAKE_PLATFORM_WINDOWS
    #define KEY_PRESSED(x) (GetAsyncKeyState(x) & 0x8000)
    #define KEY_A 0x41
    #define KEY_D 0x44
#endif

Application::Application(int width, int height)
    : m_width(width), m_height(height),
      m_gen(std::chrono::steady_clock::now().time_since_epoch().count()),
      m_distX(0, width), m_distY(0, height),
      m_snake({ m_width / 4.f, m_height / 2.f })
{
    Console::Init(width, height);
    m_buffer = std::make_unique<wchar_t[]>(width * height);
    m_exit = false;

    #if SNAKE_DEBUG == 1
        Logger::Init();
    #endif

    m_applePos = { 3 * width / 4.f, m_height / 2.f };
}

Application::~Application()
{

}

void Application::SpawnApple()
{
    m_applePos = { (float)m_distX(m_gen), (float)m_distY(m_gen) };
}

bool Application::IsAppleEaten()
{
    return GetIndexFromVector(m_snake.GetHead()->position) == GetIndexFromVector(m_applePos);
}

bool Application::IsSnakeDead()
{
    auto head = m_snake.GetHead();
    if (head->position.x <  0.f     ||
        head->position.x >= m_width ||
        head->position.y <  0.f     ||
        head->position.y >= m_height)
    {
        return true;
    }

    auto body = head->next;
    while (body != nullptr)
    {
        if (head->position == body->position)
        {
            return true;
        }

        body = body->next;
    }

    return false;
}

inline unsigned int Application::GetIndexFromVector(const snake::Vector2D& vector)
{
    return ((int)vector.y * m_width + (int)vector.x);
}

void Application::Run()
{
    using snake::Direction;

    bool keyPressed = false;
    Direction turn = Direction::Up;

    auto prev = std::chrono::steady_clock::now();
    while (!m_exit)
    {
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<float> dt = now - prev;

        if (!keyPressed)
        {
            if (KEY_PRESSED(VK_LEFT) || KEY_PRESSED(KEY_A))
            {
                turn = Direction::Left;
                keyPressed = true;
            }

            else if (KEY_PRESSED(VK_RIGHT) || KEY_PRESSED(KEY_D))
            {
                turn = Direction::Right;
                keyPressed = true;
            }
        }

        else if (!(KEY_PRESSED(VK_LEFT)  ||
                   KEY_PRESSED(KEY_A)    ||
                   KEY_PRESSED(VK_RIGHT) ||
                   KEY_PRESSED(KEY_D)))
        {
            keyPressed = false;
        }

        if (dt.count() < FPS)
        {
            continue;
        }

        prev = now;

        m_snake.Turn(turn); turn = Direction::Up;
        m_snake.Move();

        if (IsSnakeDead())
        {
            break;
        }

        if (IsAppleEaten())
        {
            m_snake.AddBody();
            SpawnApple();
        }

        // Clear the screen buffer.
        std::fill_n(m_buffer.get(), m_width * m_height, L' ');

        // Draw the apple.
        m_buffer[GetIndexFromVector(m_applePos)] = APPLE;

        // Draw the snake.
        auto body = m_snake.GetHead();
        while (body != nullptr)
        {
            m_buffer[GetIndexFromVector(body->position)] = SNAKE_BODY;
            body = body->next;
        }

        // Display it to the console.
        Console::Draw(m_buffer.get(), m_width, m_height);

        #if SNAKE_DEBUG == 1
            Logger::Log("Snake: ");
            Logger::Log(m_snake.GetHead()->position.x); Logger::Log(", ");
            Logger::Log(m_snake.GetHead()->position.y); Logger::Log("\n");
        #endif
    }
}
