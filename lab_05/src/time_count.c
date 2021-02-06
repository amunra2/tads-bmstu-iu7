#include"../inc/time_count.h"

void print_time(int64_t start1, int64_t end1, int64_t start2, int64_t end2)
{
    printf("\nОчередь массивом: %ld тактов, %.10lf секунд\n\n", end1 - start1, (double)(end1 - start1)/GHZ);
    printf("Очередь списком:  %ld тактов, %.10lf секунд\n\n", end2 - start2, (double)(end2 - start2)/GHZ);
}


int create_rand_num(void)
{
    srand(time(NULL));

    return rand() % 100 + 1;
}


void time_add(int count)
{
    int64_t start1 = 0, end1 = 0, start2= 0, end2 = 0;

    arr_t queue_arr;
    init_arr_queue(&queue_arr);

    list_t queue_list;
    init_list_queue(&queue_list);

    int num;

    for (int j = 0; j < RUNS; j++)
    {
        num = create_rand_num();

        start1 += tick();
        for (int i = 0; i < count; i++)
        {
            push_arr_queue(&queue_arr, num);
        }
        end1 += tick();

        start2 += tick();
        for (int i = 0; i < count; i++)
        {
            push_list_queue(&queue_list, num);
        }
        end2 += tick();

        for (int i = 0; i < count; i++)
        {
            pop_arr_queue(&queue_arr);
            pop_list_queue(&queue_list);
        }
    }

    puts("\n\nЗамеры добавления элемента");
    print_time(start1 / RUNS, end1 / RUNS, start2 / RUNS, end2 / RUNS);
}


void time_del(int count)
{
    int64_t start1 = 0, end1 = 0, start2 = 0, end2 = 0;

    arr_t queue_arr;
    init_arr_queue(&queue_arr);

    list_t queue_list;
    init_list_queue(&queue_list);

    int num;

    for (int j = 0; j < RUNS; j++)
    {

        for (int i = 0; i < count; i++)
        {
            num = create_rand_num();
            push_arr_queue(&queue_arr, num);
            push_list_queue(&queue_list, num);
        }

        start1 += tick();
        for (int i = 0; i < count; i++)
        {
            pop_arr_queue(&queue_arr);
        }
        end1 += tick();

        start2 += tick();
        for (int i = 0; i < count; i++)
        {
            pop_list_queue(&queue_list);
        }
        end2 += tick();
    }


    puts("\n\nЗамеры удаления элемента");
    print_time(start1 / RUNS, end1 / RUNS, start2 / RUNS, end2 / RUNS);
}





void time_counting(void)
{
    puts("\n\nВведите количество элементов (не менее 1 и не более 1000):");
    int count;

    int rc =scanf("%d", &count);

    if ((rc != 1) || (count < 1) || (count > 1000))
    {
        puts("\n\nОшибка: неверно введено количество элементов\n\n");
        return;
    }

    printf("\n\nТестирование для %d элементов\
        \n___________________________________________\n", count);

    time_add(count);
    time_del(count);

    printf("\n\nЗамеры памяти для %d элементов: \
        \n\nПод массив: %ld байт\
        \nПод список: %ld байт\n\n", count, (count + 2) * sizeof(int), count * sizeof(node_t));
}