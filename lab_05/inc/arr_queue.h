#ifndef ARR_QUEUE_H
#define ARR_QUEUE_H

#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<math.h>
#include"../inc/structs.h"
#include"../inc/timer.h"

// Time
#define T1_IN_B 1
#define T1_IN_E 5
 
#define T2_IN_B 0
#define T2_IN_E 3

#define T1_OUT_B 0
#define T1_OUT_E 4

#define T2_OUT_B 0
#define T2_OUT_E 1

// AMOUNT
#define COUNT 1000
#define INTERVAL 100



void init_arr_queue(arr_t *queue);

void push_arr_queue(arr_t *queue, int elem);

void pop_arr_queue(arr_t *queue);

void print_arr_queue(arr_t queue);

void task_arr(void);

int clear_check_arr_queue(arr_t queue);

int owerflow_arr_queue(arr_t queue);

#endif