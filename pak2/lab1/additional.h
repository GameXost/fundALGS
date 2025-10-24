#pragma once
#include <stdbool.h>


typedef enum {
    OK,
    INVALID_INPUT,
    MEMORY_ALLOCATING_ERROR,
}ReturnCode;

typedef struct {
    long long numer;
    long long denumer;
}Fraction;

typedef struct {
    int size;
    int capacity;
    double *data;
}Array;

void handleError(ReturnCode status);
int ifThen(Array *res, int base, int cnt, ...);
bool checkProper(Fraction f, int base);
long long gcd(long long a, long long b);