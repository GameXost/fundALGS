#pragma once
#include <stdio.h>

typedef enum {
    OK,
    INVALID_INPUT,
    ERROR_FILE_OPENING,
    ERROR_MEMORY_ALLOCATION,
}ReturnCode;

typedef struct {
    char *originalNumber;
    char *decimalNumber;
    int base;
    char znak;


}Number;


int readNumberString(FILE *inputFile, Number *Num);
int parseAndValidate(char *numStr);

int findMinBase(const char *numStr);

int writeResult(FILE *output, const char *numStr, int base);