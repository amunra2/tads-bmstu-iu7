#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"../inc/macrologger.h"
#include"../inc/structs.h"
#include"../inc/memory_work.h"

#ifndef LIST_WORK_H

#define LIST_WORK_H

#define OK_READ 0
#define OK_CREATE 0

#define ERR_UNRIGHT_ELEM_IN_VECTOR -30
#define ERR_UNRIGNT_ELEM -31
#define ERR_UNRIGNT_POS -32

int read_list(list_t *list, int no_zeroes);

void random_list(list_t *list, int no_zeroes);

#endif
