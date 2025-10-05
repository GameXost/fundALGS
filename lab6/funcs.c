
#include <math.h>

#include "additional.h"


double f_a(double x, const double e) {
	if (fabs(x) <= e) {
		return 1.0;
	}
	return log(1 + x) / x;
}

double f_b(double x, const double e){
	return exp(-(x*x) / 2);
}

double f_c(double x, const double e){
	return -log(1.0-x);
}

double f_d(double x, const double e){
	if (fabs(x) <= e) {
		return 1.0;
	}
	return pow(x, x);
}


int trapTrap(double a, double b, const double e, double (*func)(double, double), double *res){
	if (a >= b) {
		return INVALID_NUMBER_INPUT;
	}

	int n = 1;
	double h = b - a;
	double I = h * 0.5 * (func(a, e) + func(b, e));
	const int maxIterations = 30;

	for (int iter = 0; iter < maxIterations; iter++) {
		n *= 2;
		h /= 2.0;
		double sum = 0.0;
		for (int i = 0; i < n / 2;  i++) {
			sum += func(a + (2 * i + 1) * h, e);
		}
		double newI = I * 0.5 + h * sum;
		if (fabs(newI - I) < e) {
			*res = newI;
			return OK;
		}
		I = newI;
	}
	*res = I;
	return NO_SOLUTION;

}