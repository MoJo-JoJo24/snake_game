#ifndef __SFMLDISPLAY__
#define __SFMLDISPLAY__
#include <SFML/Graphics.hpp>

bool IsKeyPressed(const sf::Event&);
bool IsQuit(const sf::Event&);
bool IsBackSpace();
bool IsEnter();
bool IsLeft();
bool IsRight();
bool IsUp();
bool IsDown();
bool IsQ();
bool IsC();
bool IsP();
std::string FromKtoS(const sf::Keyboard::Key& k);

typedef sf::Event::EventType EVENT_TYPE;
typedef enum sf::Keyboard::Key KEY;

const KEY left_key = sf::Keyboard::Key::Left;
const KEY right_key = sf::Keyboard::Key::Right;
const KEY up_key = sf::Keyboard::Key::Up;
const KEY down_key = sf::Keyboard::Key::Down;
const KEY q_key = sf::Keyboard::Key::Q;
const KEY c_key = sf::Keyboard::Key::C; 

class SnakeDisplay
{
public:
    SnakeDisplay(int width = 0, int height = 0);
    ~SnakeDisplay();
    SnakeDisplay(const SnakeDisplay& other_) = delete;
    const SnakeDisplay& operator=(const SnakeDisplay& other_) = delete;


    void UpdateFrame();
    void ChangeFrame(int speed_val);
    bool IsEvent(sf::Event& event);
    void FillBackGround(sf::Color color);
    void DrawRec(int x1, int y1, int block_size, sf::Color color);
    void PrintRows(std::vector<std::vector<std::string>>);
    void Close();
    void PrintMessage(std::string&, sf::Color, int text_size, int width, int height, sf::Text::Style = sf::Text::Bold);
    
private:
    sf::Clock m_clock;
    sf::Font m_font;
    sf::RenderWindow m_dis;
};


#endif /* __SFMLDISPLAY__ */