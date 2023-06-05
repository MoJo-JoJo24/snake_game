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

m_display(width, height), m_rand(width, height, block_size), m_player_name(""), 

m_food(0, 0), m_block_size(block_size),m_width(width), m_height(height), 

m_is_accelerate(false), m_is_pause(false), m_framespeed(speed), 

m_acceleration_value(0), m_score(0), m_finalscores()
{
    m_acceleration_options['1'] = 0;
    m_acceleration_options['2'] = 1;
    m_acceleration_options['3'] = 2;

    for (int i = 20; i <= 50; ++i)
    {
        m_speed_options.insert(std::to_string(i));
    }
}
 
DisplayMediator::~DisplayMediator()
{
    m_acceleration_options.clear();
    m_speed_options.clear();
    m_finalscores.clear();
}

std::string DisplayMediator::GetUserInput(std::string msg)
{
    m_display.FillBackGround(sf::Color::Blue);
    m_display.PrintMessage(msg, sf::Color::Red, 24, m_width / 6, m_height / 3);
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
                    if(0 != user_input.size())
                    {
                        auto iter = user_input.end();
                        --iter;
                        user_input.erase(iter);
                    }
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
        m_display.PrintMessage(updated_msg, sf::Color::Red, 24, m_width / 6, m_height / 3);
        m_display.UpdateFrame();
    }

    return user_input;    
}

int DisplayMediator::ResetDisplay()
{
    m_is_accelerate = false;
    m_is_pause = false;
    m_player_name = GetUserInput("New Game Enter name: ");
    std::string mode = GetUserInput("Press Enter or Choose mode 1, 2, 3\n\n1 = Easy Mode with no acceleration\n\n2 = Normal Mode with slow acceleration\n\n3 = Hard Mode with fast acceleration\n\nor press Enter: ");
    std::string speed = GetUserInput("Press Enter or Change Speed\n\nCurrent Speed: "+std::to_string(m_framespeed)+"\n\nEnter a new speed between 20 - 50\n\nor press Enter: ");
    auto speed_iter = m_speed_options.find(speed);
    if (speed_iter != m_speed_options.end())
    {
        m_framespeed = std::stoi(*speed_iter);
    }
    m_acceleration_value = 0;
    auto mode_iter = m_acceleration_options.find(*mode.begin());
    if (mode_iter != m_acceleration_options.end())
    {
        return mode_iter->second;
    }

    m_display.FillBackGround(sf::Color::Blue);
    GenerateFood();
    m_display.UpdateFrame();
    ChangeFrame();

    return 0;
}

void DisplayMediator::ShowManu()
{
    m_display.FillBackGround(sf::Color::Blue);
    std::string str("");
    if (m_is_pause)
    {
        str = "Game Paused! Press Q-Quit or C-Play";
        m_display.PrintMessage(str, sf::Color::Red, 24, m_width / 6, m_height / 3);
    }
    else
    {
        m_display.PrintRows(m_finalscores);
        str = "You Lost! Press Q-Quit or C-Play Again";
        m_display.PrintMessage(str, sf::Color::Red, 24, m_width / 6, m_height / 3);
    }
    str = "Your Score: " + std::to_string(m_score) + "";
    m_display.PrintMessage(str, sf::Color::Yellow, 20, 0, 0, sf::Text::Underlined);
    m_display.UpdateFrame();    
}

KEY DisplayMediator::GetKeyPressed(sf::Event& event)
{
    if (m_display.IsEvent(event) && IsKeyPressed(event))
    {
        return event.key.code;
    }

    return KEY::Unknown; 
}

void DisplayMediator::DisplayFrame(const std::vector<BLOCK2D> &snake)
{
    m_display.FillBackGround(sf::Color::Blue);
    m_display.DrawRec(m_food.first, m_food.second, m_block_size, sf::Color::Green);
    PrintSnake(snake);
    std::string str = "Your Score: " + std::to_string(m_score) + "";
    m_display.PrintMessage(str, sf::Color::Yellow, 20, 0, 0, sf::Text::Underlined);
    str = "Your Speed: " + std::to_string(m_framespeed + m_acceleration_value) + "";
    m_display.PrintMessage(str, sf::Color::Yellow, 20, 200, 0, sf::Text::Underlined);
    m_display.UpdateFrame();    
}

void DisplayMediator::AdjustAcceleration(int acceleration)
{
    if (m_is_accelerate)
    {
        if (m_score % 10 == 0)
        {
            m_acceleration_value += acceleration;
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
    //changed
    m_display.ChangeFrame(m_framespeed + m_acceleration_value);
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
    m_food.first = static_cast<int>((m_rand.GetRandomWidth()) / m_block_size) * m_block_size;
    m_food.second = static_cast<int>((m_rand.GetRandomHeight()) / m_block_size) * m_block_size;
}