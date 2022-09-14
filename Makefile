CC=g++
FLAGS=-std=c++11 -Wall -pthread
EXE=faster_sim

all: lib/simulation.cpp
	$(CC) $(FLAGS) lib/simulation.cpp -o $(EXE)

clean: 
	rm $(EXE)