#include "lab2_additional.h"
#include <stdio.h>

#define BASE_CAP 64

int main(int argc, char *argv[]) {
	if (argc != 2){
		handleError(INVALID_INPUT);
		return INVALID_INPUT;
	}

	Primes val;
	int x;
	int capacity = BASE_CAP; 

	ReturnCode status = parseInt(argv[1], &x);
	if (status != OK) {
		handleError(status);
		return status;
	}

	status = initPrimeArray(capacity, &val);
	if (status != OK){
		handleError(status);
		return status;
	}

	for (int i = 0; i < x; i++){
		int res;
		status = readNum(&res, &val);
		if(status != OK) {
			handleError(status);
			freePrimes(&val);
			return status;
		}
		printf("num: %d\n", res);
	}
	freePrimes(&val);
	return OK;
}
