#pragma once

typedef enum {
    OK,
    INVALID_INPUT,
    EQUAL_FILE_PATHS,
    INVALID_FILE_NAME,
    MEMORY_ALLOCATION,
    END_OF_INPUT,
    NOT_BALANCED
}StatusCode;


typedef struct Stack {
    char symb;
    struct Stack *next;
}Stack;
void handleError(StatusCode status);
int check_brackets(const char *str);
