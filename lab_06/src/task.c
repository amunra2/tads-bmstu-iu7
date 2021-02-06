#include"../inc/task.h"

void print_result(int64_t time, int mem, int comp)
{
    printf("Время для добавления (в тиках): %ld", time);
    printf("\nПамяти зайдествовано: %d", mem);
    printf("\nСравнений для вставки: %d\n\n\n", comp);
}

int add_elem_file(arr_t *arr, char *filename, int num)
{
    arr->capacity += sizeof(int);

    if (arr->capacity >= arr->max_cap) // если памяти не хватает
    {
        arr->max_cap *= 2;

        int *tmp = realloc(arr->data, arr->max_cap);

        if (!tmp)
        {
            return ERR_ALLOCATE_MEMORY;
        }

        arr->data = tmp;
    }

    int count = 0;
    int64_t start = 0, end = 0;
    FILE *f;

    while (count++ < RUNS)
    {
        f = fopen(filename, "w");

        for (int i = 0; i < arr->len; i++)
        {
            fprintf(f, "%d ", arr->data[i]);
        }

        fclose(f);

        start += tick();

        f = fopen(filename, "a");

        fprintf(f, "%d ", num);

        end += tick();

        fclose(f);
    }

    f = fopen(filename, "r");

    fseek(f, 0, SEEK_END);

    int size = ftell(f);

    fclose(f);

    arr->data[arr->len] = num; // массив
    arr->len += 1;

    puts("\n\nЗамеры для файла\n");
    print_result((end - start) / RUNS, size, arr->len);

    return OK_ADD;
}


int add_elem_ddp(node_t **ddp, arr_t *arr, int num)
{
    int comp = 0;
    int height = -1;

    int64_t start = 0, end = 0;

    start = tick();
    *ddp = add_ddp(*ddp, num, &height, &comp);
    end = tick();

    int size = arr->len * sizeof(node_t);

    puts("\n\nЗамеры для ДДП\n");
    print_result((end - start), size, comp);

    return OK_ADD;
}


int add_elem_avl(node_t **avl, arr_t *arr, int num)
{
    int comp = 0;
    int height = -1;

    int64_t start = 0, end = 0;

    start = tick();
    *avl = add_avl(*avl, num, &height, &comp);
    end = tick();

    int size = arr->len * sizeof(node_t);

    puts("\n\nЗамеры для АВЛ\n");
    print_result((end - start), size, comp);

    return OK_ADD;
}


int add_hash_elem(hash_t *hash_table, arr_t *arr, int num)
{
    if (hash_table->size == arr->len)
    {
        free(hash_table->data);
        free(hash_table->key);
        fill_hash_table(hash_table, arr, near_prime(hash_table->size * 2));

        puts("\n\nРеструктаризация ХЕШ таблицы произведена по причине ее переполнения\n\n");
    }
    printf("\n\nВведите резрешенное количество сравнений для ХЕШ таблицы:  ");

    int comparsions;
    int rc = scanf("%d", &comparsions);

    if ((rc != 1) || (comparsions < 1)) 
    {
        puts("\n\nОшибка: неверно введено количество сравнений\n");
        return ERR_WRONG_NUM;
    }

    int comp_hash = 0;

    add_hash(hash_table, num, &comp_hash);

    printf("\n\nСравнений для добавления в ХЕШ таблицу: %d\n\n", comp_hash);

    while (comparsions <= comp_hash)
    {
        free(hash_table->data);
        free(hash_table->key);
        fill_hash_table(hash_table, arr, near_prime(hash_table->size * 2));

        puts("\n\nРеструктаризация ХЕШ таблицы произведена по причине большого количества сравнений\n\n");

        comp_hash = 0;

        add_hash(hash_table, num, &comp_hash);
        printf("\n\nСравнений для добавления в новую таблицу: %d\n\n", comp_hash);
    }


    // Time

    hash_t tmp = {.data = NULL, .key = NULL, .size = 0};
    
    fill_hash_table(&tmp, arr, near_prime(hash_table->size * 10));

    int64_t start = 0, end = 0;
    int cmp = 0;

    start = tick();
    add_hash(&tmp, num, &cmp);
    end = tick();

    int size = hash_table->size * 2 * sizeof(int) + sizeof(int);

    puts("\n\nЗамеры для ХЕШ таблицы\n");
    print_result((end - start), size, comp_hash);

    free(tmp.data);
    free(tmp.key);

    return OK_ADD;
}


int add_all(node_t **avl, node_t **ddp, arr_t *arr, hash_t *hash_table, char *filename)
{
    printf("\n\nВведите элемент для добавления:  ");

    int num;
    int rc = scanf("%d", &num);

    if (rc != 1)
    {
        puts("\n\nОшибка: неверно введено число для добавления\n");
        return ERR_WRONG_NUM;
    }

    for (int i = 0; i < arr->len; i++)
    {
        if (arr->data[i] == num)
        {
            puts("\n\nОшибка: такое число уже существует\n");
            return ERR_NUM_REPEAT;
        }
    }

    add_hash_elem(hash_table, arr, num);

    add_elem_file(arr, filename, num);

    add_elem_ddp(ddp, arr, num);

    add_elem_avl(avl, arr, num);

    return 0;
}