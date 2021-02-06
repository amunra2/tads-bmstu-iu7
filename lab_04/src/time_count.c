#include"../inc/time_count.h"

void print_time(int64_t start1, int64_t end1, int64_t start2, int64_t end2)
{
    printf("\nСтек массивом: %ld тактов, %.10lf секунд\n\n", end1 - start1, (double)(end1 - start1)/GHZ);
    printf("Стек списком:  %ld тактов, %.10lf секунд\n\n", end2 - start2, (double)(end2 - start2)/GHZ);
}


void create_rand_nums(int *arr, int count)
{
    srand(time(NULL));

    for (int i = 0; i < count; i++)
    {
        int num = rand() % 10;
        arr[i] = num;
    }
}


void time_add(int count)
{
    int64_t start1 = 0, end1 = 0, start2= 0, end2 = 0;

    list_t *stack_list = create_node(33);
    array_t stack_arr = {.arr = NULL, .len = 0};

    int *tmp = malloc(count * sizeof(int));

    if (!tmp)
    {
        return;
    }

    stack_arr.arr = tmp;

    int arr[1000];

    create_rand_nums(arr, count);

    for (int j = 0; j < RUNS; j++)
    {
        start1 += tick();
        for (int i = 0; i < count; i++)
        {
            push_arr(&stack_arr, arr[i]);
        }
        end1 += tick();

        start2 += tick();
        for (int i = 0; i < count; i++)
        {
            push_node(&stack_list, arr[i]);
        }
        end2 += tick();

        for (int i = 0; i < count; i++)
        {
            pop_arr(&stack_arr);
            pop_list(&stack_list);
        }
    }

    puts("\n\nЗамеры добавления элемента");
    print_time(start1 / RUNS, end1 / RUNS, start2 / RUNS, end2 / RUNS);

    free_list(&stack_list);
    free(tmp);
}


void time_del(int count)
{
    int64_t start1 = 0, end1 = 0, start2 = 0, end2 = 0;

    list_t *stack_list = create_node(33);
    array_t stack_arr = {.arr = NULL, .len = 0};

    int *tmp = malloc(count * sizeof(int));

    if (!tmp)
    {
        return;
    }

    stack_arr.arr = tmp;

    int arr[1000];

    create_rand_nums(arr, count);


    for (int j = 0; j < RUNS; j++)
    {
        for (int i = 0; i < count; i++)
        {
            push_arr(&stack_arr, arr[i]);
            push_node(&stack_list, arr[i]);
        }

        start1 += tick();
        for (int i = 0; i < count; i++)
        {
            pop_arr(&stack_arr);
        }
        end1 += tick();

        start2 += tick();
        for (int i = 0; i < count; i++)
        {
            pop_list(&stack_list);
        }
        end2 += tick();
    }


    puts("\n\nЗамеры удаления элемента");
    print_time(start1 / RUNS, end1 / RUNS, start2 / RUNS, end2 / RUNS);

    free_list(&stack_list);
    free(tmp);
}


void time_process(int count)
{
    int64_t start1 = 0, end1 = 0, start2 = 0, end2 = 0;

    int arr[1000];

    create_rand_nums(arr, count);

    exp_t expression;
    int flag = 0;

    for (int i = 0; i < count; i++)
    {
        if (!flag)
        {
            //LOG_DEBUG("num = %d (%c)", arr[i], arr[i] + '0');
            expression.sym[i] = arr[i] + '0';
            flag = 1;
        }
        else
        {
            expression.sym[i] = '+';
            flag = 0;
        }
    }

    expression.sym[count - 1] = '1';
    expression.sym[count] = '\0';

    expression.len = count;

    //printf("\n\nExp %s\n\n", expression.sym);

    //int res_arr, res_list;

    for (int i = 0; i < RUNS; i++)
    {
        start1 += tick();
        calculate_arr(expression);
        end1 += tick();

        start2 += tick();
        calculate_list(expression);
        end2 += tick();
    }

    //LOG_DEBUG("res_arr = %d", res_arr);
    //LOG_DEBUG("res_list = %d", res_list);

    puts("\n\nЗамеры вычисления выражения");
    print_time(start1 / RUNS, end1 / RUNS, start2 / RUNS, end2 / RUNS);
}



void time_counting(void)
{
    puts("\n\nВведите количество элементов в стеках (не менее 1 и не более 1000):");
    int count;

    int rc =scanf("%d", &count);

    if ((rc != 1) || (count < 1) || (count > 1000))
    {
        puts("\n\nОшибка: неверно введено количество элементов в стеках\n\n");
        return;
    }

    printf("\n\nТестирование для %d элементов\
        \n___________________________________________\n", count);

    time_add(count);
    time_del(count);
    time_process(count);


    printf("\n\nЗамеры памяти для %d элементов: \
        \n\nПод массив: %ld байт\
        \nПод список: %ld байт\n\n", count, count * sizeof(int) + sizeof(int*), count * sizeof(list_t));
}