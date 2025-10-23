#include <stdarg.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#include "additional.h"
// обрабатывает валист, вызывает чекер, записывает конечные дроби в массив


long gcd(long a, long b) {
    a = labs(a);
    b = labs(b);
    while (b) {
        a %= b;
        long temp = a;
        a = b;
        b = temp;
    }
    return a;
}

Fraction doubleToFract(double num) {
    Fraction res;
    res.numer = (long)(num * 1e+12);
    res.denumer = 1e+12;

    long divide = gcd(res.numer, res.denumer);
    res.numer /= divide;
    res.denumer /= divide;
    return res;
}

//получает чисто число и базу, сообщает, конечная ли дробь
bool checkProper(Fraction f, int base) {
    long denum = f.denumer;
    long divide = gcd(denum, base);
    while (divide > 1) {
        while (denum % divide == 0) {
            denum /= divide;
        }
        divide = gcd(denum, base);
    }
    return denum == 1;
}


int ifThen(Array *res, int base, int cnt, ...) {
    va_list args;
    va_start(args, cnt);
    for (int i = 0; i < cnt; i++) {
        double x = va_arg(args, double);
        Fraction f = doubleToFract(x);

        if (checkProper(f, base)) {
            if (res->size >= res->capacity) {
                res->capacity *= 2;
                double *temp = (double*)realloc(res->data, res->capacity * sizeof(double));
                if (temp == NULL) {
                    va_end(args);
                    return MEMORY_ALLOCATING_ERROR;
                }
                res->data = temp;
            }
            res->data[res->size++] = x;
        }
    }
    va_end(args);
    return OK;
}
