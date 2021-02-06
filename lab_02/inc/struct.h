#ifndef STRUCT_H

#define STRUCT_H
#define MAX_ADDRES_NAME 100
#define FLATS_MAX 1000

//typedef enum BOOLEAN{false = 0, true} bool;

typedef struct
{
    int decorated;
} primary_t;


typedef struct
{
    int build_year;
    int previous_owners;
    int previous_rezidents;
    int animals;
} not_primary_t;


typedef union
{
    primary_t primary;
    not_primary_t secondary;
} primary_check_t;


typedef struct
{
    char address[MAX_ADDRES_NAME + 1];
    int square;
    int rooms;
    int one_m_cost;
    int is_primary;
    primary_check_t flat;
} appartment_t;


typedef struct keys
{
    int square;
    int id;
} keys_t;


typedef struct table
{
    appartment_t *flats_arr;
    keys_t *keys;
    int size;
    int maxsize; 
} table_t;

#endif