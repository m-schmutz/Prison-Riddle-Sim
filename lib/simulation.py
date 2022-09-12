from random import SystemRandom
from multiprocessing import Pool, Pipe, cpu_count
from multiprocessing.connection import wait
from progressbar import ProgressBar
from time import perf_counter

__all__ = ['get_num_trials', 'run_simulation']


# return values for a prisoner either finding their number of not
SUCCESS = True
FAIL = False

# seconds in a minute
SECONDS_IN_MIN = 60

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
            return trials
        except:
            # berate them for entering something that isn't a number
            print('enter a number you moron')
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
    # extract number of trials and pipe
    trials, pipe = args

    # initialize successes to 0
    successes = 0

    # go through each trial for this process
    for _ in range(trials):

        # if trial returns true, it was a success
        if trial():
            successes += 1

        # send progress through pipe
        pipe.send(1)

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
    print(f'The prisoners succeeded {total_successes} times out of {trials} trials with a success rate of {success_rate}%')
    print(f'Total Elapsed Time: {mins} minutes {remaining_secs:.3f} seconds')
    print('**********************************************************************************************************')
##########################################################################################

##########################################################################################
def run_simulation(trials:int) -> None:
    # initialize the progress bar
    pb = ProgressBar(total=trials, title=f'Simulation in Progress...', titleoncomplete='Simulation Complete', left='', right='', fill_char='█', empty_char='░')

    # get the number of processes to use based on the cpu count
    num_processes = cpu_count()

    # get the max number of trials per process
    trials_per_process = trials // num_processes

    # get the remainder left over from previous step
    remainder = trials % num_processes

    # get the list of trials per process
    distro = [trials_per_process + 1] * remainder + [trials_per_process] * (num_processes - remainder)

    # initialize the lists that will contain the pipe endpoints
    send_ends = list()
    recv_ends = list()

    # populate the lists of pipes
    for _ in range(num_processes):
        r, s = Pipe(duplex=False)
        recv_ends.append(r)
        send_ends.append(s)


    # initalize progress
    progress = 0

    # start perf counter
    t1 = perf_counter()
    
    # start processor pool and execute the simulation
    with Pool(processes=num_processes) as pool:\
        # start each of the processes
        results = pool.map_async(process_driver, zip(distro, send_ends)) 

        # while simulation is not done, update the progress bar
        while True:
            progress += sum([p.recv() for p in wait(recv_ends, timeout=.1)])

            # update the progress bar
            pb.update(progress)

            # if progress is equal to the number of trials, simulation is done
            if progress == trials:
                break
    
    # end perf counter
    t2 = perf_counter()

    # get the total number of successes
    total_successes = sum(results.get())

    # print the results of the simulation
    print_results(trials, total_successes, t1, t2)
##########################################################################################









