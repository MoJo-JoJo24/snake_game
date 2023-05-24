INCLUDE = ./include

# Compiler flags
CPPFLAGS = -std=c++17 -pedantic-errors -Wall -Wextra -g
CPPRFLAGS = -std=c++17 -pedantic-errors -Wall -Wextra -DNDEBUG -O3
CC = g++

release : ./test/play_snake_game.cpp ./src/snakebodymediator.cpp ./src/scoremanager.cpp ./src/displaymediator.cpp ./src/score_database.cpp ./src/display_snake.cpp ./src/snake_body.cpp ./src/snake_game.cpp
	$(CC) $(CPPRFLAGS) -I $(INCLUDE) $^ -o play_snake_game.out -lsfml-graphics -lsfml-window -lsfml-system

snake_display_test.out : ./test/snake_display_test.cpp ./src/display_snake.cpp
	$(CC) $(CPPFLAGS) -I $(INCLUDE) $^ -o $@ -lsfml-graphics -lsfml-window -lsfml-system

play_snake_game.out : ./test/play_snake_game.cpp ./src/snakebodymediator.cpp ./src/scoremanager.cpp ./src/displaymediator.cpp ./src/score_database.cpp ./src/display_snake.cpp ./src/snake_body.cpp ./src/snake_game.cpp
	$(CC) $(CPPFLAGS) -I $(INCLUDE) $^ -o $@ -lsfml-graphics -lsfml-window -lsfml-system

score_database_test.out : ./test/score_database_test.cpp ./src/score_database.cpp
	$(CC) $(CPPFLAGS) -I $(INCLUDE) $^ -o $@ 

.PHONY: clean
clean : 
	rm -f *.hex *.out *.so *.o