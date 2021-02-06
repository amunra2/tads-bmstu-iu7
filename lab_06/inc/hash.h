#include<stdio.h>
#include<stdlib.h>
#include"../inc/structs.h"


#ifndef HASH_H
#define HASH_H

#define OK_HASH 0

#define ERR_OWERFLOW_TABLE -5
#define ERR_ALLOCATE_MEMORY -3


void print_hash_table(hash_t hash_table);

int add_hash(hash_t *hash_table, int data, int *count);

int fill_hash_table(hash_t *hash_table, arr_t *arr, int size);

int near_prime(int num);

#endif