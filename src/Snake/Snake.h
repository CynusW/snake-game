#pragma once

namespace snake
{
    struct Vector2D
    {
        float x;
        float y;
    };

    struct SnakeBody
    {
    public:
        Vector2D position;
        SnakeBody* next;

        SnakeBody() : next(nullptr), position() { }
        ~SnakeBody();
    };

    enum class Direction
    {
        Up, Down, Left, Right
    };

    class Snake
    {
    public:
        Snake(const Vector2D& pos, const Direction& facing = Direction::Right);
        ~Snake();

        void Move();
        void Turn(const Direction& direction);
        Vector2D GetVelocity();

        void AddBody() { m_bodyAdded = true; }
        SnakeBody* GetHead() { return m_body; }
        SnakeBody* GetTail();
    
    private:
        Direction m_facing;
        SnakeBody* m_body;
        bool m_bodyAdded;
    };
}

snake::Vector2D operator+(const snake::Vector2D& left, const snake::Vector2D& right);
snake::Vector2D operator-(const snake::Vector2D& left, const snake::Vector2D& right);
snake::Vector2D operator*(float scalar, const snake::Vector2D& vector);
snake::Vector2D operator*(const snake::Vector2D& vector, float scalar);
snake::Vector2D operator/(const snake::Vector2D& vector, float scalar);

snake::Vector2D& operator+=(snake::Vector2D& left, const snake::Vector2D& right);
snake::Vector2D& operator-=(snake::Vector2D& left, const snake::Vector2D& right);
snake::Vector2D& operator*=(snake::Vector2D& vector, float scalar);
snake::Vector2D& operator/=(snake::Vector2D& vector, float scalar);
