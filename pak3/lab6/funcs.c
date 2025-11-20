#include "add.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


int check_brackets(const char *str) {
    StatusCode status = OK;
    Stack *top = (Stack *)malloc(sizeof(Stack));
    if (top == NULL) {
        handleError(MEMORY_ALLOCATION);
        return MEMORY_ALLOCATION;
    }
    top->symb = '\0';
    top->next = NULL;
    int len = strlen(str);
    if (len == 0) {
        free(top);
        return INVALID_INPUT;
    }
    int ind = 0;
    for (; ind < len; ind++) {
        char symb = str[ind];
        if (symb == '(' || symb == '[' || symb == '{' || symb == '<') {
            Stack *node = (Stack *)malloc(sizeof(Stack));
            if (node == NULL) {
                status = MEMORY_ALLOCATION;
                break;
            }

            node->symb = symb;
            node->next = top;
            top = node;
        }
        if (symb == ')' || symb == ']' || symb == '}' || symb == '>') {
            switch (symb) {
                case ')':
                    if (top->symb == '('){
                        Stack *temp = top;
                        top = top->next;
                        free(temp);
                        break;
                    }
                    status = NOT_BALANCED;
                    break;
                case ']':
                    if (top->symb == '[') {
                        Stack *temp = top;
                        top = top->next;
                        free(temp);

                        break;
                    }
                    status = NOT_BALANCED;
                    break;

                case '}':
                    if (top->symb == '{') {
                        Stack *temp = top;
                        top = top->next;
                        free(temp);

                        break;
                    }
                    status = NOT_BALANCED;
                    break;


                case '>':
                    if (top->symb == '<') {
                        Stack *temp = top;
                        top = top->next;
                        free(temp);

                        break;
                    }
                    status = NOT_BALANCED;
                    break;
            }
        }
    }
    if (status == OK) {
        if (top->symb != '\0') {
            status = NOT_BALANCED;
        }
    }
    while (top != NULL) {
        Stack *temp = top;
        top = top->next;
        free(temp);
    }

    return status;
}