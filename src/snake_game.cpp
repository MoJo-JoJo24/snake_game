#include "snake_game.hpp"


SnakeGame::SnakeGame(int width, int height, int speed, int block_size): 
m_acceleration(0), m_game_over(false), m_game_close(false), m_player_name(""), m_score_db(),
m_display_controller(width, height, speed, block_size), m_snake_controller(width, height)
{
    //block_size is adjusted to be a multiple of both the width and height limits.
    while (height % block_size != 0 || width % block_size != 0)
    {
        --block_size;
    }

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

    m_display_controller.SetBlockSize(block_size);

    for (int i = 1; i <= 50; ++i)
    {
        m_speed_options.insert(std::to_string(i));
    }    
}

SnakeGame::~SnakeGame()
{
    m_moves.clear();
    m_invalid_move.clear();
    m_speed_options.clear();
}

void SnakeGame::RunGame()
{
    SetGame();
    
    while (!m_game_over)
    {
        if (m_game_close)
        {
            if (!m_display_controller.IsPause())
            {
               UpdateTopScores();
            }

            m_display_controller.ShowManu(m_score_db.GetTopScores());

            while (m_game_close)
            {
                GetManuOption();
            }
        }
        char key_pressed = m_display_controller.GetEvent();
        if (key_pressed)
        {
            if (q_key == key_pressed)
            {
                m_game_over = true;
            }
            else if (p_key == key_pressed)
            {
                m_game_close = true;
                m_display_controller.SetPause(true);
            }
            else
            {
                RegisterNexMove(key_pressed);
            }
        }

        BLOCK2D shadow_tail = m_snake_controller.GetSnakeTail();
        m_snake_controller.MoveSnake();
        if (!m_snake_controller.IsValidSnake())
        {
            m_game_close = true;
        }

        DisplayFrame(shadow_tail);

        if (IsEat())
        {
            m_snake_controller.GrowSnake();
            m_display_controller.SetScore(m_snake_controller.GetSnakeLength() - 1);

            if (m_acceleration)
            {
                m_display_controller.AdjustAcceleration(m_acceleration);
            }

            m_display_controller.GenerateFood();

        }
        m_display_controller.ChangeFramesPer();
    }
}

void SnakeGame::DisplayFrame(BLOCK2D &shadow_tail)
{
    const std::vector<BLOCK2D> &snake = m_snake_controller.GetSnake();
    BLOCK2D direction = m_snake_controller.GetNextMove();
    m_display_controller.DisplayFrame(snake, direction, shadow_tail);
}

void SnakeGame::GetManuOption()
{
    char key_pressed = m_display_controller.GetEvent();

    if (key_pressed)
    {
        if (IsContinue(key_pressed))
        {
            if (m_display_controller.IsPause())
            {
                m_game_close = false;
                m_display_controller.SetPause(false);
            }
            else
            {
                RunGame();
            }
        }
    }
}

void SnakeGame::SetGame()
{
    m_snake_controller.ClearSnake();
    m_display_controller.SetScore(m_snake_controller.GetSnakeLength() - 1);
    m_snake_controller.ResetPosition();
    m_snake_controller.MoveSnake();

    m_display_controller.ResetDisplay();

    m_player_name = m_display_controller.GetUserInput("New Game Enter name: ");   
    std::string mode = m_display_controller.GetUserInput("Press Enter to continue or Choose mode 1, 2, or 3\n\n\n\n1 = no acceleration\n\n2 = slow acceleration\n\n3 = fast acceleration\n\nor press Enter: ");
    std::string speed = m_display_controller.GetUserInput("Press Enter to continue or Change Speed\n\n\n\nCurrent Speed: "+std::to_string(m_display_controller.GetFrameSpeed())+"\n\nEnter a new speed between 1 - 50\n\nor press Enter: ");
    
    auto speed_iter = m_speed_options.find(speed);
    if (speed_iter != m_speed_options.end())
    {
        m_display_controller.SetFrameSpeed(std::stoi(*speed_iter));
    }

    if (mode == "1" || mode == "2" || mode == "3")
    {
        m_acceleration = std::stoi(mode) - 1;
    }
}

bool SnakeGame::IsContinue(char key) 
{
    if (c_key ==  key || q_key ==  key)
    {
        m_game_close = false;   

        if (q_key ==  key)
        {
            m_game_over = true;
            return false;
        }
        else
        {
            return true;
        }
    }

    return false;      
}

void SnakeGame::RegisterNexMove(char keypressed)
{
    if (m_moves.find(keypressed) != m_moves.end())
    {
        BLOCK2D direction(m_snake_controller.GetNextMove());
        if (keypressed != m_invalid_move[direction.first][direction.second])
        {
            m_snake_controller.SetNextMove(BLOCK2D(m_moves[keypressed].first, m_moves[keypressed].second));     
        }
    }
}

void SnakeGame::UpdateTopScores()
{
    m_score_db.UpdateScoreTable(m_player_name, m_display_controller.GetScore());
}

bool SnakeGame::IsEat() const
{
    return IsSame(m_display_controller.GetFood(), m_snake_controller.GetSnakeHead());
}