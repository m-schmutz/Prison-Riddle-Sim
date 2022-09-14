#include <iostream>
#include <array>
#include <algorithm>
#include <random>       
#include <chrono>    
#include <vector>   
#include <thread>
#include <unistd.h>
#include <string>
#include <iomanip>
#include <string>
#include <regex>

// i know this is bad practice
// but its a small program, deal with it
using std::array;
using std::cout;
using std::cin;
using std::shuffle;
using std::default_random_engine;
using std::vector;
using std::thread;
using std::accumulate;
using std::random_device;
using std::mt19937;
using std::fixed;
using std::setprecision;
using std::string;
using std::stoi;
using std::regex_match;
using std::flush;
using std::regex;

// number of boxes is constant
const int NUM_BOXES = 100;

// each prisoner has a max of 50 attempts to find their number
const int MAX_ATTEMPTS = 50;


// struct to store the results of a simulation
struct Results
{
    int trials;
    int total_successes;
    float success_rate;
    float sim_secs;
    int sim_mins;
};


//function to initalize the boxes array
array<int, NUM_BOXES> init_boxes()
{
    // initalize array of int that is 100 elements
    array<int, NUM_BOXES> boxes;

    // loop through each element and set it to its index + 1
    for (int i = 0; i < NUM_BOXES; ++i)
    {
        boxes[i] = i + 1;
    }
    
    // return the created array
    return boxes;
}


// function to simulate prisoner attempting to find their number
bool find_number(const array<int, NUM_BOXES>& trial_boxes, const int num)
{
    // Since our indices start at 0 (as they should) start by looking in the prisoner's number box
    int box_index = num - 1;

    // The prisoner has 50 attempts to open a box and find their number
    for (int i = 0; i < MAX_ATTEMPTS; ++i)
    {
        // if the prisoner finds their number, return true
        if (trial_boxes[box_index] == num)
        {
            return true;
        }

        // otherwise set next box to look in as the box at the found number's index
        box_index = trial_boxes[box_index] - 1;
    }

    // if we are out of the loop, prisoner failed to find their number
    return false;
}


// function to simulate every prisoner (1-100) attempting to find their number
bool trial(const array<int, NUM_BOXES>& trial_boxes)
{
    // for each prisoner, attempt to find number
    for (int num = 1; num <= NUM_BOXES; ++num)
    {
        // if find_number returns false, prisoner failed to find their number
        // therefore the entire trial fails
        if (!find_number(trial_boxes, num))
        {
            return false;
        }
    }

    // if each prisoner succeeds, trial succeeds
    return true;
}


// function that is ran by each thread 
// simulates 'trials' trials and then stores successes value into passed pointer
void thread_driver(const int trials, int* progress, int* result)
{
    // initialize successes to 0
    int successes = 0;

    // initialize boxes array
    array<int, NUM_BOXES> trial_boxes = init_boxes();

    //get non deterministic seed and create rng
    random_device dev;
    mt19937 rng(dev());

    // loop through the amount of trials this thread is doing
    for (int i = 0; i < trials; ++i)
    {
        // shuffle the numbers inside of boxes
        shuffle(trial_boxes.begin(), trial_boxes.end(), default_random_engine(rng()));

        // if trial returns true, increment successes by 1
        if (trial(trial_boxes))
        {
            successes += 1;
        }

        // update the progress
        *progress = i + 1;
    }

    // store results in reference and return
    *result = successes;

    return;
}


//dispatches the threads to complete the simulation
Results dispatch_threads(const vector<int>& distro, const int trials, const int num_threads)
{
    // initialize Results struct and store number of trials
    Results sim_results;
    sim_results.trials = trials;

    // initalize vector to store each thread 
    vector<thread> threads(num_threads);

    // initialize vector to store the results of each thread 
    vector<int> thread_results(num_threads, 0);

    // initialize vector to store the progress of each thread
    vector<int> thread_progress(num_threads, 0);
    
    //initialze progress 
    int progress = 0;

    //set cursor to be invisible
    cout << "\033[?25l\n";

    // get time at start of simulation
    auto start = std::chrono::high_resolution_clock::now();

    // start each thread 
    for (int i = 0; i < num_threads; ++i)
    {
        threads[i] = thread(thread_driver, distro[i], &thread_progress[i], &thread_results[i]);
    }
    
    // print out progress of simulation
    do 
    {
        // get the total progress of all threads
        progress = accumulate(thread_progress.begin(), thread_progress.end(), 0);
        cout << "\033[1F" << progress << " / " << trials << " | " << fixed << setprecision(2) << float(progress)/float(trials)*100 <<  " %\n";
    }
    while(progress != trials);

    // stop timer as the simulation is complete
    auto stop = std::chrono::high_resolution_clock::now();

    // join each of the threads
    for (int i = 0; i < num_threads; ++i)
    {
        threads[i].join();
    }

    // set cursor as visible again and stop ansi
    cout << "\033[?25h\033[0m\n";

    // get the total successes of the simulation
    sim_results.total_successes = accumulate(thread_results.begin(), thread_results.end(), 0);

    // set the success rate
    sim_results.success_rate = float(sim_results.total_successes) / float(trials) * 100;

    // get the duration of the simulation in milliseconds
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    // calculate the number of seconds
    sim_results.sim_secs = float(duration.count())/float(1000);

    // calculate the number of mins
    sim_results.sim_mins = sim_results.sim_secs / 60;

    // take the minutes out of the seconds count to avoid double counting
    sim_results.sim_secs -= sim_results.sim_mins * 60;

    // return the results
    return sim_results;
}

// returns a vector containing the distribution of trials that each thread will do
vector<int> get_distro(const int trials, const int num_threads)
{
    // get the base amount of trials per thread
    int trials_per_thread = trials / num_threads;

    // get the remainder if exists
    int remainder = trials % num_threads;

    // initialize vector
    vector<int> distro(num_threads, 0);

    // for each thread
    for (int i = 0; i < num_threads; ++i)
    {
        // set the base amount of trials
        distro[i] = trials_per_thread;

        // distribute the remainder as evenly as possible
        if (i < remainder)
        {
            distro[i] += 1;
        }
    }

    // return the distribution vector
    return distro;
}

// prints out the results of the simulation
void print_results(const Results& r)
{
    cout << "**********************************************************************************************************\n";
    cout << "Language used: C++\n";
    cout << "The prisoners succeeded " << r.total_successes << " times out of " << r.trials << " trials\n";
    cout << "Success rate: " << fixed << setprecision(3) << r.success_rate << "%\n";
    cout << "Total elapsed time: " << fixed << setprecision(3) << r.sim_mins << " minutes " << r.sim_secs << " seconds\n";
    cout << "**********************************************************************************************************\n";
    return;
}

// get the number of trials the user wants to simulate
int get_num_trials()
{
    // regular expression where string is a positive integer
    regex re("[1-9][0-9]*");

    //string to store user input
    string input;

    // while the user has not supplied a positive integer
    while (true)
    {
        // prompt the user
        cout << "How many trials would you like to simulate?: " << flush;

        // take input and store it as string
        cin >> input;

        // check if the string is a valid integer using regex
        // if it is, return the integer
        if (regex_match(input, re))
        {
            return stoi(input);
        }

        // otherwise print out error message
        cout << "That is not a positive integer\n";

        // clear string and repeat
        input.clear();
    }
}


int main()
{
    // get the number of trials that the user wants to simulate
    int trials = get_num_trials();

    // get the number of threads to use
    int num_threads = thread::hardware_concurrency();

    // get the distribution of trials for each thread
    vector<int> distro = get_distro(trials, num_threads);

    // run the simulation and get results
    Results simulation_results = dispatch_threads(distro, trials, num_threads);

    // print he results
    print_results(simulation_results);

    // exit
    return 0;
}