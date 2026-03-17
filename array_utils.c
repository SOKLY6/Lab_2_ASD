#include "array_utils.h"
#include "errors.h"

#include <stdlib.h>

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


int array_realloc();

int table_realloc(Table *table){
    table->capacity *= 2;
    char* *temp = table->keys;
    table->keys = realloc(table->keys, sizeof(char *) * table->capacity);
}


void array_free();

void table_destroy(Table *table){

}