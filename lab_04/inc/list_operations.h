#include<stdio.h> 
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"../inc/macrologger.h"
#include"../inc/structs.h"
#include"../inc/print_menu.h"
#include"../inc/expression.h"

#ifndef LIST_OPERATIONS_H
#define LIST_OPERATIONS_H

#define NO_MISTAKES 0
#define STACK_IS_CLEAR 1
#define STACK_IS_READY 0
#define CLEAR 0
#define INITED 1

#define OK_CREATE 0
#define OK_PUSH 0
#define OK_ADD 0
#define OK_DEL 0
#define OK_PRINT 0
#define OK_COUNT 0


#define ERR_UNRIGHT_LIST_MAX_LEN -2
#define ERR_UNRIGHT_LIST_CUR_LEN -3
#define ERR_ALLOCATE_MEMORY -4
#define ERR_OWERFLOW_STACK -5
#define ERR_UNRIGHT_ELEM -6
#define ERR_UNRIGHNT_CUR_SIZE_LIST 7


int create_list(list_t **stack_list, int *max_len);

int print_list(list_t *list);

int pop_list(list_t **list);

int push_node(list_t **list, const int num);

list_t* create_node(const int num);

void free_list(list_t **list);

int add_elem_list(list_t **list, int *max_len);

int result_list(int *res);

void add_adress(arr_clear_t *arr, list_t *list);

void print_arr_adress(arr_clear_t arr);

void del_adress(arr_clear_t *arr, list_t *list);

int calculate_list(exp_t exp);


#endif
