#pragma once

#include "../Snake/Snake.h"

#include <memory>
#include <random>

class Application
{
public:
    Application(int width, int height);
    ~Application();

    void Run();

private:
    const float FPS = 1 / 10.f;
    const wchar_t APPLE = L'\u25AB';
    const wchar_t SNAKE_BODY = L'\u2B1C';

    const int m_width;
    const int m_height;

    bool m_exit;

    std::unique_ptr<wchar_t[]> m_buffer;

    snake::Snake m_snake;

    snake::Vector2D m_applePos;

    // Pseudo-random number generator.
    std::mt19937 m_gen;
    std::uniform_int_distribution<int> m_distX;
    std::uniform_int_distribution<int> m_distY;

    void SpawnApple();
    bool IsAppleEaten();

    bool IsSnakeDead();

    inline unsigned int GetIndexFromVector(const snake::Vector2D& vector);
};
