#include<stdio.h>


#ifndef STRUCTS_H
#define STRUCTS_H 


typedef struct list
{
    int ind;

    int num;

    struct list *next;
} list_t;


typedef struct array
{
    int *arr;

    int len;
} array_t;


typedef struct
{
    char sym[1001];

    int len;
} exp_t;


typedef struct
{
    list_t *arr_clear[1000]; 
    int len;
} arr_clear_t;




#endif