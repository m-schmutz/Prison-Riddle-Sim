#!/bin/python3
import multiprocessing
from random import SystemRandom
from multiprocessing import Process, Value
from psutil import cpu_count
import time

SUCCESS = True
FAIL = False

##########################################################################################
# template for the boxes
# list indices represent the 100 boxes
# list elements represent the slips of paper
init_boxes = list()
for i in range(1,101):
    init_boxes.append(i)
##########################################################################################

##########################################################################################
# get the number of trials that the user wants to simulate
def get_num_trials():
    while(True):
        # prompt the user
        trials = input("How many trials would you like to simulate?: ")
        try:
            # check that string entered is a number
            trials = int(trials)
            return trials
        except:
            # berate them for entering something that isn't a number
            print('enter a number you moron')
##########################################################################################

##########################################################################################
# this function simulates a single prisoner trying to find their number in the 100 boxes
def find_number(num, boxes:list):
    # the user starts by looking in the box with their number
    box_index = num - 1
    # each prisoner gets to look in 50 boxes max
    for _ in range(50):
        # get number in box
        found_number = boxes[box_index]
        # check if number is the prisoners number
        if found_number == num:
            # if number is found, return success
            return SUCCESS
            
        else:
            # else if number is not found, set next box to be opened as the 
            # box matching the number in this box
            box_index = boxes[box_index] - 1
    
    return FAIL
##########################################################################################

##########################################################################################
# this function simulates all 100 prisoners attempting to find their number in the 100 boxes
def trial():
    # copy init_boxes list and shuffle it
    round_boxes = init_boxes
    SystemRandom().shuffle(round_boxes)
    # loop through each prisoners number and attemp to find their number
    for i in range(1,101):
        # call find number with the prisoners number and the boxes for this round
        result = find_number(i, round_boxes)

        # if find_number() returns a FAIL, then entire trial fails
        if not result:
            return FAIL

    # if find_number() does not return a FAIL, then trial trial succeeds
    return SUCCESS 
##########################################################################################

##########################################################################################
def process_driver(thread_trials, total_successes):
    successes = 0
    # simulate the number of trials given by the user
    for _ in range(thread_trials):

        # run a trial and get the result
        result = trial()
        
        # if the trial succeeds, increment successes
        if result:
            successes += 1
    total_successes.value += successes
    return
    
##########################################################################################



##########################################################################################
# this function 
def simulation(trials):

    # print the number of trials that are being simulating
    print(f'Simulating {trials} trials')
    
    # get the number of CPU cores 
    num_cores = cpu_count(logical=False)

    # using integer division, get the base amount that each process will do 
    process_trials = trials // num_cores

    # get the remainder, if any
    remaining = trials % num_cores  

    total_successes = Value('i', 0)

    procs = []
    for core in range(num_cores):
        if remaining:
            procs.append(Process(target=process_driver, args=(process_trials + 1, total_successes)))
            procs[core].start()

    for p in procs:
        p.join()

    return int(total_successes.value)
    
    
##########################################################################################

##########################################################################################
# this function returns the success rate of the simulation
def print_results(trials, total_successes,t1, t2):
    success_rate = (total_successes/trials) * 100
    print('**********************************************************************************************************')
    print(f'The prisoners succeeded {total_successes} times in {trials} trials with a success rate of {success_rate}%')
    print(f'simulation completed in {t2 - t1} seconds')
    print('**********************************************************************************************************')
##########################################################################################

if __name__ == '__main__':
    trials = get_num_trials()

    t1 = time.perf_counter()
    total_successes = simulation(trials)
    t2 = time.perf_counter()
    print_results(trials, total_successes, t1, t2)
