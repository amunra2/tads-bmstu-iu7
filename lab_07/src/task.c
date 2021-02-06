#include"../inc/task.h"


void create_graph(char *filename, char *graph_name, mat_t matrix)
{
    FILE *f = fopen(filename, "w");

    fprintf(f, "graph %s {\
    \nnode [shape = circle];\n\n", graph_name);

    for (int i = 0; i < matrix.size; i++)
    {
        for (int j = 0; j < matrix.size; j++)
        {
            if ((i != j) && (j > i) && (matrix.data[i][j] < INT_MAX))
            {
                fprintf(f, "%d -- %d [ label = %d, color = blue];\n", i + 1, j + 1, matrix.data[i][j]);
            }
            else if (matrix.data[i][j] == INT_MAX)
            {
                fprintf(f, "%d\n", i + 1);
            }
        }
    }

    fprintf(f, "}\n");

    fclose(f); //// не проверять
}


void free_matrix(mat_t matrix)
{
    for (int ind = 0; ind < matrix.size; ind++)
    {
        free(matrix.data[ind]);
    }

    free(matrix.data);
}


int allocate_matrix(mat_t *matrix)
{
    mat_t tmp;

    tmp.data = NULL;
    tmp.size = matrix->size;

    tmp.data = calloc(matrix->size, sizeof(int*));

    if (!tmp.data)
    {
        return ERR_ALLOCATE_MEMORY;
    }

    for (int ind = 0; ind < matrix->size; ind++)
    {
        tmp.data[ind] = calloc(matrix->size, sizeof(int));

        if (!tmp.data[ind])
        {
            tmp.size = ind + 1;
            free_matrix(tmp);

            return ERR_ALLOCATE_MEMORY;
        }
    }

    *matrix = tmp;

    return OK_ALLOCATE;
}


void print_matrix(mat_t matrix)
{
    printf("\n\n    ");

    for (int k = 0; k < matrix.size; k++)
    {
        printf("(%3d) ", k + 1);
    }

    puts("");

    for (int i = 0; i < matrix.size; i ++)
    {
        for (int j = 0; j < matrix.size; j++)
        {
            if (j == 0)
            {
                printf("(%2d) ", i + 1);
            }

            if (i == j)
            {
                printf("  -   ");
            }
            else
            {
                if (matrix.data[i][j] == INT_MAX)
                {
                    printf("  0   ");
                }
                else
                {
                    printf("%3d   ", matrix.data[i][j]);   
                }
            }
        }

        puts("");
    }
}


int read_data(mat_t *matrix, int *max_way, int *start_place)
{
    printf("Введите количество городов (вершин графа) (от 2 до 10): ");

    int size;
    int rc = scanf("%d", &size);

    if ((rc != 1) || (size < 2) || (size > 10))
    {
        puts("\nОшибка: неверно введено количество городов\n");

        return ERR_WRONG_SIZE;
    }

    matrix->size = size;
    
    rc = allocate_matrix(matrix);

    if (rc != 0)
    {
        return ERR_ALLOCATE_MEMORY;
    }

    int ind = 0;

    printf("\nВведите длину пути:\n");

    for (int i = 0; i < size; i++)
    {
        ind++;

        for (int j = ind; j < size; j++)
        {
            printf("\nиз %d в %d: ", i + 1, j + 1);

            int len;
            rc = scanf("%d", &len);

            if ((rc != 1) || (len < 0))
            {
                char buf[100];
                scanf("%s", buf);
                puts("\nОшибка: неверно введена метка пути. Повторите попытку\n");

                j--;
            }

            if ((len == 0) && (i != j))
            {
                len = INT_MAX;
            }

            matrix->data[i][j] = len;
            matrix->data[j][i] = len;
        }
    }

    print_matrix(*matrix);

    create_graph("in.dot", "in", *matrix);

    printf("\n\nВведите город, из которого будет производиться поиск: ");

    rc = 0;

    while (((rc = scanf("%d", start_place)) != 1) || (*start_place < 1) || (*start_place > size))
    {
        if (rc != 1)
        {
            char buffer[100];
            scanf("%s", buffer);
        }

        printf("\n\nrc = %d\n\n", rc);

        puts("\nОшибка: неверно введен пункт отправления. Повторите\n");
    }

    printf("\n\nВведите максимальную длину пути: ");
    
    rc = 0;

    while ((rc = (scanf("%d", max_way)) != 1) || (*max_way < 1))
    {
        if (rc != 1)
        {
            char buffer[100];
            scanf("%s", buffer);
        }

        puts("\nОшибка: неверно введена максимальная длина пути. Повторите\n");
    }

    return OK_READ;
}


void print_result_ways(int **res_ways, int points, int start_place, int max_way)
{
    printf("\n\nКратчайшие пути в город %d (не превышющие %d):", start_place, max_way);

    for (int i = 0; i < points; i ++)
    {
        int cur = i + 1;

        printf("\nИз города %d : %d ", cur, cur);

        while (cur != start_place)
        {
            if (cur == 0)
            {
                printf(" - ");
                break;
            }

            printf("-> %d ", res_ways[cur - 1][points - 1]);

            cur = res_ways[cur - 1][points - 1];
        }
    }

    puts("\n\n");

    puts("\nНайдено построение графа\n");
}



int dkstr(mat_t *matrix, int max_way, int start_place)
{
    mat_t ways = {.data = NULL, .size = matrix->size};
    mat_t distances = {.data = NULL, .size = matrix->size};

    allocate_matrix(&ways);
    allocate_matrix(&distances);

    int size = matrix->size;

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            distances.data[i][j] = INT_MAX;

            if (i == (start_place - 1))
            {
                distances.data[i][j] = 0;
            }
        }
    }

    distances.data[start_place - 1][0] = 0;

    for (int i = 1; i < size; i++) // поиск минимальных путей
    {
        for (int j = 0; j < size; j++)
        {
            for (int k = 0; k < size; k++)
            {
                if ((j != k) && (matrix->data[j][k] < INT_MAX) && (distances.data[k][i - 1] < INT_MAX) && (distances.data[j][i] > distances.data[k][i - 1] + matrix->data[j][k]))
                {
                    distances.data[j][i] = distances.data[k][i - 1] + matrix->data[j][k];

                    ways.data[j][i] = k + 1;
                }
            }
        }
    }

    for (int i = 0; i < size; i++) // минимальные пути до городов от заданного города start_place
    {
        //printf("\ndata[%d] = %d\n", i, distances.data[i][size - 1]);

        if (distances.data[i][size - 1] > max_way)
        {
            free_matrix(ways);
            free_matrix(distances);
            return NO_WAY;
        }
    }

    create_graph("out.dot", "out", *matrix);

    system("dot -Tpng in.dot -o in.png");

    print_result_ways(ways.data, matrix->size, start_place, max_way);

    free_matrix(ways);
    free_matrix(distances);

    return YES_WAY;
}



int build_roads(mat_t *matrix, no_roads_t *chosen_roads, int max_way, int start_place, int emp_num)
{
    for (int i = 0; i < 3 && i < emp_num; i++)
    {
        matrix->data[chosen_roads[i].i][chosen_roads[i].j] = 1;
        matrix->data[chosen_roads[i].j][chosen_roads[i].i] = 1;
    }

    // puts("Дороги добавлены:");

    // print_matrix(*matrix);

    int res = dkstr(matrix, max_way, start_place);

    return res;
}


int find_empty_roads(mat_t matrix, no_roads_t **clear)
{
    no_roads_t *tmp = calloc(matrix.size * matrix.size, sizeof(no_roads_t));

    if (!tmp)
    {
        return ERR_ALLOCATE_MEMORY;
    }

    int ind = 0;

    for (int i = 0; i < matrix.size; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (matrix.data[i][j] == INT_MAX)
            {
                tmp[ind].i = i;
                tmp[ind].j = j;

                ind++;
            }
        }
    }

    // puts("\n\nСвободные дороги:");

    // for (int i = 0; i < ind; i++)
    // {
    //     printf("{из %d в %d} ", tmp[i].i + 1, tmp[i].j + 1);
    // }

    // puts("\n");

    tmp->len = ind;

    *clear = tmp;

    return OK_FIND;
}


int find_ways_combinations(mat_t matrix, no_roads_t *clear, int max_way, int start_place)
{
    int size = matrix.size;

    mat_t tmp_matrix = {.data = NULL, .size = size};

    allocate_matrix(&tmp_matrix);

    for (int i = 0; i < size; i++) // копировать матрицу
    {
        for (int j = 0; j < size; j++)
        {
            tmp_matrix.data[i][j] = matrix.data[i][j];
        }
    }

    if (clear->len < 4) // если путей всего 3
    {
        int res = build_roads(&tmp_matrix, clear, max_way, start_place, clear->len);

        if (res == NO_WAY)
        {
            puts("\nНет возможности построить такой граф\n");
        }

        return res;
    }

    int new_way_index[3] = {0, 1, 2};

    no_roads_t chosen_roads[3];

    chosen_roads->len = 3;

    for (int i = 0; i < 3; i++)
    {
        chosen_roads[i] = clear[new_way_index[i]];
    }

    while (build_roads(&tmp_matrix, chosen_roads, max_way, start_place, clear->len) == NO_WAY)
    {
        new_way_index[2]++;

        if (new_way_index[2] >= clear->len) // перебор троек путей
        {
            new_way_index[1]++;
            new_way_index[2] = new_way_index[1] + 1;
        }

        if (new_way_index[1] >= clear->len)
        {
            new_way_index[0]++;
            new_way_index[1] = new_way_index[0] + 1;
            new_way_index[2] = new_way_index[1] + 1;
        }

        if (new_way_index[2] >= clear->len)
        {
            free_matrix(tmp_matrix);
            puts("\nНет возможности построить такой граф\n");
            return NO_WAY;
        }


        for (int i = 0; i < size; i++) // copy matrix
        {
            for (int j = 0; j < size; j++)
            {
                tmp_matrix.data[i][j] = matrix.data[i][j];
            }
        }

        for (int i = 0; i < 3; i++)
        {
            chosen_roads[i] = clear[new_way_index[i]];
        }

        // Отладочная печать

        // puts("\nВыбранная комбинация: \n");
        
        // for (int i = 0; i < 3; i++)
        // {
        //     printf("%d - {%d <-> %d}, ", new_way_index[i], chosen_roads[i].i + 1, chosen_roads[i].j + 1);
        // }
        
        // puts("\n");
    }


    free_matrix(tmp_matrix);

    return YES_WAY;
}