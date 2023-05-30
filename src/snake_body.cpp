#include "snake_body.hpp"

SnakeBody::SnakeBody(): m_snake_length(1)
{}

SnakeBody::~SnakeBody()
{
    m_snake.clear();
}

int SnakeBody::GetLength() const
{
    return m_snake_length;
}

const std::vector<BLOCK2D>& SnakeBody::GetSnake() const
{
    return m_snake;
}

bool SnakeBody::IsSnakeValid() const
{
    BLOCK2D head = m_snake[m_snake_length - 1];
    for (int i = 0; i < m_snake_length - 1; ++i)
    {
        if (IsSame(head, m_snake[i]))
        {
            return false; 
        }
    }

    return true;
}


void SnakeBody::MoveSnake(BLOCK2D head)
{
    m_snake.push_back(head);
    if ((std::size_t)m_snake_length < m_snake.size())
    {
        m_snake.erase(m_snake.begin());
    }
}

void SnakeBody::GrowSnake(int amount)
{
    m_snake_length += amount;
}

void SnakeBody::ClearSnake()
{
    m_snake.clear();
    m_snake_length = 1;
}

bool IsSame(const BLOCK2D a, const BLOCK2D b)
{
    return a.first == b.first && a.second == b.second;
}
