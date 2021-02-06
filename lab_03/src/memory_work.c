#include"../inc/memory_work.h"


void free_matrix(static_matrix_t matrix)
{
    for (int i = 0; i < matrix.x_len; i++)
    {
        free(matrix.matrix[i]);
    }

    free(matrix.matrix);
}


int allocate_matrix(static_matrix_t *matrix_stat)
{
    int **matrix = calloc(matrix_stat->x_len, sizeof(int*));

    if (!matrix)
    {
        return ERR_ALLOCATE_MEMORY;
    }

    for (int i = 0; i < matrix_stat->x_len; i++)
    {
        matrix[i] = calloc(matrix_stat->y_len, sizeof(int));

        if (!matrix[i])
        {
            free_matrix(*matrix_stat);
            return ERR_ALLOCATE_MEMORY;
        }
    }

    matrix_stat->matrix = matrix;

    return OK_ALLOCATE;
}


void free_parsed_matrix(matrix_t matrix)
{
    free(matrix.a);
    free(matrix.ia);
    free(matrix.ja);
}


int allocate_parsed_matrix(matrix_t *matrix)
{
    matrix_t tmp;

    tmp.a = calloc(matrix->a_len, sizeof(int));

    tmp.ja = calloc(matrix->a_len, sizeof(int));

    tmp.ia = calloc(matrix->ia_len + 1, sizeof(int));


    //printf("%ld", size * sizeof(int));

    if ((NULL == tmp.a) || (NULL == tmp.ja) || (NULL == tmp.ia))
    {
        return ERR_ALLOCATE_MEMORY;
    }

    matrix->a = tmp.a;
    matrix->ja = tmp.ja;
    matrix->ia = tmp.ia;

    return OK_ALLOCATE;
}


void free_list(list_t list)
{
    free(list.arr);
}


int allocate_list(list_t *list)
{
    list_t tmp;
    tmp.arr = calloc(list->len, sizeof(int));

    if (!tmp.arr)
    {
        return ERR_ALLOCATE_MEMORY;
    }

    list->arr = tmp.arr;

    return OK_ALLOCATE;
}


void free_all(matrix_t matrix, static_matrix_t matrix_stat, list_t list)
{
    free_list(list);
    free_matrix(matrix_stat);
    free_parsed_matrix(matrix);
}












