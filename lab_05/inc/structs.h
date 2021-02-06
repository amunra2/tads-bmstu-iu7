#ifndef STRUCTS_H
#define STRUCTS_H

#define MAX_ELEMS 5000

typedef struct arr_s
{ 
    int arr[MAX_ELEMS];
    int begin;
    int end;
    int size;
} arr_t;

typedef struct node_s
{
    int elem;

    struct node_s *next;
} node_t;

typedef struct list_s
{
    node_t *head;
    node_t *tail;

    int size;
} list_t;


typedef struct
{
    node_t *arr_clear[1000]; 
    int len;
} arr_clear_t;

#endif