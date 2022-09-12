#!/bin/python3
from lib import *


if __name__ == '__main__':
    # get the number of trials to run
    trials = get_num_trials()

    # print out warning message
    if trials <= 100000:
        msg = ansi('WARNING: For trial counts over 100,000 recommend using C implementation')
        print(msg.yellow())

    # run the simulation
    run_simulation(trials)

