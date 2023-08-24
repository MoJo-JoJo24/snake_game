#include "snakecontroller.hpp"

SnakeBodyMediator::SnakeBodyMediator(int width, int height):
m_snake(), m_snake_length(1), m_width(width), m_height(height), 
m_snake_head(width / 2, height / 2), m_next_move(0,0)
{}

SnakeBodyMediator::~SnakeBodyMediator()
{}

void SnakeBodyMediator::ResetPosition()
{
    SetSnakeHead(BLOCK2D(m_width / 2, m_height / 2));
    SetNextMove(BLOCK2D(0, 0));
}

void SnakeBodyMediator::ClearSnake()
{
    m_snake.clear();
    m_snake_length = 1;
}

void SnakeBodyMediator::MoveSnake()
{
    m_snake_head.first += m_next_move.first;
    m_snake_head.second += m_next_move.second;
    
    if (0 > m_snake_head.first)
    {
        m_snake_head.first = m_width + m_next_move.first;
    }
    else if (m_width == m_snake_head.first)
    {
        m_snake_head.first = 0;
    }

    if (0 > m_snake_head.second)
    {
        m_snake_head.second = m_height + m_next_move.second;
    }
    else if (m_height == m_snake_head.second)
    {
        m_snake_head.second = 0;
    }

    m_snake.push_back(m_snake_head);
    if ((std::size_t)m_snake_length < m_snake.size())
    {
        m_snake.erase(m_snake.begin());
    }    
}

void SnakeBodyMediator::GrowSnake()
{
    m_snake_length += 1;
}

bool SnakeBodyMediator::IsValidSnake()
{
    for (std::size_t i = 0; i < m_snake.size() - 1; ++i)
    {
        if (IsSame(m_snake_head, m_snake[i]))
        {
            return false; 
        }
    }

    return true;
}

BLOCK2D SnakeBodyMediator::GetNextMove()
{
    return m_next_move;
}

void SnakeBodyMediator::SetNextMove(BLOCK2D next_move)
{
    m_next_move.first = next_move.first;
    m_next_move.second = next_move.second;
}

BLOCK2D SnakeBodyMediator::GetSnakeHead() const
{
    return m_snake_head;
}

BLOCK2D SnakeBodyMediator::GetSnakeTail() const
{
    return m_snake[0];
}


void SnakeBodyMediator::SetSnakeHead(BLOCK2D head)
{
    m_snake_head.first = head.first;
    m_snake_head.second = head.second;
}

const std::vector<BLOCK2D> &SnakeBodyMediator::GetSnake()
{
    return m_snake;
}

int SnakeBodyMediator::GetSnakeLength()
{
    return m_snake_length;
}

bool IsSame(const BLOCK2D a, const BLOCK2D b)
{
    return a.first == b.first && a.second == b.second;
}