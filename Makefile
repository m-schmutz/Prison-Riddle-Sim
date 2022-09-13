CC=g++
FLAGS=-std=c++11 -Wall
EXE=faster_sim

all: simulation.cpp
	$(CC) $(FLAGS) simulation.cpp -o $(EXE)

clean: 
	rm $(EXE)