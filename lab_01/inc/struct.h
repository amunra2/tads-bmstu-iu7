#ifndef STRUCT_H

#define MANTISSA_MAX_LEN 33
#define NO_POINT -1

typedef struct
{
    char mantis_sign;
    char mantissa[MANTISSA_MAX_LEN + 1];
    char eps_sign;
    int eps_num;
    int point_place;
    int num_of_digits;
} float_number;

#endif
