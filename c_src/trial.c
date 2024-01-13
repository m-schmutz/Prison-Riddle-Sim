#include "trial.h"
#include "boxes.h"

// print out an array
void print_array(const __int8_t* boxes, const int size) {
    printf("[");

    for (int i = 0; i < size; ++i) {
        printf(" %d,", boxes[i]);
    }

    printf("]\n");
}


// copy NUM_BOXES random numbers to the static array
void copy_random_nums(__uint8_t* src, __uint8_t* dest) {
    // copy <NUM_BOXES> numbers from src array to dest array
    memcpy(dest, src, NUM_BOXES);
    return;
}


// find the next number to start the search at 
int next_search_num(const __int8_t* visited, const __int8_t last_number) {
    // start at the last number that was searched for
    int new_search;

    // loop until the next available number is found
    for (int i = last_number + 1; i < NUM_BOXES; ++i) {
        if (!visited[i]) {
            new_search = i;
            break;
        }
    }
    // return new search number
    return new_search;
}


// simulates a prisoner attempting to find their number 
// returns the number of boxes contained in the loop
// all numbers contained in this loop are stored in the visited array 
int find_number(const __int8_t search_number, const __int8_t* boxes, __int8_t* visited) {
    // index of the box we are looking at. This starts at the number we are looking for
    __int8_t paper_number = search_number;


    // loop through boxes to find number
    // any search that takes longer than <MAX_ATTEMPTS> is considered a fail
    for (int i = 0; i < MAX_ATTEMPTS; ++i) {
        // get the number in the box at the index on paper found
        // for first number, this is the prisoners number
        paper_number = boxes[paper_number];


        // updated the visited array so that we know that this number has been reached
        visited[paper_number] = 1;

        // check if search number has been found
        if (paper_number == search_number) {            
            return ++i;
        }
    }
    // if the number is not found, outside of range and therefore failing
    return MAX_ATTEMPTS + 1;
}


// attempt a trial:
// simulate each prisoner finding their number
// - There can be shortcuts done to reduce iterations needed
// - if a search takes longer than 50, the entire trial fails
// - If the amount of boxes left over is 50 or less after N searches, the trial succeeds
int run_trial(const __uint8_t* rbytes) {
    // initialize boxes and visited array
    __int8_t boxes[NUM_BOXES];
    __int8_t visited[NUM_BOXES];

    // keep track of the number of prisoner numbers yet to be found
    int boxes_left = NUM_BOXES;

    // randomize the box numbers
    randomize_boxes(boxes, rbytes);


    print_boxes(rbytes);


    // current search number
    int search_number = 0;

    // assume success until a loop longer than 50 is found
    int success = 1;


    /*
    If the number of unchecked boxes are < MAX_ATTEMPTS boxes left, we can stop searching and assume that one of two situations have occurred:
     - A loop > MAX_ATTEMPTS has been found, meaning that the trial fails
     - Loops < MAX_ATTEMPTS have been found, meaning that it is no longer possible for a loop > MAX_ATTEMPTS to exist
    
    */
    while (boxes_left > MAX_ATTEMPTS) {
        // get the length of the loop that the search number is contained in
        int loop_length = find_number(search_number, boxes, visited);

        // check if the loop length is larger than 50, set the success to 0 if it is
        switch (loop_length) {
            case MAX_ATTEMPTS + 1:
                success = 0;
            
            default:
                // subtract the length of the loop just found
                boxes_left -= loop_length;

                // update the search number
                search_number = next_search_num(visited, search_number);
        }
    }

    // return the success state of the trial
    return success;
}
