
#include "game_display.hpp"
#include "fromkeytostring.hpp"

Display::Display(int width, int height)
: m_clock(), m_font(), m_dis(sf::VideoMode(width, height), "Snake Game")
{   
    if (!m_font.loadFromFile("arial.ttf"))
    {
        throw std::runtime_error("Failed to open Font file arial.ttf");
    }
}

Display::~Display()
{
    m_font.~Font();
    m_dis.close();
}

void Display::UpdateFrame()
{
    m_dis.display();
}

void Display::ChangeFrame(int speed_val)
{
    sf::Time elapse = m_clock.getElapsedTime();
    sf::Int32 ticker = 100 / speed_val;
    while (elapse.asMilliseconds() < ticker)
    {
        elapse = m_clock.getElapsedTime();
    }

    m_clock.restart();
}

void Display::PrintMessage(std::string& str, sf::Color color, int text_size, int width, int height, sf::Text::Style style)
{
    sf::Text text;

    text.setFont(m_font);
    text.setFillColor(color);
    text.setString(str.c_str());
    text.setCharacterSize(text_size);
    text.setStyle(style);

    text.setPosition(width, height);

    m_dis.draw(text);    
}

void Display::PrintRows(std::vector<std::vector<std::string>> rows)
{
    sf::Text text;

    text.setFont(m_font);
    text.setFillColor(sf::Color::Green);
    int row_height = 20;
    int curr_height = 35;
    for (size_t i = 0; i < rows.size(); ++i)
    {
        int row_indent = 20;
        for (std::string col : rows[i])
        {
            auto iter = col.begin();
            if ('\n' == *iter)
            {
                col.erase(iter);
            }
            text.setString(col.c_str());
            text.setCharacterSize(20);
            text.setStyle(sf::Text::Bold | sf::Text::Italic);
            text.setPosition(row_indent, curr_height);
            m_dis.draw(text);
            row_indent += 190;
        }
        curr_height += row_height;
    }
}

void Display::FillBackGround(sf::Color color)
{
    m_dis.clear(color);
}

void Display::DrawRec(int x1, int y1, double width, int height, sf::Color color)
{
    sf::RectangleShape rectangle(sf::Vector2f(width, height));

    rectangle.setFillColor(color);
    rectangle.setPosition(sf::Vector2f(x1, y1));
    m_dis.draw(rectangle);
}

bool Display::GetEvent(sf::Event *event)
{
    return m_dis.pollEvent(*event);
}

void Display::Close()
{
    m_dis.close();
}

bool Display::GetInput(std::string& user_input)
{
    sf::Event event;
    if (m_dis.pollEvent(event))
    {   
        if (IsKeyPressed(event))
        {
            if (IsBackSpacePressed()){
                if(0 != user_input.size())
                {
                    auto iter = user_input.end();
                    --iter;
                    user_input.erase(iter);
                }
            }
            else if (IsEnterPressed())
            {
                return false;
            }
            else
            {
                user_input += FromKeytoString(event.key.code);
            }
        }
    }

    return true;
}

bool IsQuitEvent(const sf::Event& event)
{
    return event.type == sf::Event::Closed;
}

bool IsKeyPressed(const sf::Event& event)
{
    return event.type == sf::Event::KeyPressed;
}

bool IsBackSpacePressed()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace);
}

bool IsEnterPressed()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Enter);
}


bool IsLeftKeyPressed()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
}

bool IsRightKeyPressed()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
}

bool IsUpKeyPressed()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
}

bool IsDownKeyPressed()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
}

bool IsQKeyPressed()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Q);
}

bool IsCKeyPressed()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::C);
}

bool IsPKeyPressed()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::P);
}