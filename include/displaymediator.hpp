#ifndef __DISPLAYENGINE__
#define __DISPLAYENGINE__
#include <random>
#include <unordered_map>
#include "snake_body.hpp"
#include "display_snake.hpp"

class RandomPointGenerator
{
public:
    RandomPointGenerator(int width, int height);
    ~RandomPointGenerator();
    int GetRandomWidth();
    int GetRandomHeight();
private:
    std::random_device m_random_seed;
    std::mt19937 m_random_generator;
    std::uniform_int_distribution<> m_random_width_range;
    std::uniform_int_distribution<> m_random_height_range;
};

class DisplayMediator
{
public:
    DisplayMediator(int width, int height, int speed, int block_size);
    ~DisplayMediator();
    DisplayMediator(const DisplayMediator& other) = delete;
    const DisplayMediator& operator=(const DisplayMediator& other) = delete;
    
    std::string GetUserInput(std::string msg);
    bool ResetDisplay();
    KEY GetKeyPressed();
    void ShowManu();
    KEY CaptureKeyboardEvent(bool &flag_game_close, bool &flag_game_over);
    void DisplayFrame(const std::vector<BLOCK2D> &snake);
    void ChangeFrame();


    void PrintSnake(const std::vector<BLOCK2D> &snake);
    void GenerateFood();
    void AdjustAcceleration();
    void SetScores(std::vector<std::vector<std::string>> finalscores);
    void SetBlockSize(int block_size);
    BLOCK2D GetFood() const;
    std::string &GetName();
    int GetScore();
    void SetScore(int score);
    bool IsPause();
    void SetPause(bool status);

private:
    SnakeDisplay m_display;
    RandomPointGenerator m_rand;
    std::string m_player_name;
    BLOCK2D m_food;
    int m_block_size;
    bool m_is_accelerate;
    bool m_is_pause;
    int m_framespeed;
    int m_acceleration_value;
    int m_score;
    std::vector<std::vector<std::string>> m_finalscores;            
};

#endif /* __DISPLAYENGINE__ */