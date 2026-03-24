#include <stdio.h>
#include <string.h>

int input_value(int *value) {
    char c;
    if (scanf("%d%c", value, &c) == 2 && c == '\n') {
        return 0;
    } else {
        while (getchar() != '\n');
        return 1;
    }
}


int input_string(char *buffer, size_t size) {
    if (fgets(buffer, (int)size, stdin) == NULL) {
        return 1;
    }
    
    char *ptr = strchr(buffer, '\n');
    if (ptr) {
        *ptr = '\0';
    } else {
        char c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
    
    return (strlen(buffer) == 0) ? 1 : 0;
}