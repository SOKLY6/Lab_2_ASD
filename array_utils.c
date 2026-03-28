#include "array_utils.h"
#include "errors.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int table_init(Table *table){
    table->len = 0;
    table->capacity = BASE_CAPACITY;
    table->keys = (char **)calloc(table->capacity, sizeof(char *));
    if (table->keys == NULL) {
        return ALLOCATION_MEMORY_ERROR;
    }
    table->values = (char **)calloc(table->capacity, sizeof(char *));
    if (table->values == NULL) {
        free(table->keys);
        return ALLOCATION_MEMORY_ERROR;
    }
    return 0;
}


int table_realloc(Table *table){
    size_t new_capacity = table->capacity * 2;
    char **new_keys = (char **)calloc(new_capacity, sizeof(char *));
    char **new_values = (char **)calloc(new_capacity, sizeof(char *));
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
        new_keys[i] = table->keys[i];
    }
    for (size_t i = 0; i < table->capacity; i++) {
        new_values[i] = table->values[i];
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
    *array_str = NULL;
    return;
}


int table_destroy(Table *table){
    if (table == NULL) {
        return PTR_NULL;
    }
    array_free(&(table->keys), &table->len);
    array_free(&(table->values), &table->len);
    return 0;
}


int table_create_from_file(const char *file_path, Table *table) {
    FILE *fIn;
    char key_buf[BUFSIZ], *kb = key_buf;
    char value_buf[BUFSIZ], *vb = value_buf;
    char c;

    fIn = fopen(file_path, "r");
    if(fIn == NULL) {
        return OPENING_FILE_ERROR;
    }
    size_t num_pair;
    if (fscanf(fIn, "%zu", &num_pair) != 1 || num_pair <= 0) {
        fclose(fIn);
        return VALUE_ERROR;
    }
    fgetc(fIn);

    for (size_t i = 0; i < num_pair; i++) {
        if (fgets(key_buf, BUFSIZ, fIn) == NULL || 
            fgets(value_buf, BUFSIZ, fIn) == NULL) {
            fclose(fIn);
            return INCORRECT_KEY_VALUE_FORMAT;
        }
        char *ptr;

        if ((ptr = strchr(key_buf, '\n')) != NULL) *ptr = '\0';
        if ((ptr = strchr(value_buf, '\n')) != NULL) *ptr = '\0';

        char *key = (char *)malloc(strlen(key_buf) + 1);
        if (key != NULL) {
            strcpy(key, key_buf);
        }
        char *value = (char *)malloc(strlen(value_buf) + 1);
        if (value != NULL) {
            strcpy(value, value_buf);
        }
        if (key == NULL || value == NULL) {
            free(key); free(value);
            fclose(fIn);
            return ALLOCATION_MEMORY_ERROR;
        }
        int res = table_add_key_value(table, &key, &value);
        if (res != 0) {
            free(key); free(value);
            fclose(fIn);
            return res;
        }
    }
    fclose(fIn);
    return 0;
}


void table_sort(Table *table, int (*compare)(const void *, const void *)) {
    if (table == NULL || table->len <= 1) {
        return;
    }
    for (size_t i = 1; i < table->len; i++) {
        char *current_key = table->keys[i];
        char *current_value = table->values[i];
        
        int j = (int)i - 1;

        while (j >= 0 && compare(table->keys[j], current_key) > 0) {
            table->keys[j + 1] = table->keys[j];
            table->values[j + 1] = table->values[j];
            j--;
        }
        table->keys[j + 1] = current_key;
        table->values[j + 1] = current_value;
    }
}


int table_find_index(const Table *table, const char *key, int (*compare)(const void *, const void *)) {
    if (table == NULL || table->len == 0) {
        return -1;
    }

    int low = 0;
    int high = (int)table->len - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        int res = compare(table->keys[mid], key);

        if (res == 0) {
            return mid;
        }
        if (res < 0) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}


void table_print(const Table *table) {
    if (table == NULL || table->len == 0) {
        return;
    }
    for (size_t i = 0; i < table->len; i++) {
        printf("%s: %s\n", table->keys[i], table->values[i]);
    }
}
