#include <iostream>
#include "snake_game.hpp"

SnakeGame::SnakeGame(int width, int height, int speed, int block_size): 
m_width(width), m_height(height), m_speed(speed), m_block_size(block_size),
m_game_over(false), m_game_close(false), m_dis(width, height, speed), m_snake(), 
m_db(), m_random(), m_gen(m_random()), m_distr_x(0, width - block_size), m_distr_y(0, height - block_size)
{
    m_manu_op[m_dis.q] = true;
    m_manu_op[m_dis.c] = false;

    m_moves[m_dis.left].first = -m_block_size;
    m_moves[m_dis.left].second = 0;
    m_invalid_move[-m_block_size][0] = m_dis.right;

    m_moves[m_dis.right].first = m_block_size;
    m_moves[m_dis.right].second = 0;
    m_invalid_move[m_block_size][0] = m_dis.left;


    m_moves[m_dis.up].first = 0;
    m_moves[m_dis.up].second = -m_block_size;
    m_invalid_move[0][-m_block_size] = m_dis.down;

    m_moves[m_dis.down].first = 0;
    m_moves[m_dis.down].second = m_block_size;
    m_invalid_move[0][m_block_size] = m_dis.up;

    while (m_height % m_block_size != 0 && m_width % m_block_size != 0)
    {
        --m_block_size;
    }
}

SnakeGame::~SnakeGame()
{
    m_manu_op.clear();
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

        CaptureKeyboardEvent();

        Move();
        if (!m_snake.IsSnakeValid())
            m_game_close = true;

        DisplayFrame();

        if (IsEat()){
            m_snake.GrowSnake(1);
            GenerateFood();
        }

        AdjustAcceleration();
        m_dis.ChangeFrame(m_acceleration);
    }
}

void SnakeGame::CaptureKeyboardEvent()
{
    sf::Event event;
    if (m_dis.IsEvent(event)){
        if (IsQuit(event) || IsQ())
            m_game_over = true;
        
        if (IsKeyPressed(event)){
            if (IsP()){
                m_game_close = true;
                m_is_pause = true;
            }
            else{
                SetNexMove(event.key.code);
            }
        } 
    }
}

void SnakeGame::GameManu()
{
    if (!m_is_score_updated && !m_is_pause){
        UpdateScore();
        m_is_score_updated = true;
    }
    ShowMenu();
    sf::Event event;
    if (m_dis.IsEvent(event) && 
        IsKeyPressed(event) && 
        IsContinue(event.key.code)){
            if (m_is_pause){
                m_game_close = false;
                m_is_pause = false;
            }
            else{
                RunGame();
            }
    }
}

void SnakeGame::ResetGame()
{
    GetName();
    m_dis.FillBackGround(sf::Color::Blue);
    m_snake.ClearSnake();
    m_dis.SetFrameSpeed(m_speed);
    m_is_accelerate = false;
    m_is_pause = false;
    m_x1 = m_width / 2;
    m_y1 = m_height / 2;
    GenerateFood();
    m_dis.UpdateFrame();
    m_dis.ChangeFrame(0);
}

void SnakeGame::PrintSnake() 
{
    for (BLOCK2D block : m_snake.GetSnake())
    {
        m_dis.DrawRec(block.first, block.second, m_block_size, sf::Color::Black);
    }
}

void SnakeGame::GenerateFood()
{
    m_foodx = static_cast<int>(m_distr_x(m_gen) / m_block_size) * m_block_size;
    m_foody = static_cast<int>(m_distr_y(m_gen) / m_block_size) * m_block_size;
}

void SnakeGame::ShowScoreTable()
{
    std::multimap<int, ROW, std::greater<int>> scores;
    std::vector<ROW> vec = m_db.GETScoreTable();
    for (ROW row : vec)
    {
        scores.insert(std::pair(std::stoi(row.score), row));
    }

    int range = scores.size() > highest_score_rows ? highest_score_rows : scores.size();
    
    auto iter = scores.begin();
    std::vector<std::vector<std::string>> finalists(6);
    ROW header = m_db.FromBuffer(const_cast<char *>(m_db.ReadFromDB(1).c_str()));

    finalists[0].push_back(header.name);
    finalists[0].push_back(header.score);
    finalists[0].push_back(header.date);

    for (int i = 0; i < range; ++i)
    {
        finalists[i + 1].push_back(iter->second.name);
        finalists[i + 1].push_back(iter->second.score);
        finalists[i + 1].push_back(iter->second.date);
        ++iter;
    }

    m_dis.PrintRows(finalists);
} 

void SnakeGame::ShowMenu()
{
    m_dis.FillBackGround(sf::Color::Blue);
    if (m_is_pause)
    {
        m_dis.Message("Game Paused! Press Q-Quit or C-Play");
    }
    else
    {
        ShowScoreTable();
        m_dis.Message("You Lost! Press Q-Quit or C-Play Again");
    }

    m_dis.YourScore(m_snake.GetLength() - 1);
    m_dis.UpdateFrame();
}

bool SnakeGame::IsContinue(KEY key) 
{
    if (m_manu_op.find(key) != m_manu_op.end())
    {
        m_game_over = m_manu_op[key];
        m_game_close = false;
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
        if (keypressed != m_invalid_move[m_x1_change][m_y1_change])
        {
            m_x1_change = m_moves[keypressed].first;
            m_y1_change = m_moves[keypressed].second;         
        }
    }
}

void SnakeGame::Move()
{
    m_x1 += m_x1_change;
    m_y1 += m_y1_change;

    if (0 > m_x1)
    {
        m_x1 = m_width + m_x1_change;
    }
    else if (m_width == m_x1)
    {
        m_x1 = 0;
    }

    if (0 > m_y1)
    {
        m_y1 = m_height + m_y1_change;
    }
    else if (m_height == m_y1)
    {
        m_y1 = 0;
    }

    BLOCK2D head(m_x1, m_y1);
    m_snake.MoveSnake(head);         
}

void SnakeGame::DisplayFrame()
{
    m_dis.FillBackGround(sf::Color::Blue);
    m_dis.DrawRec(m_foodx, m_foody, m_block_size, sf::Color::Green);
    PrintSnake();
    m_dis.YourScore(m_snake.GetLength() - 1);
    m_dis.YourSpeed();
    m_dis.UpdateFrame();
}

bool SnakeGame::IsEat() const
{
    return m_x1 == m_foodx && m_y1 == m_foody;
}

void SnakeGame::GetName()
{
    m_dis.FillBackGround(sf::Color::Blue);
    m_dis.Message("New Game Enter name: ");
    m_dis.UpdateFrame();
    std::string name("");
    bool is_running = true;
    while (is_running)
    {
        sf::Event event;
        if (m_dis.IsEvent(event))
        {   
            if (IsKeyPressed(event)){
                if (IsBackSpace()){
                    auto iter = name.end();
                    --iter;
                    name.erase(iter);
                }
                else if (IsEnter()){
                    is_running = false;
                }
                else{
                    name += FromKtoS(event.key.code);
                }
            }
        }
        m_dis.FillBackGround(sf::Color::Blue);        
        m_dis.Message("New Game Enter name:   " + name + "");
        m_dis.UpdateFrame();
    }
    
    m_player_name = name;
}

void SnakeGame::AdjustAcceleration()
{
    m_acceleration = 0;
    if (m_is_accelerate)
    {
        if (m_snake.GetLength() % 10 == 0)
        {
            m_acceleration = 2;
            m_is_accelerate = false;
        }
    }
    else if (m_snake.GetLength() % 10 != 0)
    {
        m_is_accelerate = true;
    }
}

void SnakeGame::UpdateScore()
{
    ROW line;
    line.date = ScoreDataBase::CurrentDateNTime();
    line.name = m_player_name;
    line.score = std::to_string(m_snake.GetLength() - 1);
    m_db.WriteToDB(line);
}

