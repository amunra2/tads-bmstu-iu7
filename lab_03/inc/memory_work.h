#include"../inc/structs.h"
#include<stdlib.h>
#include<stdio.h>

#ifndef MEMORY_WORK_H

#define MEMORY_WORK_H

#define OK_ALLOCATE 0
#define ERR_ALLOCATE_MEMORY -20

int allocate_matrix(static_matrix_t *matrix_stat);

void free_matrix(static_matrix_t matrix);

int allocate_parsed_matrix(matrix_t *matrix);

void free_parsed_matrix(matrix_t matrix);

int allocate_list(list_t *list);

void free_list(list_t list);

void free_all(matrix_t matrix, static_matrix_t matrix_stat, list_t list);

#endif
