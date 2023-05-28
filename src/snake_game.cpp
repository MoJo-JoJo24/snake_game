#include "snake_game.hpp"

SnakeGame::SnakeGame(int width, int height, int speed, int block_size): 
m_acceleration(0), m_game_over(false), m_game_close(false), 
m_is_score_updated(false), m_display_mediator(width, height, speed, block_size),
m_score_db(), m_snake_mediator(width, height)
{
    while (height % block_size != 0 || width % block_size != 0)
    {
        --block_size;
    }
    
    m_manu_options[q_key] = true;
    m_manu_options[c_key] = false;

    m_moves[left_key].first = -block_size;
    m_moves[left_key].second = 0;
    m_invalid_move[-block_size][0] = right_key;

    m_moves[right_key].first = block_size;
    m_moves[right_key].second = 0;
    m_invalid_move[block_size][0] = left_key;


    m_moves[up_key].first = 0;
    m_moves[up_key].second = -block_size;
    m_invalid_move[0][-block_size] = down_key;

    m_moves[down_key].first = 0;
    m_moves[down_key].second = block_size;
    m_invalid_move[0][block_size] = up_key;

    m_display_mediator.SetBlockSize(block_size);
}

SnakeGame::~SnakeGame()
{
    m_manu_options.clear();
    m_moves.clear();
}

void SnakeGame::RunGame()
{
    ResetGame();
    m_is_score_updated = false;
    while (!m_game_over)
    {
        while (m_game_close)
        {
            GameManu();
        }

        SetNexMove(m_display_mediator.CaptureKeyboardEvent(m_game_close, m_game_over));

        m_snake_mediator.MoveSnake();
        if (!m_snake_mediator.IsMoveValid())
            m_game_close = true;

        m_display_mediator.DisplayFrame(m_snake_mediator.GetSnake());

        if (IsEat()){
            m_snake_mediator.GrowSnake();
            m_display_mediator.GenerateFood();
        }

        m_display_mediator.SetScore(m_snake_mediator.GetSnakeLength() - 1);
        
        if (m_acceleration)
        {
           m_display_mediator.AdjustAcceleration(m_acceleration);
        }

        m_display_mediator.ChangeFrame();
    }
}

void SnakeGame::GameManu()
{
    if (!m_is_score_updated && !m_display_mediator.IsPause()){
        m_display_mediator.SetScores(m_score_db.UpdateScoreTable(
                                     m_display_mediator.GetName(), 
                                     m_display_mediator.GetScore()));
        m_is_score_updated = true;
    }

    m_display_mediator.ShowManu();
    if (IsContinue(m_display_mediator.GetKeyPressed()))
    {
        if (m_display_mediator.IsPause())
        {
            m_game_close = false;
            m_display_mediator.SetPause(false);
        }
        else
        {
            RunGame();
        }
    }
}

void SnakeGame::ResetGame()
{
    m_display_mediator.SetScore(m_snake_mediator.GetSnakeLength() - 1);
    m_snake_mediator.ClearSnake();
    m_snake_mediator.ResetPosition();

    m_acceleration = m_display_mediator.ResetDisplay();
}

bool SnakeGame::IsContinue(KEY key) 
{
    if (m_manu_options.find(key) != m_manu_options.end())
    {
        m_game_over = m_manu_options[key];
        m_game_close = false;    // buf = new char [m_row_size + 1];

        if (m_game_over)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    return false;      
}

void SnakeGame::SetNexMove(KEY keypressed)
{
    if (m_moves.find(keypressed) != m_moves.end())
    {
        BLOCK2D direction(m_snake_mediator.GetDirection());
        if (keypressed != m_invalid_move[direction.first][direction.second])
        {
            m_snake_mediator.SetDirection(BLOCK2D(m_moves[keypressed].first, m_moves[keypressed].second));     
        }
    }
}

bool SnakeGame::IsEat() const
{
    return IsSame(m_display_mediator.GetFood(), m_snake_mediator.GetSnakeHead());
}