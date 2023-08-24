#include <unistd.h> // for using usleep on Unix-like systems

#include "displaycontroller.hpp"

DisplayController::DisplayController(int width, int height, int speed, int block_size):
m_rand(width, height, block_size), m_food(width / 3, height / 3), 
m_block_size(block_size), m_width(width), m_height(height), 
m_is_pause(false), m_framespeed(speed), m_acceleration_value(0), m_score(0)
{
    system("/bin/stty -icanon -echo");

    printf("\x1B[?25l");
}
 
DisplayController::~DisplayController()
{
    system("/bin/stty icanon echo");

    printf("\x1B[?25h");

}

std::string DisplayController::GetUserInput(std::string msg)
{
    printf("%s", msg.c_str());
    
    std::string user_input("");
    std::string updated_msg("");
    
    while (GetInput(user_input))
    {
        system("clear");
        updated_msg = msg + user_input;
        printf("%s\n", updated_msg.c_str());   
        ChangeFramesPer();    
    }

    return user_input;    
}

bool DisplayController::GetInput(std::string& user_input)
{
 
    char key_pressed = GetEvent();
    if (key_pressed) {
        if (backspace_key == key_pressed){
            if(0 != user_input.size())
            {
                auto iter = user_input.end();
                --iter;
                user_input.erase(iter);
            }
        }
        else if (enter_key == key_pressed)
        {
            return false;
        }
        else
        {
            user_input += key_pressed;
        }
    }
    

    return true;
}

void DisplayController::ResetDisplay()
{
    m_is_pause = false; 
    m_acceleration_value = 0;
}

void DisplayController::ShowManu(std::vector<std::vector<std::string>> &m_top_scores)
{
    system("clear"); // Use "cls" on Windows

    std::string str("");
    if (m_is_pause)
    {
        str = "\nGame Paused! Press Q-Quit or C-Play";
    }
    else
    {
        PrintRows(m_top_scores);
        
        str = "\nYou Lost! Press Q-Quit or C-Play Again";
    }
    
    str += " \nYour Score: " + std::to_string(m_score) + "";
    printf("%s\n", str.c_str());
}

void DisplayController::DisplayFrame(const std::vector<BLOCK2D> &snake, BLOCK2D direction, BLOCK2D shadow_tail)
{
    std::string str("Your Score: " + std::to_string(m_score) + "");
    const char *score_header =  str.c_str();
    for (int frame = 0; frame < BLOCK_SLICES; ++frame)
    {
        system("clear"); // Use "cls" on Windows
        printf("%s\n", score_header);
        for (int i = 0; i < m_height; i++) {
            for (int j = 0; j < m_width; j++) {
                int isSnakeBody = 0;
                size_t k = 0;
                for (; k < snake.size(); k++) {
                    if (snake[k].first == j && snake[k].second == i) {
                        isSnakeBody = 1;
                        break;
                    }
                }
                if (isSnakeBody)
                    if (snake.size() - 1 == k)
                    {
                        PrintSnakeHead(direction, frame);
                    }
                    else
                    {
                        printf(ANSI_COLOR_YELLOW "%s" ANSI_COLOR_RESET, full_block);

                    }
                else if (m_food.first == j && m_food.second == i)
                    printf(ANSI_COLOR_GREEN "%s" ANSI_COLOR_RESET, "\u25C9"); 
                else if (shadow_tail.first == j && shadow_tail.second == i)
                    PrintSnakeTail(snake[0], frame, shadow_tail);     
                else
                    printf("%s", "*");
            }
            printf("\n");
        }
        usleep(10000); 
    }   
}

void DisplayController::AdjustAcceleration(int acceleration)
{
    if (m_score % 10 == 0)
    {
        m_acceleration_value += acceleration;
    }   
}

void DisplayController::PrintSnakeHead(BLOCK2D direction, int index)
{

    if (0 < direction.first && 0 == direction.second)
    {
        printf(ANSI_COLOR_YELLOW "%s" ANSI_COLOR_RESET, block_left_right[index]);
    }
    else if (0 > direction.first && 0 == direction.second)
    {
        printf(ANSI_COLOR_YELLOW "%s" ANSI_COLOR_RESET, block_right_left[index]); 
    }
    else if(0 == direction.first && 0 > direction.second)
    {
        printf(ANSI_COLOR_YELLOW "%s" ANSI_COLOR_RESET, block_bottom_up[index]);
    }
    else if(0 == direction.first && 0 < direction.second)
    {
        printf(ANSI_COLOR_YELLOW "%s" ANSI_COLOR_RESET, block_up_bottom[index]);       
    }
}

void DisplayController::PrintSnakeTail(BLOCK2D tail, int index, BLOCK2D shadow_tail)
{
    double x_position = shadow_tail.first;
    double y_position = shadow_tail.second;

    if (!IsSame(shadow_tail, tail))
    {
        int x_direction = tail.first - x_position;
        int y_direction = tail.second - y_position;

        if (((tail.first == 0) && (x_position == m_width - m_block_size)) ||
            ((tail.first == m_width - m_block_size) && (x_position == 0)))
        {
            x_direction = -x_direction;
        }

        if (((tail.second == 0) && (y_position == m_height - m_block_size)) ||
            ((tail.second == m_height - m_block_size) && (y_position == 0)))
        {
            y_direction = -y_direction;
        }        
        

        if (0 < x_direction && 0 == y_direction)
        {
            printf(ANSI_COLOR_YELLOW "%s" ANSI_COLOR_RESET, block_right_left[BLOCK_SLICES - index - 1]);
        }
        else if (0 > x_direction && 0 == y_direction)
        {
            printf(ANSI_COLOR_YELLOW "%s" ANSI_COLOR_RESET, block_left_right[BLOCK_SLICES - index - 1]); 
        }
        else if(0 == x_direction && 0 > y_direction)
        {
            printf(ANSI_COLOR_YELLOW "%s" ANSI_COLOR_RESET, block_up_bottom[BLOCK_SLICES - index - 1]);
        }
        else
        {
            printf(ANSI_COLOR_YELLOW "%s" ANSI_COLOR_RESET, block_bottom_up[BLOCK_SLICES - index - 1]);
        }
    }  
}

void DisplayController::PrintRows(std::vector<std::vector<std::string>> rows)
{
    
    for (size_t i = 0; i < rows.size(); ++i)
    {
        for (std::string col : rows[i])
        {
            auto iter = col.begin();
            if ('\n' == *iter)
            {
                col.erase(iter);
            }
            printf("%s     ", col.c_str());
        }
        printf("\n");
    }
}

int DisplayController::GetFrameSpeed()
{
    return m_framespeed;
}

void DisplayController::SetFrameSpeed(int speed)
{
    m_framespeed = speed;
}

void DisplayController::SetBlockSize(int block_size)
{
    m_block_size = block_size;
}

BLOCK2D DisplayController::GetFood() const
{
    return m_food;
}

int DisplayController::GetScore()
{
    return m_score;
}

void DisplayController::SetScore(int score)
{
    m_score = score;
}

bool DisplayController::IsPause()
{
    return m_is_pause;
}

void DisplayController::SetPause(bool status)
{
    m_is_pause = status;
}

void DisplayController::ChangeFramesPer()
{
    usleep(50000);
}

void DisplayController::GenerateFood()
{
    m_food.first = static_cast<int>(m_rand.GetRandomWidth());
    m_food.second = static_cast<int>(m_rand.GetRandomHeight());
}

char DisplayController::GetEvent()
{
    struct timeval timeout;
    fd_set readfds;
    char ch = 0;
    timeout.tv_sec = 0;
    timeout.tv_usec = 0;
    
    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);

    int result = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &timeout);
    if (result > 0) {
        if (FD_ISSET(STDIN_FILENO, &readfds)) {
            read(STDIN_FILENO, &ch, sizeof(char));
        }
    }
    return ch;
}
