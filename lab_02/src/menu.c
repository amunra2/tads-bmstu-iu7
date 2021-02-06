#include"../inc/menu.h"


void print_menu(void)
{
    system("setterm -foreground red");
    puts("\n\n      Пункты программы:\n");
    system("setterm -foreground green");
    puts("1. Загрузить список квартир из файла");
    puts("2. Добавить квартиру в конец списка");
    puts("3. Удалить квартиры по значению площади");
    puts("4. Найти все двухкомнатное вторичное жильё без живтотных в указанном ценовом диапазоне");
    puts("5. Отсортировать таблицу пузырьком");
    puts("6. Отсортировать таблицу ключей пузырьком");
    puts("7. Отсортировать таблицу qsort");
    puts("8. Отсортировать таблицу ключей qsort");
    puts("9. Вывести сравнение сортировок пузырьком и qsort");
    puts("10. Вывести таблицу");
    puts("11. Вывести таблицу по таблице ключей");
    puts("12. Вывести таблицу ключей");
    puts("13. Очистить таблицу");
    puts("\n 0 - выйти из программы\n\n\n");

    printf("Введите желаемый пункт меню: ");
}



short int option_menu(void)
{
    int option = -1; 

    int mis, rc = 0;

    appartment_t flats_arr[MAX_FLATS];

    table_t table = {.maxsize = MAX_FLATS, .size = 0};

    keys_t keys[MAX_FLATS];

    while (option != 0)
    {
        print_menu();

        mis = scanf("%d", &option);

        if (mis != 1)
        {
            puts("Ошибка: пункт меню введён неверно");
            return ERR_OPTION_MUST_BE_NUM;
        }

        if ((option < 0) || (option > 13))
        {
            puts("Ошибка: пункт меню введён неверно");
            return ERR_OPTION_MUST_BE_FROM_0_TO_13;
        }

        // File to array
        if (option == 1)
        {
            char file[MAX_SIZE];

            printf("Введите имя файла: ");
            if (scanf("%s", file) != 1)
            {
                puts("Ошибка: неверно введено имя файла");
                return ERR_NO_SUCH_FILE;
            }

            FILE *flats_file = fopen(file, "r");

            system("clear"); 

            if (flats_file == NULL)
            {
                puts("Ошибка: неверно введено имя файла");
                return ERR_FILE_MISTAKE;
            }

            int size = table.size;

            rc = read_file(flats_file, flats_arr, &size, keys);

            if (rc != 0)
            {
                return rc;
            }

            table.size = size;
            table.keys = keys;
            table.flats_arr = flats_arr;

            fclose(flats_file);

            puts("Список квартир из файла был успешно загружен");
        }
        // Add flat info
        else if (option == 2)
        {
            int size = table.size;

            rc = add_flat(flats_arr, &size, keys);

            if (rc != 0)
            {
                return rc;
            }

            table.size = size;
            table.keys = keys;
            table.flats_arr = flats_arr;
        }
        // Delete flats by square
        else if (option == 3)
        {
            int size = table.size;

            rc = delete_by_square(flats_arr, &size, keys);

            if (rc != 0)
            {
                return rc;
            }

            table.size = size;
            table.keys = keys;
            table.flats_arr = flats_arr;
        }
        //Search
        else if (option == 4)
        {
            rc = search(table);

            if (rc != 0)
            {
                return rc;
            }
        }
        //Table bubble
        else if (option == 5)
        {
            system("clear");
            bubble_table(table);
        }
        //Keys bubble
        else if (option == 6)
        {
            system("clear");
            bubble_table_keys(table);
        }
        //Table qsort
        else if (option == 7)
        {
            system("clear");
            qsort_table(table);
        }
        //Keys qsort
        else if (option == 8)
        {
            system("clear");
            qsort_table_keys(table);
        }
        //Compare sorts
        else if (option == 9)
        {
            char file[MAX_SIZE];

            printf("Введите имя файла: ");
            if (scanf("%s", file) != 1)
            {
                puts("Ошибка: неверно введено имя файла");
                return ERR_NO_SUCH_FILE;
            }

            FILE *flats_file = fopen(file, "r");

            if (flats_file == NULL)
            {
                puts("Ошибка: неверно введено имя файла");
                return ERR_FILE_MISTAKE;
            }

            rc = compare_sorts(flats_file);

            if (rc != 0)
            {
                puts("Ошибка: неверные записи в файле");
                return ERR_FILE_MISTAKE;
            }

            fclose(flats_file);
        }
        //Print table
        else if (option == 10)
        {
            print_table(table);
        }
        //Print table by keys
        else if (option == 11)
        {
            print_table_by_keys(table);
        }
        //Print keys
        else if (option == 12)
        {
            print_table_keys(table);
        }
        //Clear table
        else if (option == 13)
        {
            system("clear");
            table.size = 0;
            puts("Таблица успешно очищена\n");
        }
    }

    system("clear");

    return OK;
}
