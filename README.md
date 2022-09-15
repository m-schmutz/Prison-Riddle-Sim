# Prison-Riddle


## Background:
This repo contains two programs that allow you to simulate the 100 prisoners problem. I was inspired to make this after watching a [video](https://youtu.be/iSNsgj1OCLA) made by Veritasium. There is also a [Wikipedia page](https://en.wikipedia.org/wiki/100_prisoners_problem) that explains the problem in a little more depth and also provides explainations for the probability of success.


## Brief Explaination:
### Setup
Imagine there are 100 prisoners who are each assigned a number from 1 to 100. Each prisoner also has a slip of paper that has their number written on it. Then 100 boxes numbered 1-100 are placed in a room. The 100 slips of paper are then collected and placed randomly in the 100 boxes.


### Task
The task of the prisoners is to find their slip of paper in the room of boxes however their are strict rules they must follow:
- They must enter 1 at a time
- They can only look in 50 of the 100 boxes
- The room is reset after each prisoners turn, so there is no way for a prisoner to leave a hint for the prisoner that comes after them
- The prisoners only succeed if all 100 of them find their number
 
 
### Riddle
The riddle part of the problem is coming up with a strategy that will give the prisoners the highest chance of succeeding. I will leave the solution out of this explaination so that you have a chance to think about it for yourself. You can find the solution in the video and article.


## Running the Simulation Code:
Running the simulation is easy and only requires python3 or g++:
- Clone this repository: `git clone https://github.com/m-schmutz/Prison-Riddle-Sim.git`
- Change to this directory: `cd Prison-Riddle-Sim`
- For python implementation: 
    - `python3 run_sim.py` 
    - `./run_sim.py` by making file executible with `chmod +x run_sim.py`
- For C++ implementation
    - Compile source code with `make`
    - This creates executible named `faster_sim` which can be ran with `./faster_sim`


NOTE: The python implementation is slow for large counts of trials. I recommend using the C++ implementation for trial counts above 100,000
