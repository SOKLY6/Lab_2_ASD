#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array_utils.h"
#include "errors.h"
#include "comparators.h"
#include "menu.h"
#include "input.h"

void run_test_case(const char *filename) {
    Table test_table;
    printf("\nТЕСТ ФАЙЛА: %s\n", filename);

    if (table_init(&test_table) != 0) {
        printf("Ошибка инициализации таблицы\n");
        return;
    }

    int res = table_create_from_file(filename, &test_table);
    if (res != 0) {
        printf("Ошибка чтения файла\n");
        table_destroy(&test_table);
        return;
    }

    printf("\nИСХОДНАЯ ТАБЛИЦА\n");
    table_print(&test_table);

    table_sort(&test_table, compare_strings);

    printf("\nТАБЛИЦА ПОСЛЕ СОРТИРОВКИ\n");
    table_print(&test_table);

    table_destroy(&test_table);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Использование: %s <путь_к_файлу>\n", argv[0]);
        return 1;
    }

    Table my_table;
    int res = table_init(&my_table);
    if (res != 0) return 1;

    res = table_create_from_file(argv[1], &my_table);
    if (res != 0) {
        if (res == OPENING_FILE_ERROR) printf("Ошибка: Файл не найден\n");
        else printf("Ошибка чтения: %d\n", res);
        table_destroy(&my_table);
        return 1;
    }

    printf("\nИСХОДНАЯ ТАБЛИЦА\n");
    table_print(&my_table);

    table_sort(&my_table, compare_strings);

    printf("\nТАБЛИЦА ПОСЛЕ СОРТИРОВКИ\n");
    table_print(&my_table);

    int choice = 0;
    char search_key[BUFSIZ];

    while (1) {
        menu();
        if (input_value(&choice) != 0) {
            printf("Введите число\n");
            continue;
        }

        if (choice == 2) break;

        if (choice == 1) {
            printf("Введите ключ для поиска: ");
            if (input_string(search_key, BUFSIZ) == 0) {
                int idx = table_find_index(&my_table, search_key, compare_strings);
                if (idx != -1) printf("Значение: %s\n", my_table.values[idx]);
                else printf("Ключ '%s' не найден\n", search_key);
            }
        } else if (choice == 3) {
            run_test_case("test_data/data1.txt");
            run_test_case("test_data/data2.txt");
            run_test_case("test_data/data3.txt");
        }
    }

    table_destroy(&my_table);
    return 0;
}