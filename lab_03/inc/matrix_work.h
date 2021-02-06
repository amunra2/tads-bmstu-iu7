#include"../inc/structs.h"
#include"../inc/macrologger.h"
#include<stdio.h>
#include<time.h>

#ifndef MATRIX_WORK_H

#define MATRIX_WORK_H

#define OK_CREATE 0
#define OK_FILL 0
#define OK_PARSE 0

#define NO_MISTAKES 0

#define ERR_UNRIGHT_INPUT_OF_SIZES -10
#define ERR_UNRIGHT_SIZES -11
#define ERR_MEMORY_ALLOCATE -12
#define ERR_UNRIGHT_INPUT_TYPE -13
#define ERR_UNRIGHT_INPUT_NO_ZEROES_ELEMS -14
#define ERR_UNRIGHNT_ELEM -15
#define ERR_UNRIGHNT_X_AXIS -16
#define ERR_UNRIGHNT_Y_AXIS -17

int create_matrix(static_matrix_t *matrix_stat, list_t *list);

int convert_matrix(static_matrix_t matrix_stat, matrix_t *matrix);

int compare_vectors(list_t vec1, list_t vec2);

#endif
