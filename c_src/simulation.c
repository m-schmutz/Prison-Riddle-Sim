#include "boxes.h"
#include "trial.h"

#define TRIALS 2


/*
 - initialize all random numbers needed for a trial in large array
 - copy NUM_BOXES into the static array
 - 




 Running the simulation
 - 

*/


int main() {

    // BOXES_ARRAY;

    __uint8_t* rnums = random_array(NUM_BOXES * TRIALS);

    for (int i = 0; i < TRIALS; ++i) {
        int result = run_trial(rnums + (NUM_BOXES * i));

        printf("Result = %d\n", result);
    }

    

   
}

