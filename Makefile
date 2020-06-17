CPPFLAGS = -std=c++11 -Wall -Werror -pedantic -ggdb -pthread

GameOfLife_Animation : GameOfLife_Animation.cpp
	g++ $(CPPFLAGS) $< -o $@
	@echo "Made GameOfLife_Animation"

GameOfLife_Parallel : GameOfLife_Parallel.cpp
	g++ $(CPPFLAGS) $< -o $@
	@echo "Made GameOfLife_Parallel"

GameOfLife_Sequential : GameOfLife_Sequential.cpp
	g++ $(CPPFLAGS) $< -o $@
	@echo "Made GameOfLife_Sequential"

all : GameOfLife_Animation.cpp GameOfLife_Parallel.cpp GameOfLife_Sequential.cpp
	g++ $(CPPFLAGS) GameOfLife_Animation.cpp -o GameOfLife_Animation
	@echo "Made GameOfLife_Animation"
	g++ $(CPPFLAGS) GameOfLife_Parallel.cpp -o GameOfLife_Parallel
	@echo "Made GameOfLife_Parallel"
	g++ $(CPPFLAGS) GameOfLife_Sequential.cpp -o GameOfLife_Sequential
	@echo "Made GameOfLife_Sequential"