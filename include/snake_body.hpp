#ifndef __SNAKE_BODY__
#define __SNAKE_BODY__
#include <utility>
#include <vector>

typedef std::pair<int, int> BLOCK2D;
typedef int WIDTH_POINT;
typedef int HEIGHT_POINT;
 
class SnakeBody
{
public:
    SnakeBody();
    ~SnakeBody();
    SnakeBody(const SnakeBody& other_) = delete;
    const SnakeBody& operator=(const SnakeBody& other_) = delete;
    void MoveSnake(BLOCK2D head);
    bool IsSnakeValid() const;
    void ClearSnake();
    const std::vector<BLOCK2D>& GetSnake() const;
    int GetLength() const;
    void GrowSnake(int amount);
private:
    std::vector<BLOCK2D> m_snake;
    int m_snake_length;
};

bool IsSame(const BLOCK2D a, const BLOCK2D b);

#endif /* __SNAKE_BODY__*/