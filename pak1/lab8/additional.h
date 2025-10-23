#pragma once
#include <stdio.h>

typedef enum {
    OK,
    INVALID_INPUT,
    ERROR_FILE_OPENING,
    ERROR_MEMORY_ALLOCATION,
    ERROR_INVALID_DIG,
    ERROR_FILE_WRITING,
    INVALID_NUMBER_INPUT,
    INVALID_POINTER

}ReturnCode;

typedef struct {
    char *originalNumber;
    char *decimalNumber;
    char *nine;
    char *eighteen;
    char *twentySeven;
    char *thirtySix;
    int base;
    char znak;
    int cap;


}Number;


void handleError(ReturnCode status);

int readNumberString(Number *Num);
int parseAndValidate(Number *num);

int findMinBase(Number *num);
int toDecimal(Number *num);
int writeResult(FILE *output, Number *num);
int fullProcess(Number *num, Number *maxim, const int base);
void freeNum(Number *num);
int writeResult(FILE *output, Number *num);
int valToChar(int val);
int moreThan(Number *num, Number *maxim);
int toBase(Number *num, int base, char **res);