#include "boxes.h"

#define URANDOM "/dev/urandom"
#define RANDOM "/dev/random"
#define READ "r"

#define SUCCESS 0 
#define FAILURE 1


// read in <size> bytes from a random source and store in the <dest> pointer
int random_bytes(void* dest, int size) {
    // open random file
    FILE* fptr = fopen(RANDOM, READ);

    // read in size bytes
    int check = fread(dest, size, 1, fptr);

    //close the file
    fclose(fptr);

    //check if the read was successful
    if (!check) {
        perror("urandom read failed\n");
        return FAILURE;
    }

    // return that read was successful
    return SUCCESS;
}


// return a uint8 array of <size> random bytes
__uint8_t* random_array(int size) {
    //allocate a new array for <size> uint8s
    __uint8_t* arr = malloc(size);

    // read random bytes into the array
    random_bytes(arr, size);

    // return the array
    return arr;
}


// swap the elements given at index_a and index_b
void swap_elements(__int8_t* boxes, int idxa, int idxb) {
    // store element a
    __int8_t temp = boxes[idxa];

    // copy element b to index a
    boxes[idxa] = boxes[idxb];

    // copy element a to index b
    boxes[idxb] = temp;
    return;
}


// randomize the <boxes> array using random numbers contained in <random_nums>
void randomize_boxes(__int8_t* boxes, const __uint8_t* random_nums) {
    //temporary array
    __int8_t temp[NUM_BOXES];

    // put values into the array to be randomized
    for (__int8_t i = 0; i < NUM_BOXES; ++i) {
        temp[i] = i;
    } 

    // modulus to control the group of numbers that can be picked
    int modulus = NUM_BOXES;

    // loop through every box and place a random number in it
    for (int i = 0; i < NUM_BOXES; ++i) {
        // get a random index to pick number
        int idx = random_nums[i] % modulus;

        // move picked element to the boxes array
        boxes[i] = temp[idx];

        // put the picked element out of the range of the next pick
        swap_elements(temp, idx, --modulus);
    }
    return;
}


// print out an array
void print_boxes(const __int8_t* boxes) {
    printf("[");

    for (int i = 0; i < NUM_BOXES; ++i) {
        printf(" %u,", boxes[i]);
    }

    printf("]\n");
}