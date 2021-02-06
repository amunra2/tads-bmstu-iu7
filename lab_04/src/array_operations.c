#include"../inc/array_operations.h"


void push_arr(array_t *array, int num)
{
    *(array->arr++) = num;
    array->len++;
}


int top_arr(array_t array)
{
    return *(array.arr - 1);
}


int create_arr(array_t *array, int *max_len)
{
    if (*max_len == 0)
    {
        puts("\n\nВведите максимально возможный размер стека (не меньше 1 и не более 10000):\n");
        
        int rc = scanf("%d", max_len);

        if ((rc != 1) || (*max_len < 0) || (*max_len > 10000))
        {
            puts("Ошибка: размер стека это число, не меньшее 1 и не большее 10000");
            return ERR_UNRIGHT_ARR_MAX_LEN_ARR;
        }

        int *tmp = malloc(*max_len * sizeof(int));

        if (!tmp)
        {
            return ERR_ALLOCATE_MEMORY_ARR;
        }

        array->arr = tmp;
    }

    puts("\nСколько элементов в стек Вы хотите ввести:\n");
    int cur_len = 0;

    if ((scanf("%d", &cur_len) != 1) || (cur_len < 1) || (array->len + cur_len > *max_len))
    {
        puts("\n\nОшибка: неверно введено количество элементов в стеке\n\n");
        return ERR_UNRIGHNT_CUR_SIZE;
    }

    // if (array->len != 0)
    // {
    //     puts("\nСтек уже создан\n");
    //     return STACK_READY;
    // }

    int num;

    puts("\nВведите элементы по одному:");

    for (int i = 0; i < cur_len; i++)
    {
        if (scanf("%d", &num) == 1)
        {
            push_arr(array, num);
        }
        else
        {
            puts("\nОшибка: крайний элемент был введен неверно, повторите попытку\n");
            flush_input();
            i--;
        }
    }

    puts("\n\nСтек массивом успешно создан\n\n");

    printf("\n\ntop arr = %d\n\n", top_arr(*array));

    return OK_CREATE;
}



int print_arr(array_t array)
{
    puts("");
    if (array.len == 0)
    {
        printf("\n\nСтек пуст\n\n");
        return STACK_IS_CLEAR;
    }

    //printf("\n\ntop arr = %d\n\n", top_arr(array));

    int *tmp = array.arr;// - 1;
    int len = array.len;

    while (len > 0)
    {
        printf("%d\n", *(--tmp));
        
        len--;
    }

    //printf("\n\ntop arr = %d\n\n", top_arr(array));

    puts("");

    return OK_PRINT;
}


int pop_arr(array_t *array)
{
    if (array->len == 0)
    {
        puts("\nСтек пуст\n");
        return STACK_IS_CLEAR;
    }

    array->arr--;
    array->len--;

    return OK_DEL;
}


int add_elem_arr(array_t *array, int *max_len)
{
    if (*max_len == 0)
    {
        puts("\nВведите максимально возможный размер стека (не меньше 1 и не больше 10000):");
        
        int rc = scanf("%d", max_len);

        if ((rc != 1) || (*max_len < 0) || (*max_len > 10000))
        {
            puts("\n\nОшибка: размер стека это число, не меньшее 0 и не большее 10000\n\n");
            return ERR_UNRIGHT_ARR_MAX_LEN_ARR;
        }

        int *tmp = malloc(*max_len * sizeof(int));

        if (!tmp)
        {
            return ERR_ALLOCATE_MEMORY_ARR;
        }

        array->arr = tmp;
    }

    if (array->len + 1 > *max_len)
    {
        puts("\n\nОшибка: стек переполнен\n\n");
        return ERR_OWERFLOW_STACK_ARR;
    }

    puts("\n\nВведите число:\n");
    int num;

    int rc = scanf("%d", &num);

    if (rc != 1)
    {
        puts("\n\nОшибка: неверно введен элемент для добавления\n\n");
        return ERR_UNRIGHT_ELEM_ARR;
    }

    //Add to array

    push_arr(array, num);

    return OK_ADD;
}


int check_clear_stack(array_t stack)
{
    //printf("$$$ len = %d $$$", stack.len);
    return (stack.len == 0) ? CLEAR : INITED;
}


void count_operation(array_t *num_stack, array_t *sign_stack)
{
    int num1 = top_arr(*num_stack);
    pop_arr(num_stack);
    
    int num2 = top_arr(*num_stack);
    pop_arr(num_stack);

    int sign_op = top_arr(*sign_stack);
    pop_arr(sign_stack);

    int result;

    if (sign_op == 1)
    {
        result = num2 + num1;
    }
    else if (sign_op == 2)
    {
        result = num2 - num1;
    }
    else if (sign_op == 3)
    {
        result = num2 * num1;
    }
    else if (sign_op == 4)
    {
        result = (int)(num2 / num1);
    }

    //printf("\n\nCOUNT: %d (%d) %d = %d\n\n", num1, sign_op, num2, result);

    push_arr(num_stack, result);

    //print_arr(*num_stack);
}


int calculate_arr(exp_t exp)
{
    array_t num_stack = {.len = 0};
    array_t sym_stack = {.len = 0}; // + = 1, - = 2, * = 3, / = 4

    // Allocate mem for num_stack

    int *tmp = malloc(exp.len * sizeof(int));

    if (!tmp)
    {
        return ERR_ALLOCATE_MEMORY_ARR;
    }

    num_stack.arr = tmp;

    // Allocate mem for sym_stack

    tmp = malloc(exp.len * sizeof(int));

    if (!tmp)
    {
        return ERR_ALLOCATE_MEMORY_ARR;
    }

    sym_stack.arr = tmp;
    
    for (int i = 0; i < exp.len; i++)
    {
        //printf("\ncur sym[%d] = %c\n", i, exp.sym[i]);

        if (check_operation(exp.sym[i])) // if sign
        {
            //printf("\n###in sign parse###\n");
            int sign = translate_operation(exp.sym[i]);

            if (!check_clear_stack(sym_stack)) // if stack clear
            {
                //puts("\n&&& stack clear -> push sign &&&\n");
                push_arr(&sym_stack, sign);
            }
            else // if stack is not clear
            {
                //puts("\n&&& stack not clear -> count &&&\n");
                int level_cur = check_priority(sign);
                int level_prev = check_priority(top_arr(sym_stack));

                if (level_cur > level_prev) // if priority is higher
                {
                    LOG_DEBUG("PUSH IT: c = %d, p = %d", level_cur, level_prev);
                    push_arr(&sym_stack, sign); // push in stack
                }
                else if (level_cur <= level_prev)// if priority is equal or lower
                {
                    count_operation(&num_stack, &sym_stack); // take 2 nums from stack and prev sign -> result in num_stack
                    i--;
                }
            }
        } // end sign parse
        else
        {
            //printf("\n###in num parse###\n");
            int num = read_num_from_arr_char(exp.sym, &i); // get num from stack
            i -= 1;

            //printf("\nnum = %d\n", num);
            push_arr(&num_stack, num);

            if (i + 1 == exp.len)
            {
                while (check_clear_stack(sym_stack)) // if operations are left after loop
                {
                    count_operation(&num_stack, &sym_stack);
                }
            }
        } // end num parse

        // puts("Stack nums now");
        // print_arr(num_stack);


        // puts("Stack sign now");
        // print_arr(sym_stack);

        //puts("");
    }

    //free(num_stack.arr);
    //free(sym_stack.arr);

    return top_arr(num_stack);
}


int result_arr(int *res)
{
    exp_t exp;
    
    int rc = read_expression(&exp); // read expression in char array

    if (rc != NO_MISTAKES)
    {
        return rc;
    }  
    
    *res = calculate_arr(exp);
 
    return OK_COUNT;
}