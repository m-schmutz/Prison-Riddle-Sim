from random import SystemRandom
from multiprocessing import Pool, Array, cpu_count
from time import perf_counter

__all__ = ['get_num_trials', 'run_simulation']


# return values for a prisoner either finding their number of not
SUCCESS = True
FAIL = False

# seconds in a minute
SECONDS_IN_MIN = 60

# get the number of processes based on cpu_count
NUM_PROCS = cpu_count()

# initalize an array for progress tracking
progress_arr = Array('i', NUM_PROCS, lock=False)

##########################################################################################
# template for the boxes
# list indices represent the 100 boxes
# list elements represent the slips of paper
init_boxes = [i for i in range(1, 101)]
##########################################################################################

##########################################################################################
# get the number of trials that the user wants to simulate
def get_num_trials() -> int:
    while(True):
        # prompt the user
        trials = input("How many trials would you like to simulate?: ")
        try:
            # check that string entered is a number
            trials = int(trials)

            assert(trials > 0)

            return trials
        
        except ValueError:
            # berate user for entering something that isn't a number
            print('enter a number you moron')
        
        except AssertionError:
            # berate user for entering a negative number
            print('can\'t simulate negative number of trials you idiot')
##########################################################################################

##########################################################################################
# this function simulates a single prisoner trying to find their number in the 100 boxes
def find_number(num:int, boxes:list) -> bool:
    # the user starts by looking in the box with their number
    box_index = num - 1

    # each prisoner gets to look in 50 boxes max
    for _ in range(50):

        # check if number is the prisoners number
        if boxes[box_index] == num:
        
            # if number is found, return success
            return SUCCESS
            
        else:
            # else if number is not found, set next box to be opened as the 
            # box matching the number in this box
            box_index = boxes[box_index] - 1
    
    # return fail if prisoner fails to find number in 50 tries
    return FAIL
##########################################################################################

##########################################################################################
# this function simulates all 100 prisoners attempting to find their number in the 100 boxes
def trial() -> bool:
    # copy init_boxes list and shuffle it
    round_boxes = init_boxes
    SystemRandom().shuffle(round_boxes)

    # loop through each prisoners number and attempt to find their number
    for i in range(1,101):
        # if find_number() returns a FAIL, then a prisoner failed to find 
        # their number and therefore the entire trial fails
        if not find_number(i, round_boxes):
            return FAIL

    # if find_number() never returns a FAIL, then trial trial succeeds
    return SUCCESS 
##########################################################################################

##########################################################################################
def process_driver(args) -> int:
    trials, ind = args

    # initialize successes to 0
    successes = 0

    # go through each trial for this process
    for i in range(trials):

        # if trial returns true, it was a success
        if trial():
            successes += 1
        
        progress_arr[ind] = i + 1
        

    # return the number of successes for this process
    return successes
##########################################################################################

##########################################################################################
# this function returns the success rate of the simulation
def print_results(trials, total_successes, t1, t2) -> None:

    # get the elapsed time
    elapsed_time = t2 - t1

    # find the amount of minutes that have passed
    mins = int(elapsed_time // SECONDS_IN_MIN)

    # find the remaining seconds
    remaining_secs = elapsed_time - (mins * SECONDS_IN_MIN)

    # calculate the success rate of the trials
    success_rate = (total_successes/trials) * 100
    print('**********************************************************************************************************')
    print(f'The prisoners succeeded {total_successes} times out of {trials} trials with a success rate of {success_rate:.3f}%')
    print(f'Total Elapsed Time: {mins} minutes {remaining_secs:.3f} seconds')
    print('**********************************************************************************************************')
##########################################################################################

##########################################################################################
def run_simulation(trials:int) -> None:
    # get the max number of trials per process
    trials_per_process = trials // NUM_PROCS

    # get the remainder left over from previous step
    remainder = trials % NUM_PROCS

    # get the list of trials per process
    distro = [trials_per_process + 1] * remainder + [trials_per_process] * (NUM_PROCS - remainder)

    # set cursor as invisible
    print('\033[?25l')
    
    # start perf counter
    t1 = perf_counter()
    
    # start processor pool and execute the simulation
    with Pool(processes=NUM_PROCS) as pool:
        # start each of the processes
        results = pool.map_async(process_driver, zip(distro, range(NUM_PROCS)))

        # while simulation is not done, update the progress bar
        while True:
            # get the current state of the sim
            done = sum(progress_arr)

            # print out progress with percentage
            print(f'\033[1F{done} / {trials} | {done/trials*100:.2f}%')

            # check if sim is done
            if sum(progress_arr) == trials:
                print(f'\033[1F{sum(progress_arr)} / {trials} | {sum(progress_arr)/trials*100:.2f}%')
                break
    
    # end perf counter
    t2 = perf_counter()
    
    # set cursor as visible again and clear ansi
    print('\033[?25h\033[0m')
    
    # get the total number of successes
    total_successes = sum(results.get())

    # print the results of the simulation
    print_results(trials, total_successes, t1, t2)
##########################################################################################

