#include<stdio.h>
#include<stdlib.h>
#include"../inc/structs.h"
#include"../inc/macrologger.h"
#include"../inc/memory_work.h"
#include"../inc/print.h"

#ifndef MULTIPLICATE_H

#define MULTIPLICATE_H

#define OK_MULTIPLICATE 0
#define NO_MISTAKES 0

#define ERR_MILTIPLICATION_FAILED -35
#define ERR_DIFFERENT_LENGTH -36
#define ERR_DIFFERENT_ELEMENTS -37

int multiplicate_ordinary(static_matrix_t matrix, list_t list, list_t *result);

int multiplicate_parsed_matrix(matrix_t matrix, list_t list, list_t *result);

int compare_vectors(list_t vec1, list_t vec2);

#endif
