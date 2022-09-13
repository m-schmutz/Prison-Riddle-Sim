#include <iostream>
#include <array>
#include <algorithm>
#include <random>       
#include <chrono>    
#include <vector>   

using std::array;
using std::cout;
using std::shuffle;
using std::default_random_engine;
using std::vector;

// obtain a time-based seed:
const int NUM_BOXES = 100;

const int MAX_ATTEMPTS = 50;


void print_array(const array<int, NUM_BOXES>& arr)
{
    for (int i = 0; i < NUM_BOXES; ++i)
    {
        cout << arr[i] << '\n';
    }
    return;
}


array<int, NUM_BOXES> init_boxes()
{
    array<int, NUM_BOXES> boxes;

    for (int i = 0; i < NUM_BOXES; ++i)
    {
        boxes[i] = i + 1;
    }

    return boxes;
}


bool find_number(const array<int, NUM_BOXES>& trial_boxes, const int num)
{
    int box_index = num - 1;

    for (int i = 0; i < MAX_ATTEMPTS; ++i)
    {
        if (trial_boxes[box_index] == num)
        {
            return true;
        }

        box_index = trial_boxes[box_index] - 1;
    }

    return false;
}


bool trial()
{
    // create seed based on current time
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    // initialize boxes array
    static array<int, NUM_BOXES> trial_boxes = init_boxes();

    // shuffle the numbers inside of boxes
    shuffle(trial_boxes.begin(), trial_boxes.end(), default_random_engine(seed));

    for (int num = 1; num <= NUM_BOXES; ++num)
    {
        if (!find_number(trial_boxes, num))
        {
            return false;
        }
    }

    return true;
}


unsigned int thread_driver(const int trials)
{
    unsigned int successes = 0;
    for (int i = 0; i < trials; ++i)
    {
        if (trial())
        {
            successes += 1;
        }
    }

    return successes;
}


int main()
{
    
    int trials = 100000;

    auto start = std::chrono::high_resolution_clock::now();
    int total_successes = thread_driver(trials);
    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    float success_rate = (float(total_successes) / float(trials)) * 100;


    float secs = float(duration.count())/1000.000;

    int mins = secs / 60;


    cout << "**********************************************************************************************************\n";
    cout << "The prisoners succeeded " << total_successes << " times out of " << trials << " trials\n";
    cout << "Success rate = " << success_rate << "%\n";
    cout << "Total elapsed time " << mins << " minutes " << secs << " seconds\n";
    cout << "**********************************************************************************************************\n";


    return 0;
}