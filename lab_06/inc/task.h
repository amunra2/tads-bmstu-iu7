#include<stdio.h>
#include<stdlib.h>

#include"../inc/structs.h"
#include"../inc/file_work.h"
#include"../inc/print_info.h"
#include"../inc/ddp_avl.h"
#include"../inc/hash.h"
#include"../inc/timer.h"

#ifndef TASK_H
#define TASK_H

#define RUNS 1000

#define OK_ADD 0

#define ERR_NUM_REPEAT -7

int add_all(node_t **avl, node_t **ddp, arr_t *arr, hash_t *hash_table, char *filename);


#endif