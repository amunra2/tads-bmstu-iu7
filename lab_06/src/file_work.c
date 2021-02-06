#include"../inc/file_work.h"


int file_len(char *filename, int *len)
{
    int size = 0;

    FILE *f = fopen(filename, "r");

    if (!f)
    {
        puts("Ошибка: неверено введено имя файла");
        return ERR_WRONG_FILE_NAME;
    }

    int num;

    int rc;

    while ((rc = fscanf(f, "%d", &num)) != EOF)
    {
        if (rc != 1)
        {
            puts("Ошибка: невереное число в файле");
            return ERR_WRONG_NUM;
        }

        size++;
    }

    *len = size;

    fclose(f);

    return OK_LEN;
}


int read_file(arr_t *arr, char *filename)
{
    printf("\n\nВведите имя файла: ");

    int rc  = scanf("%s", filename);

    if (rc != 1)
    {
        puts("Ошибка: неверено введено имя файла");
        return ERR_WRONG_FILE_NAME;
    }

    int len = 0;
    rc = file_len(filename, &len);

    if (rc != NO_MISTAKES)
    {
        return rc;
    }

    arr->len = len;
    arr->capacity = len * sizeof(int);
    arr->max_cap = arr->capacity * 5;

    arr->data = malloc(arr->max_cap);

    if (!arr->data)
    {
        return ERR_ALLOCATE_MEMORY;
    }

    FILE *f = fopen(filename, "r");

    if (!f)
    {
        puts("Ошибка: неверено введено имя файла");
        free(arr->data);
        return ERR_WRONG_FILE_NAME;
    }

    int num, i = 0;

    while ((rc = fscanf(f, "%d", &num)) != EOF)
    {
        if (rc != 1)
        {
            puts("Ошибка: невереное число в файле");
            return ERR_WRONG_NUM;
        }

        arr->data[i++] = num;
    }

    fclose(f);

    // for (int j = 0; j < arr->len; j++)
    // {
    //     printf("%d ", arr->data[j]);
    // }

    puts("\n\nДанные из файла успешно загружены\n\n");

    puts("\n");

    return OK_READ;
}



// void delete_from_file(char *filename, arr_t *arr)
// {

// }