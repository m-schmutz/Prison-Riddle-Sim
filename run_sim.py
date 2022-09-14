#!/bin/python3
from lib.simulation import *

if __name__ == '__main__':
    # get the number of trials to run
    trials = get_num_trials()

    # print out warning message
    if trials >= 100000:
        print('\033[33mWARNING: Recommend using C++ implementation for trials counts over 100,000\033[0m')

    # run the simulation
    run_simulation(trials)
