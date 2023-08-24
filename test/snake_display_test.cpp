#include <iostream>
#include "display_snake.hpp"

int main()
{
    SnakeDisplay window(800, 600, 30);

    int x = 400;
    int y = 300;
    int y_change = 0;
    int x_change = 0;
    bool game_close = false;
    while (window.IsOpen())
    {
        
        while (game_close)
        {
            window.FillBackGround(sf::Color::Blue);
            window.Message("You Lost! Press Q-Quit or C-Play Again");
            window.UpdateFrame();
            sf::Event event;
            if (window.IsEvent(event))
            {
                if (IsKeyPressed(event))
                {
                    if (IsC())
                    {
                        game_close = false;
                    }
                }
            }         
        }
        sf::Event event;
        if (window.IsEvent(event))
        {

            if (IsQuit(event))
            {
                window.Close();
            }
            if (IsKeyPressed(event))
            {
                std::cout<<"KeyPressed!\n";
                if (IsLeft())
                {
                    std::cout<<"Left!\n";
                    x_change = -10;
                    y_change = 0;
                }
                else if (IsRight())
                {
                    std::cout<<"Right!\n";
                    x_change = 10;
                    y_change = 0;
                }
                else if (IsUp())
                {
                    std::cout<<"Up!\n";
                    y_change = -10;
                    x_change = 0;
                }
                else if (IsDown())
                {
                    std::cout<<"Down!\n";
                    y_change = 10;
                    x_change = 0;
                }
                else if (IsQ())
                {
                    std::cout<<"Q!\n";
                    game_close = true;
                    //window.Close();
                }
                else if (IsC())
                {
                    std::cout<<"C!\n";
                }                
            }
        }
        x += x_change;
        y += y_change;
        if (0 > x)
        {
            x = 800 + x_change;
        }
        else if (800 == x)
        {
            x = 0;
        }

        if (0 > y)
        {
            y = 600 + y_change;
        }
        else if (600 == y)
        {
            y = 0;
        }        
        window.FillBackGround(sf::Color::Blue);
        window.DrawRec(x, y, 20, sf::Color::Black);
        window.UpdateFrame();
        window.ChangeFrame(0);
    }


    return 0;
}