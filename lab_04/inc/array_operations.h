#ifndef ARRAY_OPERATIONS_H
#define ARRAY_OPERATIONS_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"../inc/macrologger.h"
#include"../inc/structs.h"
#include"../inc/print_menu.h"
#include"../inc/expression.h"

#define NO_MISTAKES 0
#define STACK_IS_CLEAR 1
#define CLEAR 0
#define INITED 1

#define OK_CREATE 0
#define OK_PUSH 0
#define OK_ADD 0
#define OK_DEL 0
#define OK_PRINT 0
#define OK_COUNT 0
#define STACK_READY 0

#define ERR_ALLOCATE_MEMORY_ARR -31
#define ERR_OWERFLOW_STACK_ARR -32
#define ERR_UNRIGHT_ELEM_ARR -33
#define ERR_UNRIGHT_ARR_MAX_LEN_ARR -34
#define ERR_UNRIGHNT_CUR_SIZE -35

int create_arr(array_t *array, int *max_len);

int print_arr(array_t stack_arr);

int pop_arr(array_t *stack_arr);

void push_arr(array_t *array, int num);

void free_arr(array_t *static_arr);

int add_elem_arr(array_t *array, int *max_len);

int result_arr(int *res);

int calculate_arr(exp_t exp);

#endif