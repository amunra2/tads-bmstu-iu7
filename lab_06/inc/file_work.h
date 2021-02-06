#include<stdio.h>
#include<stdlib.h>
#include"../inc/structs.h"

#ifndef FILE_WORK_H
#define FILE_WORK_H

#define NO_MISTAKES 0

#define OK_READ 0
#define OK_LEN 0

#define ERR_WRONG_FILE_NAME -1
#define ERR_WRONG_NUM -2
#define ERR_ALLOCATE_MEMORY -3


int read_file(arr_t *arr, char *filename);

#endif