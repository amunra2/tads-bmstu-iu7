#include"../inc/print.h"

void print_info(void)
{
    system("clear");

    system("setterm -foreground yellow");

    puts("Сравнение умножения матрицы или разреженной матрицы\n        на вектор столбец\n\n");

    system("setterm -foreground green");
}



void print_matrix(static_matrix_t matrix)
{
    if ((matrix.x_len > 30) || (matrix.y_len > 30))
    {
        puts("Из-за большого размера, матрица не будет распечатана на экран");
        return;
    }

    puts("------------------\nПолучившаяся матрица:\n------------------");

    for (int i = 0; i < matrix.x_len; i++)
    {
        for (int j = 0; j < matrix.y_len; j++)
        {
            printf("%3d ", matrix.matrix[i][j]);
        }
        puts("");
    }
}


void print_list(list_t list)
{
    if (list.len > 30)
    {
        puts("\n\nВектор столбец слишком большой, поэтому он не будет выведен на экран\n");
        return;
    }

    puts("\n\n------------------------------------------\nВектор столбец (для удобства чтения записан в строчку)\n------------------------------------------");

    for (int i = 0; i < list.len; i++)
    {
        printf("%d ", list.arr[i]);
    }

    puts("\n\n");
}


void print_parsed_matrix(matrix_t matrix)
{
    if (matrix.a_len > 50)
    {
        puts("\n\nСлишком много ненулевых элементов, поэтому иформация о них на экран выведена не будет\n");
        return;
    }

    puts("\n\n\n------------------\nСпарсенная матрица\n------------------\nНенулевые элементы:\n");

    LOG_DEBUG("Size %d\n", matrix.a_len);

    for (int i = 0; i < matrix.a_len; i++)
    {
        printf("%2d ", matrix.a[i]);
    }

    puts("\n\nСтолбцы ненулевых элементов:\n");

    for (int i = 0; i < matrix.a_len; i++)
    {
        printf("%2d ", matrix.ja[i]);
    }

    // puts("\n\nИндекс в массиве ненулевых элементов первого вхождения элемента в строку:\n");

    // for (int i = 0; i < matrix.ia_len; i++)
    // {
    //     printf("%3d ", matrix.ia[i]);
    // }

    puts("\n\n");
}


void print_time(int64_t start, int64_t end)
{
    printf("%ld тактов, %.10lf секунд\n\n", end - start, (double)(end - start)/GHZ);
}


void print_result(matrix_t parsed_matrix, static_matrix_t matrix_stat, int64_t start1, int64_t end1, int64_t start2, int64_t end2)
{
    puts("\n\n----------------\nРезультаты замеров\n----------------\n\n");

    printf("Обычная матрица:     ");
    print_time(start1, end1);

    printf("Разреженная матрица: ");
    print_time(start2, end2);

    int memory_matrix = matrix_stat.x_len * matrix_stat.y_len * sizeof(int);
    printf("Память под обычную матрицу:      %d\n", memory_matrix);

    int memory_parsed = (parsed_matrix.a_len * 2 + parsed_matrix.ia_len) * sizeof(int);
    printf("Память под разреженную матрицу:  %d\n\n", memory_parsed);

    double percent = (double)(matrix_stat.x_len * matrix_stat.y_len) / 100;
    double filled = matrix_stat.no_zeroes / percent;


    //int filled = ((matrix_stat.x_len * matrix_stat.y_len) / matrix_stat.no_zeroes) % 1000;
    printf("Примерная заполненность матрицы %d на %d: %.1lf%% / 100%%\n", matrix_stat.x_len, matrix_stat.y_len, filled);
}


void print_parsed_list(list_t list)
{
    matrix_t tmp = {.a_len = list.len, .ia_len = 1};

    int elem = 0;

    //puts("1");

    int rc = allocate_parsed_matrix(&tmp);

    //puts("2");

    if (rc != 0)
    {
        return;
    }

    for (int i = 0; i < list.len; i++)
    {
        if (list.arr[i] != 0)
        {
            tmp.a[elem] = list.arr[i];
            tmp.ja[elem++] = i;
        }
    }

    //printf("elem = %d\n", elem);

    if (elem > 35)
    {
        puts("Слишком много ненулевых элементов, поэтому результат не будет выведен на экран\n");
        return;
    }

    puts("Ненулевые элементы:\n");
    for (int i = 0; i < elem; i++)
    {
        printf("%2d ", tmp.a[i]);
    }

    puts("\n\nПозиции ненулевых элементов:\n");

    for (int i = 0; i < elem; i++)
    {
        printf("%2d ", tmp.ja[i]);
    }

    free_parsed_matrix(tmp);
}
