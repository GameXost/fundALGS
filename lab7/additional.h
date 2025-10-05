#pragma once
#include <stdio.h>

typedef enum {
    OK,
    INVALID_INPUT,
    ERROR_FILE_OPENING,
    ERROR_MEMORY_ALLOCATION,
    ERROR_INVALID_DIG
}ReturnCode;

typedef struct {
    char *originalNumber;
    char *decimalNumber;
    int base;
    char znak;


}Number;


void handleError(ReturnCode status);

int readNumberString(FILE *inputFile, Number *Num);
int parseAndValidate(Number *num);

int findMinBase(Number *num);
int toDecimal(Number *num);
int writeResult(FILE *output, Number *num);