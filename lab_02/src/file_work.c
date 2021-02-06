#include<stdio.h>
#include<stdlib.h>
#include"../inc/struct.h"
#include"../inc/print_info.h"
#include"../inc/file_work.h"


int check_clear(FILE *f)
{
    if (fseek(f, 0, SEEK_END) != 0)
    {
        return ERR_FILE_CLEAR;
    }

    size_t current_size = ftell(f);

    if (current_size <= 0)
    {
        return ERR_FILE_CLEAR;
    }

    return fseek(f, 0, SEEK_SET);
}


short int read_file(FILE *flats_file, appartment_t *flats_arr, int *size, keys_t *keys)
{
    int num_flat = *size;
    int rc = 0;

    if (check_clear(flats_file) != 0)
    {
        puts("Ошибка: файл пустой");
        return ERR_FILE_CLEAR;
    }

    while (!feof(flats_file))
    {
        // Adress square rooms cost primary -> 1-decor 2 time owners citizens animals
        rc = fscanf(flats_file, "%100s %d %d %d %d", flats_arr[num_flat].address, &flats_arr[num_flat].square, &flats_arr[num_flat].rooms, &flats_arr[num_flat].one_m_cost, &flats_arr[num_flat].is_primary);

        keys[num_flat].square = flats_arr[num_flat].square;
        keys[num_flat].id = num_flat;

        if (rc != 5)
        {
            puts("Ошибка: неверные элементы в файле");
            return ERR_UNRIGHT_ELEMENTS;
        }

        if (flats_arr[num_flat].is_primary == 1)
        {
            primary_t type;
            rc = fscanf(flats_file, "%d", &type.decorated);

            if (rc != 1)
            {
                puts("Ошибка: неверные элементы в файле");
                return ERR_UNRIGHT_ELEMENTS;
            }

            flats_arr[num_flat].flat.primary = type;
        }
        else if (flats_arr[num_flat].is_primary == 2)
        {
            not_primary_t type;

            rc = fscanf(flats_file, "%d %d %d %d", &type.build_year, &type.previous_owners, &type.previous_rezidents, &type.animals);

            if (rc != 4)
            {
                printf("Ошибка: неверные элементы в файле");
                return ERR_UNRIGHT_ELEMENTS;
            }

            flats_arr[num_flat].flat.secondary = type;
        }
        num_flat++;

        if (num_flat > MAX_SIZE)
        {
            puts("Ошибка: количество записей переполнено");
            return ERR_TOO_MUCH_FLATS;
        }
    }

    fseek(flats_file, 0, SEEK_SET);

    *size = num_flat;

    return OK_FILE;
}


short int add_flat(appartment_t *flats_arr, int *size, keys_t *keys)
{
    appartment_t new_flat;
    system("clear"); 

    // Adress square rooms cost primary -> 1-decor 2 time owners citizens animals

    puts("\nВведите город (одно слово без пробелов):");
    if (scanf("%s", new_flat.address) != 1)
    {
        puts("Ошибка: неверно введён город");
        return ERR_UNRIGHT_CITY_INPUT;
    }

    puts("\nВведите площадь квартиры (от 1 до 100000):");
    if ((scanf("%d", &new_flat.square) != 1) || (new_flat.square < 1) || (new_flat.square > 100000))
    {
        puts("Ошибка: неверно введена площадь квартиры");
        return ERR_UNRIGHT_SQUARE_INPUT;
    }

    puts("\nВведите количество комнат (от 1 до 100):");
    if ((scanf("%d", &new_flat.rooms) != 1) || (new_flat.rooms < 1) || (new_flat.rooms > 100))
    {
        puts("Ошибка: неверно введено количество комнат");
        return ERR_UNRIGHT_ROOMS_INPUT;
    }

    puts("\nВведите цену за один квадратный метр квартиры (от 1 до 1000000):");
    if ((scanf("%d", &new_flat.one_m_cost) != 1) || (new_flat.one_m_cost < 1) || (new_flat.one_m_cost > 1000000))
    {
        puts("Ошибка: неверно введена цена за 1 квадртатный метр");
        return ERR_UNRIGHT_COST_INPUT;
    }

    puts("\nВведите класс квартиры: 1 - первичная, 2 - вторичная:");
    if ((scanf("%d", &new_flat.is_primary) != 1) || (new_flat.is_primary < 1) || (new_flat.is_primary > 2))
    {
        puts("Ошибка: неверно введен класс квартиры");
        return ERR_UNRIGHT_PRIMARY_INPUT;
    }

    if (new_flat.is_primary == 1)
    {
        puts("\nЕсть ли декор? (1 - да, 0 - нет):");
        if ((scanf("%d", &new_flat.flat.primary.decorated) != 1) || (new_flat.flat.primary.decorated < 0) || (new_flat.flat.primary.decorated > 1))
        {
            puts("Ошибка: неверно введено наличие декора");
            return ERR_UNRIGHT_DECOR_INPUT;
        }
    }
    else if (new_flat.is_primary == 2)
    {
        puts("\nВведите год постройки (от 1900 до 2020):");
        if ((scanf("%d", &new_flat.flat.secondary.build_year) != 1) || (new_flat.flat.secondary.build_year < 1900) || (new_flat.flat.secondary.build_year > 2020))
        {
            puts("Ошибка: неверно введён год постройки");
            return ERR_UNRIGHT_YEAR_INPUT;
        }

        puts("\nВведите количество прошлых владельцев (от 1 до 1000):");
        if ((scanf("%d", &new_flat.flat.secondary.previous_owners) != 1) || (new_flat.flat.secondary.previous_owners < 1) || (new_flat.flat.secondary.previous_owners > 1000))
        {
            puts("Ошибка: неверно введено количество прошлых владельцев");
            return ERR_UNRIGHT_OWNER_INPUT;
        }

        puts("\nВведите количество прошлых жильцов (от 1 до 1000):");
        if ((scanf("%d", &new_flat.flat.secondary.previous_rezidents) != 1) || (new_flat.flat.secondary.previous_rezidents < 1) || (new_flat.flat.secondary.previous_rezidents > 1000))
        {
            puts("Ошибка: неверно введено количество прошлых жильцов");
            return ERR_UNRIGHT_RESIDENT_INPUT;
        }

        puts("\nБыли ли животные в квартире? (1 - да, 0 - нет):");
        if ((scanf("%d", &new_flat.flat.secondary.animals) != 1) || (new_flat.flat.secondary.animals < 0) || (new_flat.flat.secondary.animals > 1))
        {
            puts("Ошибка: неверно введено наличие животного");
            return ERR_UNRIGHT_ANIMAL_INPUT;
        }
    }

    *size += 1;

    if (*size > MAX_SIZE)
    {
        puts("Ошибка: количество записей переполнено");
        return ERR_TOO_MUCH_FLATS;
    }

    keys[*size - 1].square = new_flat.square;
    keys[*size - 1].id = *size - 1;

    flats_arr[*size - 1] = new_flat;

    puts("\nКвартира была успешно добавлена\n");
    return OK_ADDING;
}


void swap_flats(appartment_t *flats_arr, int i, int j)
{
    appartment_t tmp;

    tmp = flats_arr[i];
    flats_arr[i] = flats_arr[j];
    flats_arr[j] = tmp;
}


void swap_keys(keys_t *keys, int i, int j)
{
    keys_t tmp;

    tmp = keys[i];
    keys[i] = keys[j];
    keys[j] = tmp;
}


void del_by_pos(appartment_t *flats_arr, keys_t *keys, int size, int flat)
{
    for (int i = flat; i < size; i++)
    {
        swap_flats(flats_arr, i, i + 1);
    }

    for (int i = flat; i < size; i++)
    {
        swap_keys(keys, i, i + 1);
        keys[i].id -= 1;
    }
}


short int delete_by_square(appartment_t *flats_arr, int *size, keys_t *keys)
{
    system("clear");

    if (*size == 0)
    {
        puts("\nТаблица пустая\n");
        return OK_DEL;
    }
    puts("Введите значение площади, по которому будут удалены квартиры с такой площадью:");

    int square_del;
    int rc = scanf("%d", &square_del);
    int size_arr = *size;

    if ((rc != 1) || (square_del < 1))
    {
        puts("Ошибка: неверно введена площадь");
        return ERR_UNRIGHT_SQUARE_INPUT;
    }

    for (int flat = 0; flat < size_arr; flat++)
    {
        if (flats_arr[flat].square == square_del)
        {
            del_by_pos(flats_arr, keys, *size, flat);
            *size -= 1;
        }
    }

    if (*size == size_arr)
    {
        puts("\nНе найдены квартиры с такой площадью\n");
    }
    else
    {
        puts("\nУспешно удалены квартиры из таблицы\n");
    }

    return OK_DEL;
}
