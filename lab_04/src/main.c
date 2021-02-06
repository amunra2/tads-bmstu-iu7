#include"../inc/main_inc.h"


int main(void)
{
    setbuf(stdin, NULL);
    int option = -1;

    list_t *stack_list = NULL;
    array_t stack_arr = {.arr = NULL, .len = 0};
    int max_len_list = 0, max_len_arr = 0;

    arr_clear_t clear_arr = {.len = 0};

    while (option != 0)
    {
        print_menu();
        
        int rc = scanf("%d", &option);

        if ((rc != 1) || (option < 0) || (option > OPTIONS))
        {
            printf("Ошибка: пункты меню это числа от 0 до %d\n", OPTIONS);
            return ERR_UNRIGHT_OPTION;
        }

        if (option == 0)
        {
            system("clear");
            break;
        }

        if (option == 1)
        {
            rc = create_list(&stack_list, &max_len_list);

            if (rc != NO_MISTAKES)
            {
                LOG_DEBUG("Error, code = %d", rc);
                return rc;
            }

            del_adress(&clear_arr, stack_list);
        }

        if (option == 2)
        {
            if (!add_elem_list(&stack_list, &max_len_list))
            {
                puts("\n\nЭлемент успешно добавлен\n\n");
                del_adress(&clear_arr, stack_list);
            }

            flush_input();
        }

        if (option == 3)
        {
            add_adress(&clear_arr, stack_list);

            if (!pop_list(&stack_list))
            {
                puts("\n\nЭлемент удален\n\n");
            }

            flush_input();
        }

        if (option == 4)
        {
            print_list(stack_list);
            flush_input();
        }

        if (option == 5)
        {
            int result;
            
            if(!result_list(&result))
            {
                printf("\n\nРезультат вычисления выражения: %d\n\n", result);
            }

            //flush_input();
        }

        if (option == 6)
        {
            print_arr_adress(clear_arr);
            flush_input();
        }

        if (option == 7)
        {
            create_arr(&stack_arr, &max_len_arr);

            flush_input();
        }

        if (option == 8)
        {
            if (!add_elem_arr(&stack_arr, &max_len_arr))
            {
                puts("\n\nЭлемент успешно добавлен\n\n");
            }
            flush_input();
        }

        if (option == 9)
        {
            if (!pop_arr(&stack_arr))
            {
                puts("\n\nЭлемент удален\n\n");
            }

            flush_input();
        }

        if (option == 10)
        {
            print_arr(stack_arr);
            flush_input();
        }

        if (option == 11)
        {
            int result;
            
            if(!result_arr(&result))
            {
                printf("\n\nРезультат вычисления выражения: %d\n\n", result);
            }

            //flush_input();
        }

        if (option == 12)
        {
            time_counting();

            flush_input();
        }
    }

    if (stack_list)
    {
        free_list(&stack_list);
    }
    
    return OK;
}