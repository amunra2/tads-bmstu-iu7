#include<stdio.h>
#include<stdlib.h>
#include"../inc/print_info.h"


void print_string(appartment_t flat)
{
    printf("%-20s | %7d | %6d | %6d |  %5d | ", flat.address, flat.square, flat.rooms, flat.one_m_cost, flat.is_primary);

    if (flat.is_primary == 1)
    {
        if (flat.flat.primary.decorated == 1)
        {
            printf("   Да   |   --   |     --    |   --   |     --   \n");
        }
        else if (flat.flat.primary.decorated == 0)
        {
            printf("   Нет  |   --   |     --    |   --   |     --   \n");
        }
    }
    else if (flat.is_primary == 2)
    {
        printf("   --   | %6d | %9d | %6d |", flat.flat.secondary.build_year, flat.flat.secondary.previous_owners, flat.flat.secondary.previous_rezidents);

        if (flat.flat.secondary.animals == 1)
        {
            puts("    Да   ");
        }
        else if (flat.flat.secondary.animals == 0)
        {
            puts("    Нет   ");
        }
    }
}


void print_table(table_t table)
{
    system("clear"); 

    int size = table.size;

    if (table.size == 0)
    {
        puts("Таблица пустая");
        return;
    }

    appartment_t *flats_arr = table.flats_arr;

    puts("    Адресс (город)   | Площадь | Комнат |  Цена  |  Класс | Отделка |  Год   | Владельцы | Жильцы | Животные");

    puts("--------------------------------------------------------------------------------------------------------------");

    for (int flat_num = 0; flat_num < size; flat_num++)
    {
        print_string(flats_arr[flat_num]);
    }
}


void print_table_keys(table_t table)
{
    system("clear"); 

    int size = table.size;

    if (table.size == 0)
    {
        puts("Таблица пустая");
        return;
    }

    keys_t *keys = table.keys;

    puts("    Таблица ключей");

    for (int key = 0; key < size; key++)
    {
        printf("Номер: %3d  | Площадь: %9d  \n", keys[key].id, keys[key].square);
    }
}

 

void print_table_by_keys(table_t table)
{
    system("clear");
    
    if (table.size == 0)
    {
        puts("Таблица пустая");
        return;
    }

    puts("    Адресс (город)   | Площадь | Комнат |  Цена  |  Класс | Отделка |  Год   | Владельцы | Жильцы | Животные");

    puts("--------------------------------------------------------------------------------------------------------------");
    for (int flat = 0; flat < table.size; flat++)
    {
        print_string(table.flats_arr[table.keys[flat].id]);
    }
}


short int search(table_t table)
{
    system("clear");

    if (table.size == 0)
    {
        puts("Таблица пустая");
        return OK_SEARCH;
    }

    int cost_start, cost_end;

    puts("Введите нижнюю границу цены (не меньше 1):");
    int rc = scanf("%d", &cost_start);

    if ((rc != 1) || (cost_start < 1))
    {
        puts("Ошибка: неверно введена начальная граница");
        return ERR_UNRIGHT_START_PRICE;
    }

    puts("\n\nВведите верхнюю границу цены:");
    rc = scanf("%d", &cost_end);

    if ((rc != 1) || (cost_end < 1))
    {
        puts("Ошибка: неверно введена конечная цена");
        return ERR_UNRIGHT_END_PRICE;
    }

    if (cost_start > cost_end)
    {
        puts("Ошибка: конечная цена не может быть меньше начальной");
        return ERR_START_CANNOT_BE_BIGGER_THEN_END_PRICE;
    }

    int check = 0;

    for (int flat = 0; flat < table.size; flat++)
    {
        if ((table.flats_arr[flat].rooms == 2) && (table.flats_arr[flat].is_primary == 2) && (table.flats_arr[flat].flat.secondary.animals == 1) && (table.flats_arr[flat].one_m_cost >= cost_start) && (table.flats_arr[flat].one_m_cost <= cost_end))
        {
            if (check == 0)
            {
                puts("\n\n    Адресс (город)   | Площадь | Комнат |  Цена  |  Класс | Отделка |  Год   | Владельцы | Жильцы | Животные");

                puts("--------------------------------------------------------------------------------------------------------------");
            }

            print_string(table.flats_arr[table.keys[flat].id]);

            check = 1;
        }
    }

    if (check == 0)
    {
        puts("\n\nНичего не было найдено по заданным границам цены");
    }


    return OK_SEARCH;
}
