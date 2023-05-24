#include "displaymediator.hpp"

RandomPointGenerator::RandomPointGenerator(int width, int height, int block_size_offset):
m_random_seed(), m_random_generator(m_random_seed()), 
m_random_width_range(0, width - block_size_offset), m_random_height_range(0, height - block_size_offset)
{}

RandomPointGenerator::~RandomPointGenerator()
{}

int RandomPointGenerator::GetRandomWidth()
{
    return m_random_width_range(m_random_generator);
}

int RandomPointGenerator::GetRandomHeight()
{
    return m_random_height_range(m_random_generator);
}

DisplayMediator::DisplayMediator(int width, int height, int speed, int block_size):
m_display(width, height, speed), m_rand(width, height, block_size), m_player_name(""), 
m_food(0, 0), m_block_size(block_size), m_is_accelerate(false), m_is_pause(false), 
m_framespeed(speed), m_acceleration_value(0), m_score(0), m_finalscores()
{}

DisplayMediator::~DisplayMediator()
{
    m_finalscores.clear();
}

std::string DisplayMediator::GetUserInput(std::string msg)
{
    m_display.FillBackGround(sf::Color::Blue);
    m_display.Message(msg);
    m_display.UpdateFrame();
    std::string user_input("");
    std::string updated_msg("");
    bool is_running = true;
    while (is_running)
    {
        sf::Event event;
        if (m_display.IsEvent(event))
        {   
            if (IsKeyPressed(event)){
                if (IsBackSpace()){
                    auto iter = user_input.end();
                    --iter;
                    user_input.erase(iter);
                }
                else if (IsEnter()){
                    is_running = false;
                }
                else{
                    user_input += FromKtoS(event.key.code);
                }
            }
        }
        m_display.FillBackGround(sf::Color::Blue);
        updated_msg = msg + user_input;       
        m_display.Message(updated_msg);
        m_display.UpdateFrame();
    }

    return user_input;    
}

bool DisplayMediator::ResetDisplay()
{
    m_is_accelerate = false;
    m_is_pause = false;
    m_player_name = GetUserInput("New Game Enter name: ");
    std::string mode = GetUserInput("New Game Enter 2 For Hard Mode\nor press Enter: ");

    m_display.FillBackGround(sf::Color::Blue);
    m_display.SetFrameSpeed(m_framespeed);

    GenerateFood();
    m_display.UpdateFrame();
    m_display.ChangeFrame(0);

    return '2' == *mode.begin();
}

void DisplayMediator::ShowManu()
{
    m_display.FillBackGround(sf::Color::Blue);
    if (m_is_pause)
    {
        m_display.Message("Game Paused! Press Q-Quit or C-Play");
    }
    else
    {
        m_display.PrintRows(m_finalscores);
        m_display.Message("You Lost! Press Q-Quit or C-Play Again");
    }

    m_display.YourScore(m_score);
    m_display.UpdateFrame();    
}

KEY DisplayMediator::GetKeyPressed()
{
    sf::Event event;
    if (m_display.IsEvent(event) && IsKeyPressed(event))
    {
        return event.key.code;
    }

    return KEY::Unknown; //input to IsContinue in game
}

KEY DisplayMediator::CaptureKeyboardEvent(bool &flag_game_close, bool &flag_game_over)
{
    sf::Event event;
    if (m_display.IsEvent(event)){
        if (IsQuit(event) || IsQ())
            flag_game_over = true;
        
        if (IsKeyPressed(event)){
            if (IsP()){
                flag_game_close = true;
                m_is_pause = true;
            }
            else{
                return event.key.code;
            }
        } 
    }

    return KEY::Unknown; //input to SetNextMove in game
}

void DisplayMediator::DisplayFrame(const std::vector<BLOCK2D> &snake)
{
    m_display.FillBackGround(sf::Color::Blue);
    m_display.DrawRec(m_food.first, m_food.second, m_block_size, sf::Color::Green);
    PrintSnake(snake);
    m_display.YourScore(m_score);
    m_display.YourSpeed();
    m_display.UpdateFrame();    
}

void DisplayMediator::AdjustAcceleration()
{
    m_acceleration_value = 0;
    if (m_is_accelerate)
    {
        if (m_score % 10 == 0)
        {
            m_acceleration_value = 2;
            m_is_accelerate = false;
        }
    }
    else if (m_score % 10 != 0)
    {
        m_is_accelerate = true;
    }    
}

void DisplayMediator::SetScores(std::vector<std::vector<std::string>> finalscores)
{
    m_finalscores = finalscores;
}

void DisplayMediator::SetBlockSize(int block_size)
{
    m_block_size = block_size;
}

BLOCK2D DisplayMediator::GetFood() const
{
    return m_food;
}

std::string &DisplayMediator::GetName()
{
    return m_player_name;
}

int DisplayMediator::GetScore()
{
    return m_score;
}

void DisplayMediator::SetScore(int score)
{
    m_score = score;
}

bool DisplayMediator::IsPause()
{
    return m_is_pause;
}

void DisplayMediator::SetPause(bool status)
{
    m_is_pause = status;
}

void DisplayMediator::ChangeFrame()
{
    m_display.ChangeFrame(m_acceleration_value);
}

void DisplayMediator::PrintSnake(const std::vector<BLOCK2D> &snake)
{
    for (BLOCK2D block : snake)
    {
        m_display.DrawRec(block.first, block.second, m_block_size, sf::Color::Black);
    }    
}

void DisplayMediator::GenerateFood()
{
    m_food.first = static_cast<int>(780 / m_block_size) * m_block_size;
    m_food.second = static_cast<int>(0 / m_block_size) * m_block_size;

    // m_food.first = static_cast<int>((m_rand.GetRandomWidth()) / m_block_size) * m_block_size;
    // m_food.second = static_cast<int>((m_rand.GetRandomHeight()) / m_block_size) * m_block_size;
}