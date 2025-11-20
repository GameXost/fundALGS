#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "additional.h"


char *intToRoman(int number, StatusCode *status) {
    if (number <= 0) {
        *status = INVALID_INPUT;
        return NULL;
    }
    size_t len = 0;
    size_t cap = 16;
    char *buf = (char*)malloc(sizeof(char) * cap);
    if (buf == NULL) {
        *status = MEMORY_ALLOCATION;
        return NULL;
    }
    buf[0] = '\0';

    int i = 0;
    while (number > 0) {
        while (number >= roms[i].value) {
            if (len + strlen(roms[i].letter) + 1 >= cap) {
                cap*=2;
                char *temp = (char*)realloc(buf, cap);
                if (temp == NULL) {
                    free(buf);
                    *status = MEMORY_ALLOCATION;
                    return NULL;
                }
                buf = temp;
            }
            strcat(buf, roms[i].letter);
            len += strlen(roms[i].letter);
            number -= roms[i].value;
        }
        i++;
    }
    *status = OK;
    return buf;
}


char *zec(unsigned int number, StatusCode *status) {
    if (number == 0) {
        *status = OK;
        return strdup("01");
    }
    size_t cap = 16;
    unsigned int *fib = (unsigned int *)malloc(sizeof(unsigned int) * cap);
    if (fib == NULL) {
        *status = MEMORY_ALLOCATION;
        return NULL;
    }

    fib[0] = 1;
    fib[1] = 2;
    size_t len = 2;
    while (fib[len - 1] <= number) {
        if (len + 1 >= cap) {
            cap *= 2;
            unsigned int *temp = (unsigned int *)realloc(fib, sizeof(unsigned int) * cap);
            if (temp == NULL) {
                free(fib);
                *status = MEMORY_ALLOCATION;
                return NULL;
            }
            fib = temp;
        }
        fib[len] = fib[len - 1] + fib[len - 2];
        len++;
    }
    char *res = (char*)calloc(len + 2, 1);
    if (res == NULL) {
        free(fib);
        *status = MEMORY_ALLOCATION;
        return NULL;
    }
    bool usedPrev = false;

    for (int i = len - 1; i >= 0; i--) {
        if (fib[i] <= number && !usedPrev) {
            res[i] = '1';
            number -= fib[i];
            usedPrev = true;
        } else {
            res[i] = '0';
            usedPrev = false;
        }
    }

    for (int i = 0; i < len / 2; i++) {
        char temp = res[i];
        res[i] = res[len - i - 1];
        res[len - i - 1] = temp;
    }

    res[len] = '1';
    res[len+1] = '\0';
    *status = OK;
    return res;
}

char *toBaseSup(char *num, int base, int isUpper, StatusCode *status) {
    if (num == NULL || *num == '\0') {
        *status = INVALID_INPUT;
        return NULL;
    }
    if (strcmp(num, "0") == 0) {
        *status = OK;
        return strdup("0");
    }
    const char lowerDigits[] = "0123456789abcdefghijklmnopqrstuvwxyz";
    const char upperDigits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char *digits = isUpper == 1 ? upperDigits : lowerDigits;
    int resLen = 0;
    int cap = 16;
    int *resDig = (int*)malloc(sizeof(int) * cap);
    if (resDig == NULL) {
        *status = MEMORY_ALLOCATION;
        return NULL;
    }

    const char *p = num;

    while (*p) {
        if (*p < '0' || *p > '9') {
            // if (!isalnum(*p)){
            free(resDig);
            *status = INVALID_INPUT;
            return NULL;
        }
        int digit = *p - '0';
        int  ost = digit;

        for (int i = 0; i < resLen; i++) {
            int val = resDig[i] * 10 + ost;
            resDig[i] = val % base;
            ost = val / base;
        }

        while (ost > 0) {
            if (resLen >= cap) {
                cap *= 2;
                int *temp = (int*)realloc(resDig, sizeof(int) * cap);
                if (temp == NULL) {
                    free(resDig);
                    *status = MEMORY_ALLOCATION;
                    return  NULL;
                }
                resDig = temp;
            }

            resDig[resLen++] = ost % base;
            ost /= base;

        }

        p++;
    }

    char *res = (char*)malloc(resLen + 1);
    if (res == NULL) {
        free(resDig);
        *status = MEMORY_ALLOCATION;
        return NULL;
    }
    for (int i = 0; i < resLen; i++) {
        res[i] = digits[resDig[resLen - 1 - i]];
    }
    res[resLen] = '\0';
    free(resDig);
    *status = OK;
    return res;

}


char *toBase(int num, int base, int isUpper) {
    if (base < 2 || base > 36) {
        base = 10;
    }
    int isNeg = num < 0;
    char buf[64];

    unsigned int absNum = num < 0 ? (unsigned int)(-(long)num): (unsigned int)num;

    snprintf(buf, sizeof(buf), "%u", absNum);
    char *res =  toBaseSup(buf, base, isUpper);
    if (res == NULL) {
        return NULL;
    }
    if (isNeg == 1) {
        size_t len = strlen(res) + 2;
        char *negRes = (char*)malloc(sizeof(char) * len);
        if (negRes == NULL) {
            free(res);
            return NULL;
        }
        negRes[0] = '-';
        strcpy(negRes + 1, res);
        free(res);
        return negRes;
    }
    return res;
}




int charToVal(char c) {
    if (isdigit(c)) {
        return c - '0';
    }

    if (isalpha(c)) {
        return tolower(c) - 'a'+10;
    }
    return  -1;
}


char *multipleString(char *numStr, int base) {
    int len = strlen(numStr);
    long long ost = 0;
    int cap = len + 10;
    char *res = (char*)malloc(sizeof(char) * cap);
    if (res == NULL) {
        return NULL;
    }
    int ind = 0;

    for (int i = len - 1; i >= 0; i--) {
        int dig = numStr[i] - '0';
        long long prod = dig * base + ost;
        res[ind++] = (char)((prod % 10) + '0');
        ost = prod / 10;
    }

    for (;ost > 0;) {
        if (ind+1 >= cap ) {
            cap *= 2;
            char *temp = (char*)realloc(res, cap);
            if (temp == NULL) {
                free(res);
                return NULL;
            }
            res = temp;
        }
        res[ind++] = (char)((ost % 10) + '0');
        ost /= 10;
    }
    res[ind] = '\0';

    for (int i = 0; i < ind / 2; i++) {
        char temp = res[i];
        res[i] = res[ind - i - 1];
        res[ind - i - 1] = temp;
    }
    return res;
}


char *incrementStr(char *numStr, int increm) {
    int len = strlen(numStr);
    long long ost = increm;
    int cap = len + 10;
    int ind = 0;
    char *res = (char*)malloc(sizeof(char) * cap);
    if (res == NULL) {
        return NULL;
    }
    for (int i = len - 1; i >= 0; i--) {
        int dig = numStr[i] - '0';
        long long sum = dig + ost;
        res[ind++] = (char)((sum % 10) + '0');
        ost = sum / 10;
    }
    while (ost > 0) {
        if (ind +1 >= cap) {
            cap *= 2;
            char *temp = (char*)realloc(res, sizeof(char) * cap);
            if (temp == NULL) {
                free(res);
                return NULL;
            }
            res = temp;
        }
        res[ind++] = (char)((ost % 10) + '0');
        ost /= 10;
    }
    res[ind] = '\0';
    for (int i = 0; i < ind/2; i++) {
        char temp = res[i];
        res[i] = res[ind - i - 1];
        res[ind - i - 1] = temp;
    }
    return res;
}


char *toDec(char *numStr, int base, StatusCode *status) {

    if (base < 2 || base > 36) {
        base = 10;
    }
    char *res = (char*)malloc(sizeof(char) * 2);
    if (res == NULL) {
        *status= MEMORY_ALLOCATION;
        return NULL;
    }
    res[0] = '0';
    res[1] = '\0';


    for(int i = 0; numStr[i]; i++) {
        int dig = charToVal(numStr[i]);
        if (dig < 0 || dig >= base) {
            free(res);
            *status = INVALID_INPUT;
            return NULL;
        }
        char *preResMul = NULL;
        preResMul = multipleString(res, base);
        free(res);
        if (preResMul == NULL) {
            *status = INVALID_INPUT;
            return NULL;
        }
        char *preResAdd = NULL;
        preResAdd = incrementStr(preResMul, dig);
        free(preResMul);
        if (preResAdd == NULL) {
            *status = INVALID_INPUT;
            return NULL;
        }
        res = preResAdd;
    }
    *status = OK;
    return res;
}


char *dumpDumpDumpIt(void *ptr, size_t size, StatusCode *status) {
    size_t strSize = size * 8 + size;

    char *res = (char *)malloc(strSize);
    if (res == NULL) {
        *status = MEMORY_ALLOCATION;
        return NULL;
    }

    unsigned char *bytePtr = (unsigned char*)ptr;

    size_t ind = 0;
    for (size_t i = 0; i < size; i++) {
        unsigned char byte = bytePtr[i];
        for (int bit = 7; bit >= 0; bit--) {
            res[ind++] = (byte >> bit) & 1 ? '1':'0';
        }
        if (i < size - 1) {
            res[ind++] = ' ';
        }
    }
    res[ind] = '\0';
    *status = OK;
    return res;
}



