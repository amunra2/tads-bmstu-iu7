#include"../inc/struct.h"
#include"../inc/read.h"


short int read_number(float_number *number)
{
    int c;

    // Read mantissa sign
    if ((c = getchar()) != '\n')
    {
        if ((c == EOF) || strchr("+-", c) == NULL)
        {   
            puts("ERR_UNRIGHT_MANTISS_SIGN");
            return ERR_UNRIGHT_MANTISS_SIGN;
        }

        number->mantis_sign = c;
    }
    else
    {
        puts("ERR_NO_NUMBER");
        return ERR_NO_NUMBER;
    }

    // Read mantissa
    int i = 0;
    number->point_place = NO_POINT;

    while ((c = getchar()) != 'E')
    {
        if ((c == EOF) || (c == '\n'))
        {   
            puts("ERR_NO_EPSILON");
            return ERR_NO_EPSILON;
        }

        if ((c == '.') && (number->point_place == NO_POINT))
        {
            number->point_place = i;
        }
        else if ((c == '.') && (number->point_place != NO_POINT))
        {
            puts("ERR_TOO_MUCH_POINTS");
            return ERR_TOO_MUCH_POINTS;            
        }

        if ((c != '.') && (strchr("0123456789", c) == NULL))
        {
            puts("ERR_UNRIGHT_MANTISS_NUMBER");
            return ERR_UNRIGHT_MANTISS_NUM;
        }

        number->mantissa[i++] = c;

        if (i > MANTISSA_MAX_LEN)
        {
            puts("ERR_MANTISSA_TOO_LONG");
            return ERR_MANTISSA_TOO_LONG;
        }
    }

    number->num_of_digits = i - 1;
    number->mantissa[i] = '\0';

    if (number->point_place == NO_POINT)
    {
        puts("ERR_NUMBER_MUST_BE_FLOAT");
        return ERR_NUMBER_MUST_BE_FLOAT;        
    }

    if (number->num_of_digits == 0)
    {
        puts("ERR_ONLY_POINT");
        return ERR_ONLY_POINT;
    }

    // Read Power Sign
    if ((c = getchar()) != '\n')
    {
        if ((c == EOF) || (strchr("+-", c) == NULL))
        {   
            puts("ERR_UNRIGHT_POWER_SIGN");
            return ERR_UNRIGHT_POWER_SIGN;
        }

        number->eps_sign = c;
    }

    // Read Power Sign
    int num;
    if (scanf("%d", &num) != 1)
    {
        puts("ERR_UNRIGHT_POWER");
        return ERR_UNRIGHT_POWER;
    }
    else if (num / 100000 >= 1)
    {
        puts("ERR_POWER_TOO_LONG");
        return ERR_POWER_TOO_LONG;
    }

    c = getchar();
    if ((c != EOF) && (c != '\n'))
    {
        puts("ERR_UNRIGHT_POWER");
        return ERR_UNRIGHT_POWER;
    }
    else
    {
        number->eps_num = num;
    }
    
    return OK_READ_NUMBER;
}
