#include <stdio.h>
#include "additional.h"
#include <stdbool.h>
#include <stdlib.h>
//TODO: func for reading nums ignoring tabs/spaces/ so on
//TODO: func for formatting the input num
//TODO: func for finding the lowest system base
//TODO: func for writing the num into the output file


int readNumberString(FILE *inputFile, Number *Num) {


    int c = 0;
    bool flag = true;
    size_t curSize = 0;
    size_t capacity = 16;
    char *buf = (char*)malloc(capacity * sizeof(char));
    if (buf == NULL) {
        return ERROR_MEMORY_ALLOCATION;
    }

    while ((c = getc(inputFile)) != EOF) {
        if (c == '\t' || c == '\n' || c == ' ') {
            if (curSize != 0 && flag) {
                buf[curSize] = '\0';
                Num->originalNumber = buf;
                return OK;
            }

            curSize = 0;
            flag = true;
            free(buf);
            capacity = 16;
            buf = (char*)malloc(capacity * sizeof(char));
            if (buf == NULL) {
                return ERROR_MEMORY_ALLOCATION;
            }

            continue;
        }


        if (flag == false){
            continue;
        }
        if (curSize + 1 >= capacity) {
            capacity *= 2;
            char *newBuf = (char *)realloc(buf, capacity * sizeof(char));
            if (newBuf == NULL) {
                free(buf);
                return ERROR_MEMORY_ALLOCATION;
            }
            buf = newBuf;
        }


        if (('0' <= c && c <= '9') || ('a' <= c && c <= 'z') ||  ('A' <= c && c <= 'Z') || (c == '-' || c == '+')){
            buf[curSize++] = c;
        } else {
            flag = false;
        }
    }
    if (curSize > 0 && flag) {
        buf[curSize] = '\0';
        Num->originalNumber = buf;
        return OK;
    }
    free(buf);
    Num->originalNumber = NULL;
    return OK;
}



int parseAndValidate(Number *num) {

}
