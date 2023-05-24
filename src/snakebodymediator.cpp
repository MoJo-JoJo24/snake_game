#include "snakebodymediator.hpp"

SnakeBodyMediator::SnakeBodyMediator(int width, int height):
m_snake(), m_width(width), m_height(height), m_snakehead(width / 2, height / 2),
m_snakedirection(0,0)
{}

SnakeBodyMediator::~SnakeBodyMediator()
{}

void SnakeBodyMediator::ResetPosition()
{
    SetSnakeHead(BLOCK2D(m_width / 2, m_height / 2));
}

void SnakeBodyMediator::ClearSnake()
{
    m_snake.ClearSnake();
}

void SnakeBodyMediator::MoveSnake()
{
    m_snakehead.first += m_snakedirection.first;
    m_snakehead.second += m_snakedirection.second;

    if (0 > m_snakehead.first)
    {
        m_snakehead.first = m_width + m_snakedirection.first;
    }
    else if (m_width == m_snakehead.first)
    {
        m_snakehead.first = 0;
    }

    if (0 > m_snakehead.second)
    {
        m_snakehead.second = m_height + m_snakedirection.second;
    }
    else if (m_height == m_snakehead.second)
    {
        m_snakehead.second = 0;
    }

    m_snake.MoveSnake(m_snakehead);     
}

void SnakeBodyMediator::GrowSnake()
{
    m_snake.GrowSnake(1);
}

bool SnakeBodyMediator::IsMoveValid()
{
    return m_snake.IsSnakeValid();
}

BLOCK2D SnakeBodyMediator::GetDirection()
{
    return m_snakedirection;
}

void SnakeBodyMediator::SetDirection(BLOCK2D direction)
{
    m_snakedirection.first = direction.first;
    m_snakedirection.second = direction.second;
}

BLOCK2D SnakeBodyMediator::GetSnakeHead() const
{
    return m_snakehead;
}

void SnakeBodyMediator::SetSnakeHead(BLOCK2D head)
{
    m_snakehead.first = head.first;
    m_snakehead.second = head.second;
}

const std::vector<BLOCK2D> &SnakeBodyMediator::GetSnake()
{
    return m_snake.GetSnake();
}

int SnakeBodyMediator::GetSnakeLength()
{
    return m_snake.GetLength();
}
