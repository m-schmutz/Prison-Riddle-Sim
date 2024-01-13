#ifndef TRIAL_H
#define TRIAL_H

#include <stdio.h>

void copy_random_nums(__uint8_t* src, __uint8_t* dest);
int next_search_num(const __int8_t* visited, const __int8_t last_number);
int find_number(const __int8_t search_number, const __int8_t* boxes, __int8_t* visited);
int run_trial(const __uint8_t* rbytes);


#endif