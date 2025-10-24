#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#include "additional.h"


long long gcd(long long a, long long b) {
    a = llabs(a);
    b = llabs(b);
    while (b) {
        a %= b;
        long long temp = a;
        a = b;
        b = temp;
    }
    return a;
}

// конвертит в правильную дробь конечную
Fraction doubleToFract(double num) {
    Fraction res;
    double frac = num;
    long long denom = 1;
    while (fabs(frac - round(frac)) > 1e-10 && denom < 1e12) {
        frac *= 10.0;
        denom *= 10;
    }
    res.numer = llround(frac);
    res.denumer = denom;
    long long g = gcd(res.numer, res.denumer);
    res.numer /= g;
    res.denumer /= g;
    return res;
}

//получает чисто число и базу, сообщает, конечная ли дробь
bool checkProper(Fraction f, int base) {
    long long denum = f.denumer;
    long long commonDiv = gcd(denum, base);
    while (commonDiv > 1) {
        while (denum % commonDiv == 0) {
            denum /= commonDiv;
        }
        commonDiv = gcd(denum, base);
    }
    return denum == 1;
}

// валист итерируется по аргмуентам функции
int ifThen(Array *res, int base, int cnt, ...) {
    va_list args;
    va_start(args, cnt);
    for (int i = 0; i < cnt; i++) {
        double x = va_arg(args, double);
        if (x <= 1e-12 || x >= 1 - 1e-12) {
            continue;
        }
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
