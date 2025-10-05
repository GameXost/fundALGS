#include <ctype.h>
#include <stdio.h>
#include "additional.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "../lab6/additional.h"
//DONE:

//TODO: func for reading nums ignoring tabs/spaces/ so on
//TODO: func for formatting the input num

//NEXT TO DO
//TODO: func for finding the lowest system base
//TODO func for converting to decimal system
//TODO: func for writing the num into the output file

//the result of the below is a string consists of [2, 36] s.s. symbols and + - need to be validated properly in next func

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
            char *newBuf = (char*)realloc(buf, capacity * sizeof(char));
            if (newBuf == NULL) {
                free(buf);
                Num->originalNumber = NULL;
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


//the func below normalizuet number, if there is any extra - || +, the number is incorrect, also deletes extra zeroes in front
int parseAndValidate(Number *num) {

    char *inputNum = num->originalNumber;

    if (*inputNum == '-') {
        num->znak = '-';
        inputNum++;

    } else if (*inputNum == '+'){
        num->znak = '+';
        inputNum++;
    } else {
        num->znak = '+';
    }

    while (*inputNum == '0' && *(inputNum+1) != '\0'){
        if (*inputNum == '-' || *inputNum == '+' || !isalnum(*inputNum)) {
            return INVALID_NUMBER_INPUT;
        }
        inputNum++;
    }

    if (*inputNum == '\0') {
        return INVALID_NUMBER_INPUT;
    }

    for (char *check = inputNum; *check; check++) {
        if (!isalnum(*check)) {
            return INVALID_NUMBER_INPUT;
        }
    }
    char *outputNum = (char*)malloc(strlen(inputNum)+1);
    if (outputNum == NULL) {
        return ERROR_MEMORY_ALLOCATION;
    }


    strcpy(outputNum, inputNum);
    free(num->originalNumber);
    num->originalNumber = outputNum;
    return OK;
}


int findMinBase(Number *num) {
    int curBase = 2;
    int val = 2;
    for (size_t i = 0; i < strlen(num->originalNumber); i++) {
        char ch = tolower(num->originalNumber[i]);
        if ('a' <= ch && ch <= 'z') {
            val = ch - 'a' + 11;
        } else if ('0' <= ch && ch <= '9') {
            val = ch - '0' + 1;
        }
        curBase = (curBase > val) ? curBase: val;
    }
    num->base = curBase;
    return OK;
}



int charToVal(char c) {
    if (isdigit(c)) {
        return c - '0';
    }
    if (isalpha(c)) {
        return tolower(c) - 'a'+10;
    }
}

int multipleString(char *numStr, int base, char **strRes) {
    int len = strlen(numStr);
    int ost = 0;
    int cap = len + 10;
    char *res = (char*)malloc(sizeof(char) * cap);
    if (res == NULL) {
        return ERROR_MEMORY_ALLOCATION;
    }
    int ind = 0;

    for (int i = len - 1; i >= 0; i--) {
        int dig = numStr[i] - '0';
        int prod = dig * base + ost;
        res[ind++] = (prod % 10) + '0';
        ost = prod / 10;
    }

    for (;ost > 0;) {
        if (ind+1 >= cap ) {
            cap *= 2;
            char *temp = (char*)realloc(res, cap);
            if (temp == NULL) {
                return ERROR_MEMORY_ALLOCATION;
            }
            res = temp;
        }
        res[ind++] = (ost % 10) + '0';
        ost /= 10;
    }
    res[ind] = '\0';

    for (int i = 0; i < ind / 2; i++) {
        char temp = res[i];
        res[i] = res[ind - i - 1];
        res[ind - i - 1] = temp;
    }
    *strRes = res;
    return OK;
}


int incrementStr(char *numStr, int increm, char **strRes) {
    int len = strlen(numStr);
    int ost = increm;
    int cap = len + 10;
    int ind = 0;
    char *res = (char*)malloc(sizeof(char) * cap);
    if (res == NULL) {
        return ERROR_MEMORY_ALLOCATION;
    }
    for (int i = len - 1; i >= 0; i--) {
        int dig = numStr[i] - '0';
        int sum = dig + ost;
        res[ind++] = (sum % 10) + '0';
        ost = sum / 10;
    }
    while (ost > 0) {
        if (ind +1 >= cap) {
            cap *= 2;
            char *temp = (char*)realloc(res, sizeof(char) * cap);
            if (temp == NULL) {
                return ERROR_MEMORY_ALLOCATION;
            }
            res = temp;
        }
        res[ind++] = (ost % 10) + '0';
        ost /= 10;
    }
    res[ind] = '\0';
    for (int i = 0; i < ind/2; i++) {
        char temp = res[i];
        res[i] = res[ind - i - 1];
        res[ind - i - 1] = temp;
    }
    *strRes = res;
    return OK;
}


int toDec(char *numStr, int base, char **outRes) {
    char *res = (char*)malloc(sizeof(char) * 2);
    if (res == NULL) {
        return ERROR_MEMORY_ALLOCATION;
    }
    res[0] = '0';
    res[1] = '\0';

    for(int i = 0; numStr[i]; i++) {
        int dig = charToVal(numStr[i]);
        if (dig < 0|| dig >= base) {
            free(res);
            *outRes = NULL;
            return ERROR_INVALID_DIG;
        }
        char *preResMul = NULL;
        ReturnCode status = multipleString(res, base, &preResMul);
        free(res);
        if (status != OK) {
            *outRes = NULL;
            return status;
        }
        char *preResAdd = NULL;
        status = incrementStr(preResMul, dig, &preResAdd);
        free(preResMul);
        if (status != OK) {
            *outRes = NULL;
            return status;
        }
        res = preResAdd;
    }
    *outRes = res;
    return OK;

}