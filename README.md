# snake_game
snake game in c++

## How to Run
1. Install the graphic library SFML/Graphics.hpp:
```sh
sudo apt-get install libsfml-dev
```
2. make sure to download from this repository the image file arial.ttf and save in the same directory as the executable
3. source files for compilaiton include:
play_snake_game.cpp, snakebodymediator.cpp, scoremanager.cpp, displaymediator.cpp, score_database.cpp, display_snake.cpp, snake_body.cpp, and snake_game.cpp
5. Compile geme form the command line:

  option 1 using makefile:
```sh
make release
```
  option 2:
```sh
g++ -std=c++17 -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I ./include test/play_snake_game.cpp src/snakebodymediator.cpp src/scoremanager.cpp src/displaymediator.cpp src/score_database.cpp src/display_snake.cpp src/snake_body.cpp src/snake_game.cpp -o play_snake_game.out -lsfml-graphics -lsfml-window -lsfml-system
```
5. Run the executable 'play_snake_game.out' from the command line
```sh
./play_snake_game.out
```
## How to Play
1.  Download or clone the repository to your local machine
2.  follow steps on how to run above
6.  Follow the in-game manu promps and use the arrow keys to move the snake

## Scores
The game uses a text file to record and display the history of scores
