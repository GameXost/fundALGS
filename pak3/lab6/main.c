#include <stdio.h>
#include "add.h"
#include <stdlib.h>
#include <string.h>

int parseStr(char **res) {
    int cap = 16;
    int len = 0;
    char *str = (char *)malloc(cap);
    if (str == NULL) {
        handleError(MEMORY_ALLOCATION);
        return MEMORY_ALLOCATION;
    }
    int c;
    while ((c = getchar()) != EOF && c != '\n') {
        if (len + 1 >= cap) {
            cap *= 2;
            char *temp = (char *)realloc(str, cap);
            if (temp == NULL) {
                free(str);
                handleError(MEMORY_ALLOCATION);
                return MEMORY_ALLOCATION;
            }
            str = temp;
        }
        str[len++] = c;
    }
    str[len] = '\0';
    *res = str;
    return  OK;
}

int main() {

    char *str = NULL;
    StatusCode status = parseStr(&str);
    if (status != OK) {
        handleError(status);
        return status;
    }

    status = check_brackets(str);
    if (status != OK) {
        handleError(status);
        free(str);
        return status;
    }
    free(str);
    printf("Str is balanced LOL\n");
    return OK;
}
