#include"../inc/hash.h"


int key_hash(int num, int size)
{
    return abs(num) % size;
}


int find_next_empty_ind(hash_t *hash_table, int ind, int *count)
{
    for (int i = ind; i < hash_table->size; i++)
    {
        (*count)++;

        if (hash_table->key[i] == 0)
        {
            return i;
        }
    }

    for (int i = 0; i < ind; i++)
    {
        (*count)++;

        if (hash_table->key[i] == 0)
        {
            return i;
        }
    }

    printf("!!!!!!!!! -1 !!!!!!!!!");

    return -1;
}


int add_hash(hash_t *hash_table, int data, int *count)
{
    int ind = key_hash(data, hash_table->size);

    if (hash_table->key[ind] == 0)
    {
        hash_table->data[ind] = data;
        hash_table->key[ind] = 1;

        *count = 1;
    }
    else
    {
        ind = find_next_empty_ind(hash_table, ind, count);

        if (ind == -1)
        {
            return ERR_OWERFLOW_TABLE;
        }

        hash_table->data[ind] = data;
        hash_table->key[ind] = 2;
    }    

    return OK_HASH;
}


int fill_hash_table(hash_t *hash_table, arr_t *arr, int size)
{
    hash_table->size = size;//arr->len;

    hash_table->data = malloc(hash_table->size * sizeof(int));
    hash_table->key = calloc(hash_table->size, sizeof(int));

    if (!hash_table->data && !hash_table->key)
    {
        return ERR_ALLOCATE_MEMORY;
    }

    for (int i = 0; i < arr->len; i++)
    {
        int count = 1;
        int rc = add_hash(hash_table, arr->data[i], &count);

        if (rc)
        {
            return ERR_OWERFLOW_TABLE;
        }
    }

    return OK_HASH;
}


int check_prime(int num)
{
    for (int i = 2; i < num; i++)
    {
        if (num % i == 0)
        {
            return 0;
        }
    }

    return 1;
}


int near_prime(int num)
{
    while (1)
    {
        num++;

        if (check_prime(num))
        {
            return num;
        }
    }
}


void print_hash_table(hash_t hash_table)
{
    if (!hash_table.data)
    {
        return;
    }

    for (int i = 0; i < hash_table.size; i++)
    {
        if (hash_table.key[i] == 1)
        {
            printf("%3d.  { %3d }\n", i, hash_table.data[i]);
        }
        else if (hash_table.key[i] == 2)
        {
            printf("%3d.  { %3d }   K\n", i, hash_table.data[i]);
        }
        else
        {
            printf("%3d. NULL \n", i);
        }
    }
}