#ifndef __SNAKE_GAME__
#define __SNAKE_GAME__
#include <unordered_map>
#include <random>
#include <map>
#include "score_database.hpp"
#include "display_snake.hpp"
#include "snake_body.hpp"

const int highest_score_rows = 5;
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
    void DisplayFrame();
    void Move();
    void SetNexMove(KEY);
    bool IsContinue(KEY);
    void ShowMenu();
    void GenerateFood();
    void PrintSnake();    
    void AdjustAcceleration();
    void GetName();
    void ShowScoreTable();
    void UpdateScore();
    void GameManu();
    void CaptureKeyboardEvent();

    int m_width;
    int m_height;
    int m_speed;
    int m_acceleration;
    int m_block_size;
    int m_x1;
    int m_y1;
    int m_x1_change;
    int m_y1_change;
    int m_foodx;
    int m_foody;
    bool m_game_over;
    bool m_game_close;
    bool m_is_accelerate;
    bool m_is_pause;
    bool m_is_score_updated;
    std::string m_player_name;

    SnakeDisplay m_dis;
    SnakeBody m_snake;
    ScoreDataBase m_db;
    std::random_device m_random;
    std::mt19937 m_gen;
    std::uniform_int_distribution<> m_distr_x;
    std::uniform_int_distribution<> m_distr_y;
    std::unordered_map<KEY, bool> m_manu_op;
    std::unordered_map<KEY, BLOCK2D> m_moves;
    std::unordered_map<X2D, std::unordered_map<Y2D, KEY>> m_invalid_move;
};


#endif /* __SNAKE_GAME__ */