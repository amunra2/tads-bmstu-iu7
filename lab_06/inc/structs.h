#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct arr_r
{
    int *data;

    int len;
    int capacity; 
    int max_cap;
} arr_t;


typedef struct node_r
{
    int data;
    unsigned char height;

    struct node_r *left;
    struct node_r *right;
} node_t;


typedef struct hash_r
{
    int *data;
    int *key;

    int size;
} hash_t;

#endif