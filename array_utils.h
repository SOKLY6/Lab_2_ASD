#ifndef ARRAY_UTILS_H
#define ARRAY_UTILS_H

#include <stddef.h>

#define BASE_CAPACITY 16

typedef struct Table {
    char* *keys;
    char* *values;
    size_t len;
    size_t capacity;
} Table;

int table_init(Table *table);
int table_realloc(Table *table);
int table_create(const char *file_name, Table *table);
void table_print(const Table *table);
void table_destroy(Table *table);

#endif