#include<stdint.h>
#include<inttypes.h>

#include"../inc/sorts.h"



void bubble_sort_keys(keys_t *keys, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (keys[j].square > keys[j + 1].square)
            {
                swap_keys(keys, j, j + 1);
            }
        }
    }
}


void bubble_sort_flats(appartment_t *flats_arr, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size- i - 1; j++)
        {
            if (flats_arr[j].square > flats_arr[j + 1].square)
            {
                swap_flats(flats_arr, j, j + 1);
            }
        }
    }
}



void bubble_table(table_t table)
{
    appartment_t *flats_arr = table.flats_arr;

    if (table.size == 0)
    {
        puts("Таблица пустая");
        return;
    }

    bubble_sort_flats(flats_arr, table.size);

    puts("Таблица сортировкой пузырьком успешно отсортирована");

    // table_t table_tmp = {.flats_arr = flats_arr, .size = table.size};

    // print_table(table_tmp);
}


void bubble_table_keys(table_t table)
{
    keys_t *keys = table.keys;

    if (table.size == 0)
    {
        puts("Таблица пустая");
        return;
    }    

    bubble_sort_keys(keys, table.size);

    puts("Таблица ключей сортировкой пузырьком успешно отсортирована");
}


int comparator_table(const void *val1, const void *val2)
{
    return ((appartment_t*)(val1))->square - ((appartment_t*)(val2))->square;
}


void qsort_table(table_t table)
{
    if (table.size == 0)
    {
        puts("Таблица пустая");
        return;
    }
    
    qsort(table.flats_arr, table.size, sizeof(appartment_t), comparator_table);

    puts("Таблица сортировкой qsort успешно отсортирована");
}


int comparator_keys(const void *val1, const void *val2)
{
    return ((keys_t*)(val1))->square - ((keys_t*)(val2))->square;
}


void qsort_table_keys(table_t table)
{   
    if (table.size == 0)
    {
        puts("Таблица пустая");
        return;
    }
    qsort(table.keys, table.size, sizeof(keys_t), comparator_keys);

    puts("Таблица ключей сортировкой qsort успешно отсортирована");
}


uint64_t tick_count(void)
{
    uint32_t high, low;
    __asm__ __volatile__ (
        "rdtsc\n"
        "movl %%edx, %0\n"
        "movl %%eax, %1\n"
        : "=r" (high), "=r" (low)
        :: "%rax", "%rbx", "%rcx", "%rdx"
        );

    uint64_t ticks = ((uint64_t)high << 32) | low;

    return ticks;
}


void print_result(int64_t start, int64_t end)
{
    printf("\n %ld тактов, %.10lf секунд\n\n", end - start, (double)(end - start)/GHZ);
}


short int compare_sorts(FILE *flats_file)
{
    system("clear");
    int64_t start1, end1, start2, end2, start3, end3, start4, end4;

    appartment_t flats_arr[MAX_SIZE];
    int size = 0;
    keys_t keys[MAX_SIZE];

    int rc = 0;

    rc = read_file(flats_file, flats_arr, &size, keys);

    printf("\n\nСортировка файла из %d записей\n\n", size);
    puts("-------------------------------------------------------------------------");

    start1 = tick_count();
    bubble_sort_flats(flats_arr, size);
    end1 = tick_count();

    puts("Сортировка таблицы пузырьком: ");

    print_result(start1, end1);

    puts("-------------------------------------------------------------------------");

    size = 0;

    rc = read_file(flats_file, flats_arr, &size, keys);

    start2 = tick_count();
    bubble_sort_keys(keys, size);
    end2 = tick_count();

    puts("Сортировка таблицы ключей пузырьком: ");

    print_result(start2, end2);

    size = 0;

    puts("-------------------------------------------------------------------------");

    rc = read_file(flats_file, flats_arr, &size, keys);

    

    start3 = tick_count();
    qsort(flats_arr, size, sizeof(appartment_t), comparator_table);
    end3 = tick_count();

    puts("Сортировка таблицы qsort: ");

    print_result(start3, end3);

    size = 0;

    puts("-------------------------------------------------------------------------");

    rc = read_file(flats_file, flats_arr, &size, keys);

    start4 = tick_count();
    qsort(keys, size, sizeof(keys_t), comparator_table);
    end4 = tick_count();

    puts("Сортировка таблицы ключей qsort: ");

    print_result(start4, end4);


    printf("\n%lu размер массива ключей (в байтах)", sizeof(*keys) * size);
    printf("\n%lu размер таблицы (в байтах)\n\n", sizeof(*flats_arr) * size);

    return rc;
}
