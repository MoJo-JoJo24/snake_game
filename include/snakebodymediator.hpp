#ifndef __SNAKEBODYENGINE__
#define __SNAKEBODYENGINE__
#include "snake_body.hpp"

class SnakeBodyMediator
{
public:
    SnakeBodyMediator(int width, int height);
    ~SnakeBodyMediator();
    SnakeBodyMediator(const SnakeBodyMediator& other) = delete;
    const SnakeBodyMediator& operator=(const SnakeBodyMediator& other) = delete;

    void ResetPosition();
    void ClearSnake();
    void MoveSnake();
    void GrowSnake();
    bool IsMoveValid();
    BLOCK2D GetDirection();
    void SetDirection(BLOCK2D direction);
    BLOCK2D GetSnakeHead() const;
    void SetSnakeHead(BLOCK2D head);    
    const std::vector<BLOCK2D> &GetSnake();
    int GetSnakeLength();
    
private:
    SnakeBody m_snake;
    int m_width;
    int m_height;
    BLOCK2D m_snakehead;
    BLOCK2D m_snakedirection;           
};

#endif /* __SNAKEBODYENGINE__ */