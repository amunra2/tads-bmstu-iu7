#include"../inc/struct.h"
#include"../inc/print.h"


void check_arr(int *arr, int ind, int end_arr)
{
    if (arr[end_arr + 1] >= 5)
    {
        int i = end_arr;
        while (arr[i] == 9)
        {
            arr[i] = (arr[i] + 1) % 10;
            i--;
        }
        arr[i] = (arr[i] + 1) % 10;
    }
}


void print_result(float_number num1, float_number num2, int *result, int res_power, int ind)
{
    char res_sign_mantis;

    if (num1.mantis_sign != num2.mantis_sign)
    {
        res_sign_mantis = '-';
    }
    else
    {
        res_sign_mantis = '+';
    }

    char res_sign_eps;

    if (res_power < 0)
    {
        res_power *= -1;
        res_sign_eps = '-';
    }
    else
    {
        res_sign_eps = '+';
    }

    puts("_________________________________________________________________");

    if (result[ind] != 0)
    {
        printf("\n\nResult : %c0.", res_sign_mantis);

        int end_arr = 60;

        if (end_arr - ind > 30 )
        {
            end_arr -= (end_arr - ind - 29);
            check_arr(result, ind, end_arr);
        }

        int j = end_arr;

        if (result[j] == 0)
        {
            while (result[j--] == 0)
            {
                end_arr--;
            }
        }

        if (end_arr != 60)
        {
            end_arr += 1;
        }

        for (int i = ind; i < end_arr; i++)
        {
            printf("%d", result[i]);
        }

        printf("E%c%d\n", res_sign_eps, res_power);
    }
    else
    {
        puts("\n\nResult : +0.0E+0\n");
    }
}
