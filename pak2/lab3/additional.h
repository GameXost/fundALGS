#pragma once
#include <stddef.h>

typedef struct {
    int value;
    const char *letter;
}romanCombs;

typedef enum {
    OK,
    INVALID_INPUT,
    MEMORY_ALLOCATION,

}StatusCode;

romanCombs roms[] = {
    {1000, "M"},
    {900, "CM"},
    {500, "D"},
    {400, "CD"},
    {100, "C"},
    {90, "XC"},
    {50, "L"},
    {40, "XL"},
    {10, "X"},
    {9, "IX"},
    {5, "V"},
    {4, "IV"},
    {1, "I"},
};

char *intToRoman(int number, StatusCode *status);
char *zec(unsigned int number, StatusCode *status);
char *toBaseSup(char *num, int base, int isUpper);
char *toBase(int num, int base, int isUpper, StatusCode *status);
int charToVal(char c);
char *multipleString(char *numStr, int base);
char *incrementStr(char *numStr, int increm);
char *toDec(char *numStr, int base, StatusCode *status);
char *dumpDumpDumpIt(void *ptr, size_t size, StatusCode *status);