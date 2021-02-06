#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include"../inc/structs.h"


#ifndef TASK_H
#define TASK_H

#define YES_WAY 1
#define NO_WAY 0

#define OK_READ 0
#define OK_ALLOCATE 0
#define OK_FIND 0

#define ERR_ALLOCATE_MEMORY -1
#define ERR_WRONG_SIZE -2
#define ERR_WRONG_GRAPH -3

int read_data(mat_t *matrix, int *max_way, int *start_place);

int find_empty_roads(mat_t matrix, no_roads_t **clear);

void free_matrix(mat_t matrix);

int find_ways_combinations(mat_t matrix, no_roads_t *clear, int max_way, int start_place);

#endif