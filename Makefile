CC=gcc
FLAGS=-std=c17 -Wall 
EXE=sim

all: c_src/boxes.c c_src/simulation.c c_src/trial.c
	$(CC) $(FLAGS) c_src/boxes.c c_src/simulation.c c_src/trial.c -o $(EXE)

clean: 
	rm $(EXE)