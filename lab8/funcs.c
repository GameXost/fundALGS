#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include  "additional.h"
#include <stdbool.h>


int readNumberString(Number *Num) {
    int c = 0;
    bool flag = false;
    size_t curSize = 0;
    size_t capacity = 16;

    char *buf = (char*)malloc(capacity * sizeof(char));
    if (buf == NULL) {
        return ERROR_MEMORY_ALLOCATION;
    }

    while ((c = getchar()) != EOF) {
        if (isspace(c)) {
            if (flag) {
                break;
            } else {
                continue;
            }
        }
        if (!isalnum(c) && c != '+' && c != '-'){
            while ((c = getchar()) != EOF && !isspace(c)){};
            curSize = 0;
            flag = false;
            free(buf);
            Num->originalNumber = NULL;
            return INVALID_NUMBER_INPUT;
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
        buf[curSize++] = (char)c;
        flag = true;
    }


    //если ниче не записали
    if (!flag) {
        free(buf);
        Num->originalNumber = NULL;
        return OK;
    }

    //если всё норм
    buf[curSize] = '\0';
    char *res = malloc(curSize + 1);
    if (res == NULL) {
        free(buf);
        Num->originalNumber = NULL;
        return ERROR_MEMORY_ALLOCATION;
    }

    strcpy(res, buf);
    Num->originalNumber = res;
    free(buf);
    return OK;
}


int parseAndValidate(Number *num) {
    if (num == NULL || num -> originalNumber == NULL) {
        return INVALID_NUMBER_INPUT;
    }
    char *inputNum = num->originalNumber;

    //парсим знак
    if (*inputNum == '-') {
        num->znak = '-';
        inputNum++;

    } else if (*inputNum == '+'){
        num->znak = '+';
        inputNum++;
    } else {
        num->znak = '+';
    }

    //нули лишние отбрасыываем
    while (*inputNum == '0' && *(inputNum+1) != '\0'){
        if (*inputNum == '-' || *inputNum == '+' || !isalnum(*inputNum)) {
            return INVALID_NUMBER_INPUT;
        }
        inputNum++;
    }


    //число 0
    if (*inputNum == '\0') {
        char *outputNum = (char*)malloc(sizeof(char) * 2);
        if (outputNum == NULL) {
            return ERROR_MEMORY_ALLOCATION;
        }
        outputNum[0] = '0';
        outputNum[1] = '\0';
        free(num->originalNumber);
        num->originalNumber = outputNum;
        num->znak = '+';
        return OK;
    }

    for (char *check = inputNum; *check; check++) {
        if (!isalnum(*check)) {
            return INVALID_NUMBER_INPUT;
        }
        if (isalpha(*check) && !isupper(*check)) {
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
    if (curBase > 36) {
        return INVALID_INPUT;
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
    return  -1;
}


int valToChar(int val) {
    if (val < 10) {
        return '0' + val;
    }
    return 'A' + (val - 10);
}


int multipleString(char *numStr, int base, char **strRes) {
    int len = strlen(numStr);
    long long ost = 0;
    int cap = len + 10;
    char *res = (char*)malloc(sizeof(char) * cap);
    if (res == NULL) {
        *strRes = NULL;
        return ERROR_MEMORY_ALLOCATION;
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
                *strRes = NULL;
                return ERROR_MEMORY_ALLOCATION;
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
    *strRes = res;
    return OK;
}


int incrementStr(char *numStr, int increm, char **strRes) {
    int len = strlen(numStr);
    long long ost = increm;
    int cap = len + 10;
    int ind = 0;
    char *res = (char*)malloc(sizeof(char) * cap);
    if (res == NULL) {
        *strRes = NULL;
        return ERROR_MEMORY_ALLOCATION;
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
                *strRes = NULL;
                return ERROR_MEMORY_ALLOCATION;
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
        if (dig < 0 || dig >= base) {
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


void freeNum(Number *num) {
    if (num == NULL) {
        return;
    }
    if (num -> originalNumber != NULL) {
        free(num->originalNumber);
        num->originalNumber  = NULL;
    }
    if (num -> decimalNumber != NULL) {
        free(num->decimalNumber);
        num->decimalNumber = NULL;
    }
    if (num->eighteen != NULL) {
        free(num->eighteen);
        num->eighteen = NULL;
    }
    if (num -> nine != NULL) {
        free(num->nine);
        num->nine = NULL;
    }
    if (num->twentySeven != NULL) {
        free(num->twentySeven);
        num->twentySeven = NULL;
    }
    if (num ->thirtySix != NULL) {
        free(num->thirtySix);
        num->thirtySix = NULL;
    }
    return;
}

int moreThan(Number *num, Number *maxim) {
    if (maxim->decimalNumber == NULL || strlen(num->decimalNumber)  > strlen(maxim->decimalNumber)) {
        if (maxim->decimalNumber != NULL) {
            free(maxim->decimalNumber);
        }
        maxim->decimalNumber = strdup(num->decimalNumber);
        if (maxim->decimalNumber == NULL) {
            return  ERROR_MEMORY_ALLOCATION;
        }
        return OK;
    }
    if (strlen(num->decimalNumber) == strlen(maxim->decimalNumber)) {
        for (int i = 0; i< strlen(num->decimalNumber); i++) {
            if (num->decimalNumber[i] > maxim->decimalNumber[i]) {
                free(maxim->decimalNumber);
                maxim->decimalNumber = strdup(num->decimalNumber);
                if (maxim -> decimalNumber == NULL) {
                    return ERROR_MEMORY_ALLOCATION;
                }
                return OK;
            }
        }
    }
    return OK;
}


int toBase(Number *num, int base, char **res) {
    if (num == NULL || num->decimalNumber == NULL || res == NULL) {
        return INVALID_POINTER;
    }
    if (base < 2 || base > 36) {
        return INVALID_INPUT;
    }

    const char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int resLen = 0;
    int cap = 16;
    int *resDig = (int*)malloc(sizeof(int) * cap);
    if (resDig == NULL) {
        return ERROR_MEMORY_ALLOCATION;
    }

    const char *p = num->decimalNumber;

    if (*p == '\0') {
        *res = malloc(2);
        if (*res == NULL) {
            free(resDig);
            return ERROR_MEMORY_ALLOCATION;
        }
        strcpy(*res, "0");
        free(resDig);
        return OK;
    }

    while (*p) {
        if (*p < '0' || *p > '9') {
            free(resDig);
            return INVALID_INPUT;
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
                    return  ERROR_MEMORY_ALLOCATION;
                }
                resDig = temp;
            }

            resDig[resLen++] = ost % base;
            ost /= base;

        }

        p++;
    }

    *res = malloc(resLen + 1);
    if (!*res) {
        free(resDig);
        return ERROR_MEMORY_ALLOCATION;
    }
    for (int i = 0; i < resLen; i++) {
        (*res)[i] = digits[resDig[resLen - 1 - i]];
    }
    (*res)[resLen] = '\0';
    free(resDig);
    return OK;
}



int fullProcess(Number *num, Number *maxim, const int base) {
    ReturnCode status = parseAndValidate(num);
    if (status != OK) {
        return status;
    }

    status = toDec(num->originalNumber, num->base, &num->decimalNumber);
    if (status != OK) {
        return status;
    }

    status = moreThan(num, maxim);
    if (status != OK) {
        return status;
    }

    return OK;

}



