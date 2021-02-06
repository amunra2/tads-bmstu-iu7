#include"../inc/struct.h"
#include"../inc/main_func.h"


void swap(char *mantissa, int j)
{
    char tmp = mantissa[j];
    mantissa[j] = mantissa[j + 1];
    mantissa[j + 1] = tmp;
}


void swap1(char *mantissa, int j)
{
    char tmp = mantissa[j];
    mantissa[j] = mantissa[j - 1];
    mantissa[j - 1] = tmp;
}


void delete_num(char *mantissa, int *n, int i)
{
    for (int j = i; j < *n; j++)
    {
        swap(mantissa, j);
    }
}


unsigned short int move_arr(char *arr, int n)
{
    unsigned short int k = 0;

    for (int j = n; j > 0; j--)
    {
        swap1(arr, j);
        k++;
    }
    return k;
}


void append(char *arr, int n, int i, char elm)
{
    char tmp = arr[i];

    arr[i] = elm;

    for (int j = i + 1; j <= n; j++)
    {
        char cur = arr[j];
        arr[j] = tmp;
        tmp = cur;
    }
}


void normalization(float_number *number)
{
    int n = number->num_of_digits;

    //Do not count 0 in the end
    while(number->mantissa[n--] == '0')
    {
        number->num_of_digits--;
    }

    n = number->num_of_digits;
    
    if (number->mantissa[0] == '0')
    {
        int i = 0;

        while (strchr("123456789.", number->mantissa[i]) == NULL)
        {
            delete_num(number->mantissa, &n, i);
            number->point_place -= 1;
            number->num_of_digits -= 1;
        }
    }

    if (number->mantissa[0] != '0')
    {
        unsigned short int k;

        k = move_arr(number->mantissa, number->point_place);
        number->point_place -= k;
        
        if (number->eps_sign == '+')
        {
            number->eps_num += k;
        }
        else
        {
            number->eps_num -= k;
        }
    }

    if ((number->mantissa[number->point_place + 1] == '0') && (number->mantissa[number->point_place] == '.'))
    {
        int i = number->point_place + 1;

        int q = 0; // For zero, because it then will have unlimited cicle

        while ((number->mantissa[i] == '0') && (q++ < MANTISSA_MAX_LEN))
        {
            delete_num(number->mantissa, &n, i);
            number->num_of_digits -= 1;

            if (number->eps_sign == '+')
            {
                number->eps_num -= 1;
            }
            else
            {
                number->eps_num += 1;
            }
        }

        // SPECIAL FOR 0
        if (number->num_of_digits < 0)
        {
            number->num_of_digits = 1;
        }
    }

    // puts("\n#################################\nMy number is (normalized):");
    // printf("Point here: %d\n", number->point_place);
    // printf("%c0%s%c%c%d\n\n", number->mantis_sign, number->mantissa, number->eps, number->eps_sign, number->eps_num);
}


int find_power(float_number num1, float_number num2, int extra_power)
{
    int power_1, power_2, res_power;

    if (num1.eps_sign == '-')
    {
        power_1 = num1.eps_num * (-1); 
    }
    else
    {
        power_1 = num1.eps_num;
    }
    

    if (num2.eps_sign == '-')
    {
        power_2 = num2.eps_num * (-1);
    }
    else
    {
        power_2 = num2.eps_num;
    }

    res_power = power_1 + power_2 + extra_power;

    return res_power;
}


short int multiply(float_number num1, float_number num2, int *result, int *res_power, int *ind)
{
    int n1 = num1.num_of_digits;
    int n2 = num2.num_of_digits;
    
    int index = 59, q;
    
    int num, write, rem = 0;
    
    for (int i = n1; i > 0; i--)
    {
        q = index;
        rem = 0;
        
        for (int j = n2; j > 0; j--)
        {
            num = (num1.mantissa[i] - '0') * (num2.mantissa[j] - '0') + rem + result[q];
            
            write = num % 10;
            rem = num / 10;
            
            result[q] = write;
            q--;
        }
        
        index--;
        result[q] = rem;
    }

    int extra_power = 0;

    if (result[q] != 0)
    {
        *ind = q;
    }
    else
    {
        *ind = q + 1;
        extra_power = -1;
    }
    
    *res_power = find_power(num1, num2, extra_power);

    if (*res_power > 99999)
    {
        puts("ERR_POWER_OVERFLOW");
        return ERR_POWER_OVERFLOW;
    }

    return 0;
}
