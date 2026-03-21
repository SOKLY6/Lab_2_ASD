#include "array_utils.h"
#include "errors.h"

#include <stdlib.h>
#include <string.h>

int table_init(Table *table){
    table->len = 0;
    table->capacity = BASE_CAPACITY;
    table->keys = calloc(table->capacity, sizeof(char *));
    if (table->keys == NULL) {
        return ALLOCATION_MEMORY_ERROR;
    }
    table->values = calloc(table->capacity, sizeof(char *));
    if (table->values == NULL) {
        free(table->keys);
        return ALLOCATION_MEMORY_ERROR;
    }
    return 0;
}


int table_realloc(Table *table){
    size_t new_capacity = table->capacity * 2;
    char **new_keys = calloc(new_capacity, sizeof(char *));
    char **new_values = calloc(new_capacity, sizeof(char *));
    if (new_keys == NULL || new_values == NULL) {
        if (new_keys != NULL) {
            free(new_keys);
        }
        if (new_values != NULL) {
            free(new_values);
        }
        return REALLOCATION_MEMORY_ERROR;
    }
    for (size_t i = 0; i < table->capacity; i++) {
        strcpy(new_keys[i], table->keys[i]);
    }
    for (size_t i = 0; i < table->capacity; i++) {
        strcpy(new_values[i], table->values[i]);
    }
    free(table->keys);
    free(table->values);
    table->keys = new_keys;
    table->values = new_values;
    table->capacity = new_capacity;
    return 0;
}


int table_add_key_value(Table *table, char* *key, char* *value) {
    if (table->len == table->capacity) {
        if (table_realloc(table) == REALLOCATION_MEMORY_ERROR) {
            return REALLOCATION_MEMORY_ERROR;
        }
    }
    table->keys[table->len] = *key;
    table->values[table->len] = *value;
    table->len++;
    return 0;
}


void array_free(char* **array_str, size_t *array_len) {
    for (size_t i = 0; i < *array_len; i++) {
        free((*array_str)[i]);
    }
    free(*array_str);
    return 0;
}


void table_destroy(Table *table){
    if (table == NULL || table->len == 0) {
        return PTR_NULL;
    }
    array_free(table->keys, &table->len);
    array_free(table->values, &table->len);
}