#ifndef __DISPLAYENGINE__
#define __DISPLAYENGINE__

#include "snakecontroller.hpp"
#include "randomgenerator.hpp"

#define BLOCK_SLICES 8

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"


const char * const full_block = "\u2588";

const char * const block_left_right[] = {
    "\u258F", "\u258E", "\u258D", "\u258C",
    "\u258B", "\u258A", "\u2589", "\u2588"
};

const char * const block_right_left[] = {
    "\u2595", "\U0001FB87", "\U0001FB88", "\u2590",
    "\U0001FB89", "\U0001FB8A", "\U0001FB8B", "\u2588"
};

const char * const block_bottom_up[] = {
    "\u2581", "\u2582", "\u2583", "\u2584",
    "\u2585", "\u2586", "\u2587", "\u2588"
};

const char * const block_up_bottom[] = {
    "\u2594", "\U0001FB82", "\U0001FB83", "\u2580",
    "\U0001FB84", "\U0001FB85", "\U0001FB86", "\u2588"
};

const char left_key = 'a';
const char right_key = 'd';
const char up_key = 'w';
const char down_key = 's';
const char q_key = 'q';
const char c_key = 'c'; 
const char p_key = 'p'; 
const char backspace_key = 127; 
const char enter_key = 10; 
const int ch_width = 2;

class DisplayController
{
public:
    DisplayController(int width, int height, int speed, int block_size);
    ~DisplayController();
    DisplayController(const DisplayController& other) = delete;
    const DisplayController& operator=(const DisplayController& other) = delete;
    
    std::string GetUserInput(std::string msg);
    void ResetDisplay();
    char GetKeyPressed(); 
    void ShowManu(std::vector<std::vector<std::string>> &m_top_scores);
    void DisplayFrame(const std::vector<BLOCK2D> &snake, BLOCK2D direction, BLOCK2D shadow_tail);
    void ChangeFramesPer();
    void PrintRows(std::vector<std::vector<std::string>> rows);
    void PrintSnakeHead(BLOCK2D direction, int index);
    void PrintSnakeTail(BLOCK2D tail, int index, BLOCK2D shadow_tail);
    void GenerateFood();
    void AdjustAcceleration(int acceleration);
    bool GetInput(std::string& user_input);
    void SetBlockSize(int block_size);
    BLOCK2D GetFood() const;
    int GetScore();
    void SetScore(int score);
    bool IsPause();
    void SetPause(bool status);
    char GetEvent();
    void SetFrameSpeed(int speed);
    int GetFrameSpeed();
private:
    RandomPointGenerator m_rand;
    BLOCK2D m_food;
    double m_block_size;
    int m_width;
    int m_height;
    bool m_is_pause;
    int m_framespeed;
    int m_acceleration_value;
    int m_score; 
};

#endif /* __DISPLAYENGINE__ */