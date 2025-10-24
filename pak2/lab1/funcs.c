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

// конвертит в правильную дробь конечную  drob p/q
Fraction doubleToFract(double num) {
    const double EPS = 1e-12;
    const long long MAX_DEN = 1e12;

    long long a0 = floor(num);
    double frac = num - a0;

    if (fabs(frac) < EPS) {
        return (Fraction){a0, 1};
    }

    long long p0 = 1, q0 = 0;

    long long p1 = a0, q1 = 1;

    double x = num;
    while (true) {
        x = 1.0 / (x - floor(x));
        long long a = floor(x);
        long long p2 = a * p1 + p0;
        long long q2 = a * q1 + q0;

        if (fabs(num - (double)p2 / q2) < EPS || q2 > MAX_DEN) {
            return (Fraction){p2, q2};
        }

        p0 = p1;
        q0 = q1;

        p1 = p2;
        q1 = q2;
    }
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
    const double EPS = 1e-12;

    va_list args;
    va_start(args, cnt);
    for (int i = 0; i < cnt; i++) {
        double x = va_arg(args, double);
        if (x <= EPS || x >= 1 - EPS) {
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
