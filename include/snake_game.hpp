#ifndef __SNAKE_GAME__
#define __SNAKE_GAME__
#include <unordered_map>
#include <unordered_set>
#include "scoremanager.hpp"
#include "displaycontroller.hpp"
#include "snakecontroller.hpp"

class SnakeGame 
{
public:
    SnakeGame(int width = 0, int height = 0, int speed = 0, int block_size = 0);
    ~SnakeGame();
    SnakeGame(const SnakeGame& other_) = delete;
    const SnakeGame& operator=(const SnakeGame& other_) = delete;
    void RunGame();
    
private:
    void SetGame();
    bool IsEat() const;
    void RegisterNexMove(char);
    bool IsContinue(char);
    void GetManuOption();
    void DisplayFrame(BLOCK2D &shadow_tail);
    void UpdateTopScores();

    int m_acceleration;
    bool m_game_over;
    bool m_game_close;
    std::string m_player_name;
    ScoreManager m_score_db;
    DisplayController m_display_controller;
    SnakeBodyMediator m_snake_controller;
    std::unordered_map<char, BLOCK2D> m_moves;
    std::unordered_map<int, std::unordered_map<int, char>> m_invalid_move;
    std::unordered_set<std::string> m_speed_options;
};


#endif /* __SNAKE_GAME__ */