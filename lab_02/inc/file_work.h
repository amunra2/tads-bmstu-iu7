#include"../inc/struct.h"

#ifndef FILE_WORK_H

#define FILE_WORK_H

#define MAX_SIZE 1000

#define OK_FILE 0
#define OK_ADDING 0
#define OK_DEL 0

//for file
#define ERR_UNRIGHT_ELEMENTS -3

//for adding
#define ERR_UNRIGHT_CITY_INPUT -4
#define ERR_UNRIGHT_SQUARE_INPUT -5
#define ERR_UNRIGHT_ROOMS_INPUT -6
#define ERR_UNRIGHT_COST_INPUT -7
#define ERR_UNRIGHT_PRIMARY_INPUT -8
#define ERR_UNRIGHT_DECOR_INPUT -9
#define ERR_UNRIGHT_YEAR_INPUT -10
#define ERR_UNRIGHT_OWNER_INPUT -11
#define ERR_UNRIGHT_RESIDENT_INPUT -12
#define ERR_UNRIGHT_ANIMAL_INPUT -13
#define ERR_TOO_MUCH_FLATS -14
#define ERR_FILE_CLEAR -15

short int read_file(FILE *flats_file, appartment_t *flats_arr, int *size, keys_t *keys);

short int add_flat(appartment_t *flats_arr, int *size, keys_t *keys);

short int delete_by_square(appartment_t *flats_arr, int *size, keys_t *keys);

void swap_keys(keys_t *keys, int i, int j);

void swap_flats(appartment_t *flats_arr, int i, int j);

#endif
