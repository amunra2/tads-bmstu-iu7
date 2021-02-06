#include"../inc/struct.h"

#ifndef PRINT_INFO_H

#define PRINT_INFO_H

#define MAX_SIZE 1000

#define OK_SEARCH 0

#define ERR_UNRIGHT_START_PRICE -15
#define ERR_UNRIGHT_END_PRICE -16
#define ERR_START_CANNOT_BE_BIGGER_THEN_END_PRICE -17

void print_table(table_t table);

void print_table_keys(table_t table);

void print_table_by_keys(table_t table);

short int search(table_t table);

#endif
