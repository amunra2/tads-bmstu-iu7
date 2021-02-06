#include"../inc/expression.h"


int check_operation(char sym)
{
   if ((sym == '+') || (sym == '-') || (sym == '*') || (sym == '/'))
   {
       return RIGHT_OPERATION;
   }
   else
   {
       return UNRIGHNT_SYMBOL;
   }
}


int read_num_from_arr_char(char *sym, int *ind)
{
    //printf("@@@ index for translate = %d @@@", *ind);
    char num[150];
    int i = 0;

    while ((sym[*ind] >= '0') && (sym[*ind] <= '9'))
    {
        num[i] = sym[*ind];
        i++;
        *ind += 1;
    }

    num[i] = '\0';

    int number;
    sscanf(num, "%d", &number);

    return number;
}


int translate_operation(char sym)
{
    if (sym == '+')
    {
        return 1;
    }
    else if (sym == '-')
    {
        return 2;
    }
    else if (sym == '*')
    {
        return 3;
    }
    else
    {
        return 4;
    }
}


int check_priority(int sym)
{
    if ((sym == 1) || (sym == 2))
    {
        return 1;
    }

    return 2;
}


int read_expression(exp_t *expression)
{
    // if (expression->len != 0)
    // {
    //     puts("\n\nВыражение уже введено\n\n");
    //     return OK_READ_EXPRESSION;
    // }

    puts("\nВведите выражение в следующем формате без пробелов :\n\nчисло|знак|... число |знак| число \
        \nДоступные операции: + - * /\n\n");

    char sym;
    //char string_exp[150];
    //string_exp[0] = '=';
    int rc, i = 0;

    scanf("%c", &sym);

    while (((rc = scanf("%c", &sym)) == 1) && (sym != '\n'))
    {
        if ((sym > '9') || (sym < '0'))// || (sym != '+') || (sym != '-'))
        {
            if (!check_operation(sym))
            {
                puts("Ошибка: неверный символ в выражении");
                return ERR_WRONG_SYMBOL;
            }
        }

        if (check_operation(sym))
        {
            if ((expression->sym[i - 1] == '+') || (expression->sym[i - 1] == '-'))
            {
                puts("Ошибка: не может быть введено несколько знаков подряд");
                return ERR_WRONG_SYMBOL;    
            }
        }

        expression->sym[i++] = sym;
    }

    //string_exp[0] = '+';
    expression->sym[i] = '\0';
    expression->sym[i] = '\0';

    if (check_operation(expression->sym[0]))
    {
        puts("Ошибка: первым должно быть введено число");
        return ERR_FIRST_SYM_NOT_NUM;
    }

    if (check_operation(expression->sym[i - 1]))
    {
        //printf("\nexpression[strlen(i - 1)] = %c\n", string_exp[i - 1]);
        //printf("\nexpression[strlen(expression)] = %c\n", expression[strlen(expression)]);
        puts("Ошибка: последним должно быть введено число");
        return ERR_LAST_SYM_NOT_NUM;
    }

    printf("\n\nВыражение: %s\n\n", expression->sym);

    //*expression->sym = *string_exp;
    expression->len = i;

    // int num, count = 0;

    // int k = 0, q = 0;

    // char number[100];

    // while(k < i)
    // {
    //     //printf("sym = %c -> ", string_exp[k]);

    //     if ((string_exp[k] == '+') || (string_exp[k] == '-'))
    //     {
    //         if (q != 0)
    //         {
    //             number[q] = '\0';
    //             q = 0;
    //             sscanf(number, "%d", &num);

    //             expression->arr[count++] = num;
    //         }

    //         expression->sym[count] = string_exp[k];
    //     }
    //     else
    //     {
    //         //puts("in num");
    //         number[q++] = string_exp[k];
    //     }
        
    //     k++;
    // }

    // number[q] = '\0';
    // q = 0;
    // sscanf(number, "%d", &num);
    // expression->arr[count] = num;


    //puts("\n\nTransleted");
    // printf("\ncount = %d\n", count);

    // for (int j = 0; j <= count; j++)
    // {
    //     printf("%c   %d\n", expression->sym[j], expression->arr[j]);
    // }

    puts("\n");

    //expression->len = count + 1;

    return OK_READ_EXPRESSION;
}