#include"../inc/matrix_work.h"
#include"../inc/memory_work.h"
#include"../inc/list_work.h"
#include"../inc/print.h"


void random_matrix(static_matrix_t *matrix, int no_zeroes)
{
    LOG_DEBUG("ok %d", no_zeroes);
    srand(time(NULL));

    int x, y;

    for (int i = 0; i < no_zeroes; i++)
    {
        x = 0;
        y = 0;

        do
        {
            x = rand() % matrix->x_len;
            y = rand() % matrix->y_len;
        } while (matrix->matrix[x][y] != 0);


        matrix->matrix[x][y] = rand() % 100 + 1;
        LOG_DEBUG("elem [%d][%d] = %d", x, y, matrix->matrix[x][y]);
    }
}


int input_matrix(static_matrix_t *matrix, int no_zeroes)
{
    int num, x, y;

    while (no_zeroes-- > 0)
    {
        puts("\nВведите элемент матрицы: ");

        if (scanf("%d", &num) != 1)
        {
            puts("Ошибка: неверно введено число");
            return ERR_UNRIGHNT_ELEM;
        }

        puts("Введите строку матрицы (нумерация с 0): ");

        if ((scanf("%d", &x) != 1) || (x > matrix->x_len) || (x < 0))
        {
            puts("Ошибка: неверно введена строка матрицы");
            return ERR_UNRIGHNT_X_AXIS;
        }

            puts("Введите номер столбца матрицы (нумерация с 0): ");

        if ((scanf("%d", &y) != 1) || (y > matrix->y_len) || (y < 0))
        {
            puts("Ошибка: неверно введен столбец матрицы");
            return ERR_UNRIGHNT_Y_AXIS;
        }

        matrix->matrix[x][y] = num;
    }

    return OK_FILL;
}


int create_matrix(static_matrix_t *matrix_stat, list_t *list)
{
    static_matrix_t tmp = {.matrix = NULL, .x_len = 0, .y_len = 0};

    int input_type;

    puts("Вы хотите ввести матрицу:\n  1 - собственноручно\n  2 - сгенерировать случайно\n\nВведите ");

    if ((scanf("%d", &input_type) != 1) || (input_type > 2) || (input_type < 1))
    {
        puts("Ошибка: тип заполнения матрицы введён неверно");
        return ERR_UNRIGHT_INPUT_TYPE;
    }

    puts("\nВведите размер матрицы, сначала строки, потом столбцы через пробел (<= 10000 и > 0):");

    if (scanf("%d %d", &tmp.x_len, &tmp.y_len) != 2)
    {
        puts("Ошибка: неверно введены размеры матрицы");
        return ERR_UNRIGHT_INPUT_OF_SIZES;
    }

    if ((tmp.x_len < 1) || (tmp.x_len > 10000) || (tmp.y_len < 1) || (tmp.y_len > 10000))
    {
        puts("Ошибка: размеры матрицы не удовлетворяют допустимым значениям (от 1 до 10000)");
        return ERR_UNRIGHT_SIZES;
    }

    int rc = allocate_matrix(&tmp);

    if (rc != NO_MISTAKES)
    {
        puts("Ошибка: память под матрицу выделить не удалось");
        return ERR_MEMORY_ALLOCATE;
    }

    list_t tmp_list = {.arr = NULL, .len = tmp.y_len};

    rc = allocate_list(&tmp_list);

    if (rc != NO_MISTAKES)
    {
        puts("Ошибка: память под массив выделить не удалось");
        free_list(tmp_list);
        return ERR_MEMORY_ALLOCATE;
    }

    puts("\nКакое количество ненулевых элементов в матрице Вы хотите ввести?");

    int no_zeroes;

    if ((scanf("%d", &no_zeroes) != 1) || (no_zeroes > tmp.x_len * tmp.y_len) || (no_zeroes < 0))
    {
        puts("Ошибка: количество ненулевых элементов в матрице введено неверно");
        return ERR_UNRIGHT_INPUT_NO_ZEROES_ELEMS;
    }

    puts("\n\nВведите количество ненулевых элементов в векторе столбце:");

    int no_zeroes_list;

    if ((scanf("%d", &no_zeroes_list) != 1) || (no_zeroes_list < 0) || (no_zeroes_list > tmp_list.len))
    {
        LOG_DEBUG("no_zeroes_list = %d", no_zeroes_list);
        puts("Ошибка: количество ненулевых элементов в векторе столбце введено неверно");
        return ERR_UNRIGHT_ELEM_IN_VECTOR;
    }

    LOG_DEBUG("OK no zeroes = %d", no_zeroes);

    if (input_type == 1)
    {
        rc = input_matrix(&tmp, no_zeroes);

        if (rc != NO_MISTAKES)
        {
            return rc;
        }

        rc = read_list(&tmp_list, no_zeroes_list);

        if (rc != NO_MISTAKES)
        {
            return rc;
        }
    }
    else if (input_type == 2)
    {
        random_matrix(&tmp, no_zeroes);
        random_list(&tmp_list, no_zeroes_list);
    }

    system("clear");

    tmp.no_zeroes = no_zeroes;

    *matrix_stat = tmp;

    *list = tmp_list;

    //puts("\n\nМатрица и вектор столбец успешно созданы\n");



    print_matrix(tmp);

    print_list(tmp_list);

    return OK_CREATE;
}


int convert_matrix(static_matrix_t matrix_stat, matrix_t *matrix)
{
    matrix_t tmp = {.a_len = matrix_stat.no_zeroes, .ia_len = matrix_stat.x_len};

    //LOG_DEBUG("Size %d\n", tmp.a_len);

    int rc = NO_MISTAKES;

    rc = allocate_parsed_matrix(&tmp);

    LOG_DEBUG("Size %d\n", tmp.a_len);

    if (rc != NO_MISTAKES)
    {
        puts("Ошибка: память под матрицу выделить не удалось");
        return ERR_MEMORY_ALLOCATE;        
    }

    LOG_DEBUG("\n%d\n", matrix_stat.matrix[0][0]);
    LOG_DEBUG("\n%d\n", tmp.ja[0]);

    int elem = 0, flag = 0;
    int rem_elem = -1;

    for (int i = 0; i < matrix_stat.x_len; i++)
    {
        flag = 0;

        //printf("%d", i);

        for (int j = 0; j < matrix_stat.y_len; j++)
        {
            //LOG_DEBUG("elem i = %d j = %d ==%d\n", i, j, matrix_stat.matrix[i][j]);
            if (matrix_stat.matrix[i][j] != 0)
            {
                tmp.a[elem] = matrix_stat.matrix[i][j];
                //LOG_DEBUG("%d\n", tmp.a[elem]);

                tmp.ja[elem] = j;
                //LOG_DEBUG("%d\n", tmp.ja[elem]);

                if (flag == 0)
                {
                    tmp.ia[i] = elem;
                    LOG_DEBUG("%d\n", tmp.ia[i]);
                    rem_elem = elem;
                    flag = 1; 
                }

                elem++; 
            }
        }

        if (flag == 0)
        {
            tmp.ia[i] = rem_elem;
        }
    }

    print_parsed_matrix(tmp);
    
    LOG_DEBUG("size %d\n", tmp.ia_len);

    tmp.size = matrix_stat.x_len * matrix_stat.y_len;
    tmp.no_zeroes = matrix_stat.no_zeroes;

    *matrix = tmp;

    LOG_DEBUG("size %d\n", matrix->ia_len);

    return OK_PARSE;
}
