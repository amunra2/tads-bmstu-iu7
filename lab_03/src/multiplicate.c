#include"../inc/multiplicate.h"


int multiplicate_ordinary(static_matrix_t matrix, list_t list, list_t *result)
{
    list_t tmp = *result;

    //puts("YESSSSSSSS1");

    int ind = 0, num;

    //puts("YESSSSSSSS");

    for (int i = 0; i < matrix.x_len; i++)
    {
        num = 0;

        for (int j = 0; j < matrix.y_len; j++)
        {
            num += matrix.matrix[i][j] * list.arr[j];
        }

        tmp.arr[ind++] = num;
    }

    *result = tmp;

    //puts("YESSSSSSSS2");

    //puts("\n\nРезультат вычислений: ");

    //print_list(tmp);

    return OK_MULTIPLICATE;
}


int multiplicate_parsed_matrix(matrix_t matrix, list_t list, list_t *result)
{
    list_t tmp = *result;

    LOG_DEBUG("size matrix %d", matrix.size);

    matrix.ia[matrix.ia_len] = matrix.no_zeroes;

    int k = 0, flag = 0, q = 0;

    for (int i = 0; i < matrix.ia_len; i++)
    {
        if (matrix.ia[i] == -1)
        {
            tmp.arr[i] = 0;
            k++;
        }
        else
        {
            for (int j = matrix.ia[i]; j < matrix.ia[i + 1]; j++)
            {
                LOG_DEBUG("matrix.ia[%d] = %d, matrix.ia[%d] = %d", i, matrix.ia[i], i + 1, matrix.ia[i + 1]);
                tmp.arr[k] += matrix.a[j] * list.arr[matrix.ja[j]];

                flag = 1;
            }

            if (flag == 0)
            {
                q++;
            }
            else if (flag == 1)
            {
                k = k + q + 1;
                q = 0;
                flag = 0;
            }

            LOG_DEBUG("tmp.arr[%d] = %d\n", i, tmp.arr[i]);
        }
    }


    *result = tmp;

    //puts("\n\nРезультат через разреженную матрицу:\n");

    //print_list(tmp);

    return OK_MULTIPLICATE;
}


int compare_vectors(list_t vec1, list_t vec2)
{
    if (vec1.len != vec2.len)
    {
        printf("Длины не равны: %d %d", vec1.len, vec2.len);
        return ERR_DIFFERENT_LENGTH;
    }
    for (int i = 0; i < vec1.len; i++)
    {
        if (vec1.arr[i] != vec2.arr[i])
        {
            printf("\nЭлементы vec1[%d] = %d, vec2[%d] = %d различны\n", i, vec1.arr[i], i, vec2.arr[i]);
            return ERR_DIFFERENT_ELEMENTS;
        }
    }

    puts("\n\nВекторы идентичны\n");

    return 0;
}
