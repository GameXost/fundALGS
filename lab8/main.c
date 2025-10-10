#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "additional.h"

int main() {
    int base;
    if (scanf("%d", &base) != 1) {
        handleError(INVALID_INPUT);
        return  INVALID_INPUT;
    }
    if (base < 2 || base > 36) {
        handleError(INVALID_INPUT);
        return INVALID_INPUT;
    }

    Number maxim = {NULL, NULL, NULL, NULL, NULL, NULL, base, '+'};;
    while(1) {
        Number num = {NULL, NULL, NULL, NULL, NULL, NULL, base, '+'};
        ReturnCode status = readNumberString(&num);
        if (status != OK) {
            handleError(status);
            return status;
        }
        if (num.originalNumber && strcmp(num.originalNumber, "Stop") == 0) {
            freeNum(&num);
            break;
        }

        status = fullProcess(&num, &maxim, base);
        if (status != OK) {
            handleError(status);
            freeNum(&maxim);
            freeNum(&num);
            return status;
        }
        freeNum(&num);
    }


    ReturnCode status = toBase(&maxim, 9, &maxim.nine);
    if (status != OK) {
        handleError(status);
        return status;
    }

    printf("decimal %s\n", maxim.decimalNumber);
    printf("nine: %s\n", maxim.nine);

    status = toBase(&maxim, 18, &maxim.eighteen);
    printf("eighteen: %s\n", maxim.eighteen);

    status = toBase(&maxim, 27, &maxim.twentySeven);
    printf("twentySeven: %s\n", maxim.twentySeven);

    status = toBase(&maxim, 36, &maxim.thirtySix);
    printf("thirtySix: %s\n", maxim.thirtySix);


    freeNum(&maxim);
    return OK;

}