#include "add.h"
#include <stdio.h>


unsigned long long bitAdd(unsigned long long origin, unsigned long long add) {
    while (add != 0) {
        unsigned long long ost = origin & add;
        origin = origin ^ add;
        add = ost << 1;
    }
    return origin;
}

int getLogTwo(unsigned int base) {
    int s = 0;
    while (base > 1) {
        base >>= 1;
        s = bitAdd(s, 1);
    }
    return s;
}




StatusCode toBinBase(unsigned long long number, int base, char *res) {
    if (base < 2 || base> 32) {
        return STATUS_INVALID_BASE;
    }
    if ((base & bitAdd(base, ~0)) != 0) {
        return STATUS_INVALID_BASE;
    }
    if (res == NULL) {
        return STATUS_NULL_POINTER;
    }
    if (number == 0) {
        res[0] = '0';
        res[1] = '\0';
        return STATUS_OK;
    }
    char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int power = getLogTwo(base);
    unsigned long long mask = bitAdd(base, ~0);
    int buf[128];
    int i = 0;
    while (number != 0) {
        unsigned long long val = number & mask;
        buf[i] = digits[val];
        i = bitAdd(i, 1);
        number >>= power;
    }
    i = bitAdd(i, ~0);
    int resInd = 0;
    while (i >= 0) {
        res[resInd] = buf[i];
        resInd = bitAdd(resInd, 1);
        i = bitAdd(i, ~0);
    }
    res[resInd] = '\0';
    return STATUS_OK;
}

