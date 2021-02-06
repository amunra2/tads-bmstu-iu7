#include"../inc/main_inc.h"


int main(void)
{
    int option = -1;
    arr_t arr = {.data = NULL, .len = 0, .capacity = 0, .max_cap = 0};
    node_t *ddp = NULL;
    node_t *avl = NULL;
    hash_t hash_table = {.data = NULL, .key = NULL, .size = 0};
    char filename[250];

    while (option != 0)
    {
        print_menu();

        int rc = scanf("%d", &option);

        if (rc != 1)
        {
            puts("Ошибка: неверно введен пункт меню, повторите попытку");
            flush_input();
            continue;
        }


        flush_input();

        if (option == 1)
        {
            rc = read_file(&arr, filename);

            if (rc != NO_MISTAKES)
            {
                continue;
            }

            fill_ddp(&ddp, arr);
            fill_avl(&avl, arr);
            fill_hash_table(&hash_table, &arr, near_prime(arr.len));
        }

        if (option == 2)
        {
            print_tree(ddp, 0);
        }

        if (option == 3)
        {
            print_tree(avl, 0);
        }

        if (option == 4)
        {
            print_hash_table(hash_table);
        }

        if (option == 5)
        {
            add_all(&avl, &ddp, &arr, &hash_table, filename);
        }
    }

    free_tree(ddp);
    free_tree(avl);

    free(hash_table.data);
    free(hash_table.key);
    free(arr.data);

    return OK;
}