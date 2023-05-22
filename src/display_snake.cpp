#include <math.h>
#include <iostream>
#include "display_snake.hpp"

SnakeDisplay::SnakeDisplay(int width, int height, int speed)
: m_clock(), m_font(), m_dis(sf::VideoMode(width, height), "Snake Game"),
  m_frame_speed(speed), m_width(width), m_height(height)
{
    left = sf::Keyboard::Key::Left;
    right = sf::Keyboard::Key::Right;
    up = sf::Keyboard::Key::Up;
    down = sf::Keyboard::Key::Down;
    q = sf::Keyboard::Key::Q;
    c = sf::Keyboard::Key::C;
    
    if (!m_font.loadFromFile("arial.ttf"))
    {
        throw std::runtime_error("Failed to open Font file");
    }
}

SnakeDisplay::~SnakeDisplay()
{
    m_dis.close();
}

void SnakeDisplay::UpdateFrame()
{
    m_dis.display();
}

void SnakeDisplay::ChangeFrame(int change_speed_val)
{
    sf::Time elapse = m_clock.getElapsedTime();
    m_frame_speed += change_speed_val;
    sf::Int32 ticker = 1000 / m_frame_speed;
    while (elapse.asMilliseconds() < ticker)
    {
        elapse = m_clock.getElapsedTime();
    }

    m_clock.restart();
}

bool SnakeDisplay::IsEvent(sf::Event& event)
{
    return m_dis.pollEvent(event);
}

void SnakeDisplay::FillBackGround(sf::Color color)
{
    m_dis.clear(color);
}

void SnakeDisplay::DrawRec(int x1, int y1, int block_size, sf::Color color)
{
    sf::RectangleShape rectangle(sf::Vector2f(block_size, block_size));

    rectangle.setFillColor(color);
    rectangle.setPosition(sf::Vector2f(x1, y1));
    m_dis.draw(rectangle);
}

void SnakeDisplay::Close()
{
    m_dis.close();
}

bool SnakeDisplay::IsOpen()
{
    return m_dis.isOpen();
}

void SnakeDisplay::Message(std::string str)
{
    sf::Text text;

    text.setFont(m_font);
    text.setFillColor(sf::Color::Red);
    text.setString(str.c_str());
    text.setCharacterSize(24);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    text.setPosition(m_width / 6, m_height / 3);

    m_dis.draw(text);
}

void SnakeDisplay::PrintRows(std::vector<std::string> rows)
{
    sf::Text text;

    text.setFont(m_font);
    text.setFillColor(sf::Color::Green);
    int row_height = 20;
    int curr_height = 35;
    int row_indent = 20;     
    for (size_t i = 0; i < rows.size(); ++i)
    {
        text.setString(rows[i].c_str());
        std::cout<<rows[i].c_str()<<std::endl;
        text.setCharacterSize(20);
        text.setStyle(sf::Text::Bold | sf::Text::Italic);
        text.setPosition(row_indent, curr_height);

        m_dis.draw(text);
        curr_height += row_height;
    }
}


void SnakeDisplay::YourScore(int score)
{
    sf::Text text;
    text.setFont(m_font);
    text.setFillColor(sf::Color::Yellow);
    std::string str("Your Score: " + std::to_string(score) + " ");
    text.setString(str.c_str());
    text.setCharacterSize(20);
    text.setStyle(sf::Text::Underlined);    
    text.setPosition(0, 0);
    
    m_dis.draw(text);
}

void SnakeDisplay::SetFrameSpeed(int speed)
{
    m_frame_speed = speed;
}

bool IsQuit(const sf::Event& event)
{
    return event.type == sf::Event::Closed;
}

bool IsKeyPressed(const sf::Event& event)
{
    return event.type == sf::Event::KeyPressed;
}

bool IsBackSpace()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace);
}

bool IsEnter()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Enter);
}


bool IsLeft()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
}

bool IsRight()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
}

bool IsUp()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
}

bool IsDown()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
}

bool IsQ()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Q);
}

bool IsC()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::C);
}

bool IsP()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::P);
}

std::string FromKtoS(const sf::Keyboard::Key& k)
{
    std::string ret;
    switch(k)
    {

    case sf::Keyboard::A :
        ret="A";
        break;

    case sf::Keyboard::B :
        ret="B";
        break;

    case sf::Keyboard::C :
        ret="C";
        break;

    case sf::Keyboard::D :
        ret="D";
        break;

    case sf::Keyboard::E :
        ret="E";
        break;

    case sf::Keyboard::F :
        ret="F";
        break;

    case sf::Keyboard::G :
        ret="G";
        break;

    case sf::Keyboard::H :
        ret="H";
        break;

    case sf::Keyboard::I :
        ret="I";
        break;

    case sf::Keyboard::J :
        ret="J";
        break;

    case sf::Keyboard::K :
        ret="K";
        break;

    case sf::Keyboard::L :
        ret="L";
        break;

    case sf::Keyboard::M :
        ret="M";
        break;

    case sf::Keyboard::N :
        ret="N";
        break;

    case sf::Keyboard::O :
        ret="O";
        break;

    case sf::Keyboard::P :
        ret="P";
        break;

    case sf::Keyboard::Q :
        ret="Q";
        break;

    case sf::Keyboard::R :
        ret="R";
        break;

    case sf::Keyboard::S :
        ret="S";
        break;

    case sf::Keyboard::T :
        ret="T";
        break;

    case sf::Keyboard::U :
        ret="U";
        break;

    case sf::Keyboard::V :
        ret="V";
        break;

    case sf::Keyboard::W :
        ret="W";
        break;

    case sf::Keyboard::X :
        ret="X";
        break;

    case sf::Keyboard::Y :
        ret="Y";
        break;

    case sf::Keyboard::Z :
        ret="Z";
        break;

    case sf::Keyboard::Num0 :
        ret="0";
        break;

    case sf::Keyboard::Num1 :
        ret="1";
        break;

    case sf::Keyboard::Num2 :
        ret="2";
        break;

    case sf::Keyboard::Num3 :
        ret="3";
        break;

    case sf::Keyboard::Num4 :
        ret="4";
        break;

    case sf::Keyboard::Num5 :
        ret="5";
        break;

    case sf::Keyboard::Num6 :
        ret="6";
        break;

    case sf::Keyboard::Num7 :
        ret="7";
        break;

    case sf::Keyboard::Num8 :
        ret="8";
        break;

    case sf::Keyboard::Num9 :
        ret="9";
        break;

    case sf::Keyboard::Escape :
        ret="";
        break;

    case sf::Keyboard::LControl :
        ret="";
        break;

    case sf::Keyboard::LShift :
        ret="";
        break;

    case sf::Keyboard::LAlt :
        ret="";
        break;

    case sf::Keyboard::LSystem :
        ret="";
        break;

    case sf::Keyboard::RControl :
        ret="";
        break;

    case sf::Keyboard::RShift :
        ret="";
        break;

    case sf::Keyboard::RAlt :
        ret="";
        break;

    case sf::Keyboard::RSystem :
        ret="";
        break;

    case sf::Keyboard::Menu :
        ret="Menu";
        break;

    case sf::Keyboard::LBracket :
        ret="(";
        break;

    case sf::Keyboard::RBracket :
        ret=")";
        break;

    case sf::Keyboard::SemiColon :
        ret=";";
        break;

    case sf::Keyboard::Comma :
        ret=",";
        break;

    case sf::Keyboard::Period :
        ret=".";
        break;

    case sf::Keyboard::Quote :
        ret="""";
        break;

    case sf::Keyboard::Slash :
        ret="/";
        break;

    case sf::Keyboard::BackSlash :
        ret="\\";
        break;

    case sf::Keyboard::Tilde :
        ret="Tilde";
        break;

    case sf::Keyboard::Equal :
        ret="=";
        break;

    case sf::Keyboard::Dash :
        ret="-";
        break;

    case sf::Keyboard::Space :
        ret=" ";
        break;

    // case sf::Keyboard::Return :
    //     ret="Return";
    //     break;

    // case sf::Keyboard::BackSpace :
    //     ret="BackSpace";
    //     break;

    case sf::Keyboard::Tab :
        ret="    ";
        break;

    case sf::Keyboard::PageUp :
        ret="PageUp";
        break;

    case sf::Keyboard::PageDown :
        ret="PageDown";
        break;

    case sf::Keyboard::End :
        ret="End";
        break;

    case sf::Keyboard::Home :
        ret="Home";
        break;

    case sf::Keyboard::Insert :
        ret="Insert";
        break;

    case sf::Keyboard::Delete :
        ret="Delete";
        break;

    case sf::Keyboard::Add :
        ret="+";
        break;

    case sf::Keyboard::Subtract :
        ret="-";
        break;

    case sf::Keyboard::Multiply :
        ret="*";
        break;

    case sf::Keyboard::Divide :
        ret="/";
        break;

    case sf::Keyboard::Left :
        ret="Left";
        break;

    case sf::Keyboard::Right :
        ret="Right";
        break;

    case sf::Keyboard::Up :
        ret="Up";
        break;

    case sf::Keyboard::Down :
        ret="Down";
        break;

    case sf::Keyboard::Numpad0 :
        ret="0";
        break;

    case sf::Keyboard::Numpad1 :
        ret="1";    
        break;

    case sf::Keyboard::Numpad2 :
        ret="2";
        break;

    case sf::Keyboard::Numpad3 :
        ret="3";
        break;

    case sf::Keyboard::Numpad4 :
        ret="4";
        break;    

    case sf::Keyboard::Numpad5 :
        ret="5";
        break;

    case sf::Keyboard::Numpad6 :
        ret="6";
        break;

    case sf::Keyboard::Numpad7 :
        ret="7";
        break;
    case sf::Keyboard::Numpad8 :
        ret="8";
        break;

    case sf::Keyboard::Numpad9 :
        ret="9";
        break;

    case sf::Keyboard::F1 :
        ret="F1";
        break;

    case sf::Keyboard::F2 :
        ret="F2";
        break;

    case sf::Keyboard::F3 :
        ret="F3";
        break;

    case sf::Keyboard::F4 :
        ret="F4";
        break;

    case sf::Keyboard::F5 :
        ret="F5";
        break;

    case sf::Keyboard::F6 :
        ret="F6";
        break;

    case sf::Keyboard::F7 :
        ret="F7";
        break;

    case sf::Keyboard::F8 :
        ret="F8";
        break;

    case sf::Keyboard::F9 :
        ret="F9";
        break;

    case sf::Keyboard::F10 :
        ret="F10";
        break;

    case sf::Keyboard::F11 :
        ret="F11";
        break;

    case sf::Keyboard::F12 :
        ret="F12";
        break;

    case sf::Keyboard::F13 :
        ret="F13";
        break;

    case sf::Keyboard::F14 :
        ret="F14";
        break;

    case sf::Keyboard::F15 :
        ret="F15";
        break;

    case sf::Keyboard::Pause :
        ret="Pause";
        break;

    case sf::Keyboard::KeyCount :
        ret="KeyCount";
        break;

        default:
            ret="";
            break;
    }
    return ret;
}
