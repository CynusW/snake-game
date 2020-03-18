#include "Snake.h"

namespace snake
{
    SnakeBody::~SnakeBody()
    {
        if (next != nullptr)
        {
            delete next;
        }
    }

    Snake::Snake(const Vector2D& pos, const Direction& facing)
    {
        SnakeBody* body = new SnakeBody();
        body->next = new SnakeBody();
        body->next->next = new SnakeBody();

        body->position = pos;
        switch (facing)
        {
        case Direction::Up:
            body->next->position = { pos.x, pos.y - 1};
            body->next->next->position = { pos.x, pos.y - 2};
            break;
        case Direction::Down:
            body->next->position = { pos.x, pos.y + 1};
            body->next->next->position = { pos.x, pos.y + 2};
            break;
        case Direction::Left:
            body->next->position = { pos.x + 1, pos.y };
            body->next->next->position = { pos.x + 2, pos.y };
            break;
        case Direction::Right:
        default:
            body->next->position = { pos.x - 1, pos.y };
            body->next->next->position = { pos.x - 2, pos.y };
            break;
        }

        m_body = body;
        m_facing = facing;
        m_bodyAdded = false;
    }

    Snake::~Snake()
    {
        delete m_body;
        m_body = nullptr;
    }

    void Snake::Move()
    {
        Vector2D velocity = GetVelocity();

        SnakeBody* newBody = new SnakeBody();
        newBody->position = m_body->position + velocity;
        newBody->next = m_body;
        m_body = newBody;

        if (!m_bodyAdded)
        {
            auto pretail = m_body;
            while (pretail->next->next != nullptr)
            {
                pretail = pretail->next;
            }

            delete GetTail();
            pretail->next = nullptr;
        }

        else m_bodyAdded = false;
    }

    void Snake::Turn(const Direction& direction)
    {
        if (direction == Direction::Left)
        {
            switch (m_facing)
            {
            case Direction::Up:
                m_facing = Direction::Left;
                break;
            case Direction::Down:
                m_facing = Direction::Right;
                break;
            case Direction::Left:
                m_facing = Direction::Down;
                break;
            case Direction::Right:
                m_facing = Direction::Up;
                break;
            }
        }

        else if (direction == Direction::Right)
        {
            switch (m_facing)
            {
            case Direction::Up:
                m_facing = Direction::Right;
                break;
            case Direction::Down:
                m_facing = Direction::Left;
                break;
            case Direction::Left:
                m_facing = Direction::Up;
                break;
            case Direction::Right:
                m_facing = Direction::Down;
                break;
            }
        }
    }

    Vector2D Snake::GetVelocity()
    {
        Vector2D velocity = { };

        switch (m_facing)
        {
        case Direction::Up:
            velocity.y = -0.5f;
            break;
        case Direction::Down:
            velocity.y =  0.5f;
            break;
        case Direction::Right:
            velocity.x =  1.0f;
            break;
        case Direction::Left:
            velocity.x = -1.0f;
            break;
        }

        return velocity;
    }

    SnakeBody* Snake::GetTail()
    {
        SnakeBody* tail = m_body;
        while (tail->next != nullptr)
        {
            tail = tail->next;
        }

        return tail;
    }
}


snake::Vector2D operator+(const snake::Vector2D& left, const snake::Vector2D& right)
{
    return { left.x + right.x, left.y + right.y };
}

snake::Vector2D operator-(const snake::Vector2D& left, const snake::Vector2D& right)
{
    return { left.x - right.x, left.y - right.y };
}

snake::Vector2D operator*(float scalar, const snake::Vector2D& vector)
{
    return { scalar * vector.x, scalar * vector.y };
}

snake::Vector2D operator*(const snake::Vector2D& vector, float scalar)
{
    return { scalar * vector.x, scalar * vector.y };
}

snake::Vector2D operator/(const snake::Vector2D& vector, float scalar)
{
    return { vector.x / scalar, vector.y / scalar };
}

snake::Vector2D& operator+=(snake::Vector2D& left, const snake::Vector2D& right)
{
    left.x += right.x; left.y += right.y;
    return left;
}

snake::Vector2D& operator-=(snake::Vector2D& left, const snake::Vector2D& right)
{
    left.x -= right.x; left.y -= right.y;
    return left;
}

snake::Vector2D& operator*=(snake::Vector2D& vector, float scalar)
{
    vector.x *= scalar; vector.y *= scalar;
    return vector;
}

snake::Vector2D& operator/=(snake::Vector2D& vector, float scalar)
{
    vector.x /= scalar; vector.y /= scalar;
    return vector;
}

