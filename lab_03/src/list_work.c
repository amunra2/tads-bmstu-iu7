#include"../inc/list_work.h"


int read_list(list_t *list, int no_zeroes)
{
    int num, pos;

    while (no_zeroes-- > 0)
    {
        puts("\nВведите элемент вектора столбца:");

        if (scanf("%d", &num) != 1)
        {
            puts("Ошибка: элемент вектора введён неверно");
            return ERR_UNRIGNT_ELEM;
        }

        puts("Введите позицию элемента в векторе столбце (нумерация с 0):");

        if ((scanf("%d", &pos) != 1) || (pos < 0) || (pos > list->len))
        {
            puts("Ошибка: позиция элемента вектора введена неверно");
            return ERR_UNRIGNT_POS;
        }

        list->arr[pos] = num;
    }

    return OK_READ;
}


void random_list(list_t *list, int no_zeroes)
{
    srand(time(NULL));

    int pos;

    while (no_zeroes-- > 0)
    {
        pos = 0;

        do
        {
            pos = rand() % list->len;
        } while (list->arr[pos] != 0);

        list->arr[pos] = rand() % 100 + 1;
    }
}
