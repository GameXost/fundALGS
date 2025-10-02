
#include <math.h>


double f_a(double x){
	if (x == 0.0) {
		return 1.0;
	}
	return log(1.0 + x) / x;
}

double f_b(double x){
	return exp(-(x*x) / 2);
}

double f_c(double x){
	if (x == 1.0) {
		return INFINITY;
	}
	return log(1.0/(1.0-x));
}

double f_d(double x){
	for (int i = 0; i < x; i++){
		x *= x;
	}
	return x;
}


double trapTrap(double a, double b, int n, double (*func)(double)){
	const double width = (b - a) / n;

	double trapIntegral = 0;
	for (int i = 0; i < n; i++){
		const double x1 = a + i * width;
		const double x2 = a + (i + 1) * width;
		
		trapIntegral += 0.5 * (x2 - x1) * (func(x1) + func(x2));
	}
	return trapIntegral;
}