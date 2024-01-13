#ifndef BOXES_H
#define BOXES_H

// system include needed
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Sizes for number of boxes and attempts
#define NUM_BOXES 20
#define MAX_ATTEMPTS 10

// Macro for defining a static box array
#define BOXES_ARRAY __int8_t boxes[NUM_BOXES]


int random_bytes(void* dest, int size);
__uint8_t* random_array(int size);
void randomize_boxes(__int8_t* boxes, const __uint8_t* random_nums);
void print_boxes(const __int8_t* boxes);

#endif