#ifndef __SNAKE_GAME__
#define __SNAKE_GAME__
#include <unordered_map>
#include "scoremanager.hpp"
#include "displaymediator.hpp"
#include "snakebodymediator.hpp"

class SnakeGame 
{
public:
    SnakeGame(int width = 0, int height = 0, int speed = 0, int block_size = 0);
    ~SnakeGame();
    SnakeGame(const SnakeGame& other_) = delete;
    const SnakeGame& operator=(const SnakeGame& other_) = delete;
    void RunGame();
    
private:
    void ResetGame();
    bool IsEat() const;
    void SetNexMove(KEY);
    bool IsContinue(KEY);
    void GameManu();

    int m_acceleration;
    bool m_game_over;
    bool m_game_close;
    bool m_is_score_updated;
    DisplayMediator m_display_mediator;
    ScoreManager m_score_db;
    SnakeBodyMediator m_snake_mediator;
    std::unordered_map<KEY, bool> m_manu_options;
    std::unordered_map<KEY, BLOCK2D> m_moves;
    std::unordered_map<WIDTH_POINT, std::unordered_map<HEIGHT_POINT, KEY>> m_invalid_move;
};


#endif /* __SNAKE_GAME__ */