#!/bin/python3
from py_src.simulation import get_num_trials, run_simulation

if __name__ == '__main__':
    # get the number of trials to run
    trials = get_num_trials()

    # print out warning message
    if trials >= 300000:
        print('\033[33mWARNING: Python implementation not recommended for trial counts over 300,000\033[0m')

    # run the simulation
    run_simulation(trials)
