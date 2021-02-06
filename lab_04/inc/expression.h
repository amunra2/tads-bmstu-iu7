#ifndef EXPRESSION_H
#define EXPRESSION_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"../inc/structs.h"

#define RIGHT_OPERATION 1
#define UNRIGHNT_SYMBOL 0 

#define OK_READ_EXPRESSION 0

#define ERR_WRONG_SYMBOL -21 
#define ERR_UNRIGHT_LIST_LEN_MAX -22
#define ERR_FIRST_SYM_NOT_NUM -23
#define ERR_LAST_SYM_NOT_NUM -24

int read_expression(exp_t *expression);

int read_num_from_arr_char(char *sym, int *ind);

int check_operation(char sym);

int translate_operation(char sym);

int check_priority(int sym);

#endif