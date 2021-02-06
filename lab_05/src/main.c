#include "../inc/main_inc.h"


int get_random_num(void)
{
    srand(time(NULL));
    return rand() % 100 + 1;
}


int main(void)
{
    int option = -1;

    int rc = 0;

    arr_t queue_arr;
    init_arr_queue(&queue_arr);

    list_t queue_list;
    init_list_queue(&queue_list);

    arr_clear_t clear_arr = {.len = 0};

    while (option != 0)
    {
        print_menu();

        rc = scanf("%d", &option);

        if ((rc != 1) || (option < 0) || (option > 10))
        {
            puts("\n\nОшибка: пункты меню это числа от 0 до 10");
            return ERR_UNRIGHT_OPTION;
        }

        if (option == 1)
        {
            int num = get_random_num();

            if (!owerflow_arr_queue(queue_arr))
            {
                push_arr_queue(&queue_arr, num);
            }
            else
            {
                printf("\n\nОшибка: очередь переполнена\n\n");
            }
        }
        
        if (option == 2)
        {
            if (!clear_check_arr_queue(queue_arr))
            {
                pop_arr_queue(&queue_arr);
            }
            else
            {
                printf("\n\nОчередь пустая\n\n");
            }
            
        }

        if (option == 3)
        {
            print_arr_queue(queue_arr);
        }

        if (option == 4)
        {
            int num = get_random_num();
            push_list_queue(&queue_list, num);
            del_adress(&clear_arr, &queue_list);
        }
        
        if (option == 5)
        {
            if (!clear_check_list(queue_list))
            {
                add_adress(&clear_arr, &queue_list);
                pop_list_queue(&queue_list);
            }
            else
            {
                printf("\n\nОчередь пустая\n\n");
            }
        }

        if (option == 6)
        {
            print_list_queue(queue_list);
        }

        if (option == 7)
        {
            print_arr_adress(clear_arr);
        }

        if (option == 8)
        {
            task_arr();
        }

        if (option == 9)
        {
            task_list();
        }

        if (option == 10)
        {
            time_counting();
        }
    }

    //free_list(&queue_list);
}