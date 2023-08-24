#ifndef __SNAKEBODYENGINE__
#define __SNAKEBODYENGINE__
#include <vector>

typedef std::pair<int, int> BLOCK2D;

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
    bool IsValidSnake();
    BLOCK2D GetNextMove();
    void SetNextMove(BLOCK2D next_move);
    BLOCK2D GetSnakeHead() const;
    BLOCK2D GetSnakeTail() const;
    void SetSnakeHead(BLOCK2D head);    
    const std::vector<BLOCK2D> &GetSnake();
    int GetSnakeLength();
    
private:
    std::vector<BLOCK2D> m_snake;
    int m_snake_length;
    int m_width;
    int m_height;
    BLOCK2D m_snake_head;
    BLOCK2D m_next_move;           
};
bool IsSame(const BLOCK2D a, const BLOCK2D b);
#endif /* __SNAKEBODYENGINE__ */