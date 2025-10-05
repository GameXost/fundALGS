#pragma once

typedef enum ReturnCode {
    OK = 0,
    INVALID_INPUT,
    INVALID_NUMBER_INPUT,
    NUM_OVERFLOW,
    NO_SOLUTION
} ReturnCode;

double f_a(double x, const double e);
double f_b(double x, const double e);
double f_c(double x, const double e);
double f_d(double x, const double e);
int trapTrap(double a, double b, const double e, double (*func)(double, double), double *res);
void handleError(ReturnCode status);