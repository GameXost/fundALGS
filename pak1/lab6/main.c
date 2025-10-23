#include <stdlib.h>
#include "additional.h"
#include <math.h>
#include <stdio.h>


int main(int argc, char **argv) {
    if (argc < 2) {
        handleError(INVALID_INPUT);
        return INVALID_INPUT;

    }
    char *end;
    const double e = strtod(argv[1], &end);
    if (end == argv[1] || *end != '\0') {
        handleError(INVALID_NUMBER_INPUT);
        return INVALID_NUMBER_INPUT;
    }

    if (e <= 0.0) {
        handleError(INVALID_NUMBER_INPUT);
        return INVALID_NUMBER_INPUT;
    }
    double resA, resB, resC, resD;

    ReturnCode status = trapTrap(0.0, 1.0, e, f_a, &resA);
    if (status != OK) {
        handleError(status);
        return status;
    }
    printf("Integr for a: %f\n", resA);


    double z = sqrt(2.0 * log(1.0/e));
    status = trapTrap(-z, z, e, f_b, &resB);
    if (status != OK) {
        handleError(status);
        return status;
    }
    printf("Integr for b: %f\n", resB);


    double delt = e / log(1.0 / e);
    status = trapTrap(0.0, 1.0 - delt, e, f_c, &resC);
    if (status != OK) {
        handleError(status);
        return status;
    }
    resC  += (-delt * log(delt) + delt);
    printf("Integr for c: %f\n", resC);


    status = trapTrap(0.0, 1.0, e, f_d, &resD);
    if (status != OK) {
        handleError(status);
        return status;
    }
    printf("integr for d: %f\n", resD);

    return OK;
}
