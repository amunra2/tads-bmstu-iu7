#ifndef STRUCTS_H

#define STRUCTS_H

typedef struct
{
    int **matrix;
    int x_len;
    int y_len;

    int no_zeroes;
} static_matrix_t;


typedef struct 
{
    int *a;
    int *ja;
    int *ia;

    int a_len;
    int ia_len;
    int size;
    int no_zeroes;
} matrix_t;


typedef struct
{
    int *arr;
    int len;
} list_t;



#endif