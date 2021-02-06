#include<stdio.h>
#include"../inc/struct.h"
#include"../inc/read.h"
#include"../inc/main_func.h"
#include"../inc/print.h"
#include"../inc/rules.h"

#define OK 0


int main(void)
{
    print_rules();

    short int rc = 0;
    float_number number_1;

    puts("                                 -+|........|.........|..........|E-+|...|");
    printf("Введите 1-ое вещественное число:  ");

    rc = read_number(&number_1);

    if (rc != OK)
    {
        return rc;
    }

    normalization(&number_1);


    float_number number_2;
    puts("\n                                 -+|........|.........|..........|E-+|...|");
    printf("Введите 2-ое вещественное число:  ");

    rc = read_number(&number_2);

    if (rc != OK)
    {
        return rc;
    }


    normalization(&number_2);

    int result[60] = {0}, res_power, ind;

    rc = multiply(number_1, number_2, result, &res_power, &ind);

    if (rc != OK)
    {
        return rc;
    }

    print_result(number_1, number_2, result, res_power, ind);
    
    return rc;
}
