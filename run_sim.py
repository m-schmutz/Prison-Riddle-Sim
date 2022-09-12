#!/bin/python3
from lib import *


if __name__ == '__main__':
    # get the number of trials to run
    trials = get_num_trials()

    # run the simulation
    run_simulation(trials)
