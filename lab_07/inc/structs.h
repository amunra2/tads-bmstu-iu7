#include<stdio.h>


#ifndef STRUCTS_H
#define STRUCTS_H


typedef struct mat_r
{
    int **data;

    int size;
} mat_t;

typedef struct no_roads_r
{
    int i;
    int j;

    int len;
} no_roads_t;


#endif