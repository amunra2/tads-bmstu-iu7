#ifndef SORTS_H

#define SORTS_H

#include<stdlib.h>
#include<stdio.h>
#include"../inc/struct.h"
#include"../inc/file_work.h"

#define GHZ 3500000000

void bubble_table(table_t table);

void bubble_table_keys(table_t table);

void qsort_table(table_t table);

void qsort_table_keys(table_t table);

short int compare_sorts(FILE *flats_file);

#endif
