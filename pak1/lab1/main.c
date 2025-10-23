#include <stdio.h>
#include <stdlib.h>

#include "additional.h"
//TODO: -s в переводе в 16 ричную систему исключить оверфлоу, в 
int main(int argc, char *argv[]) {
  	if (argc != 3) {
		handleError(INVALID_INPUT);
    	return INVALID_INPUT;
  	}

	char *numberInp = argv[1];
	char *flagInp = argv[2]; 
	int num;
	char flag;

	ReturnCode status = validate(argc, numberInp, flagInp, &num, &flag);
	if (status != OK) {
		handleError(status);
		return status;
	}

	if (flag == 'h') {
		int res[100];
		int curSize = 0;
		ReturnCode status  = kratno(num, res, &curSize);
		if (status != OK) {
			handleError(status);
			return status;
		}
		if (res[0] == 0){
			printf("no numbers were found, enter number <= 100\n");
			return OK;
		}
		for (int i = 0; i < curSize; i++) {
			printf("%d\n", res[i]);
		}
		return status;


	} else if (flag == 'p') {
		PrimeStatus res;
		ReturnCode status = simple(num, &res);
		if (status != OK) {
			handleError( status);
			return status;
		}
		switch (res) {
			case Prime:
				printf("number %d is Prime\n", num);
				return status;
			case Composite:
				printf("number %d composite\n", num);
				return status;
			case NumberOne:
				printf("number %d is neither prime nor composite\n", num);
				return status;
			case InvalidNumber:
				printf("number %d is less than 0\n", num);
				return status;
			case Zero:
				printf("number is 0\n");
				return status;
		}


	} else if (flag == 'f') {
		long long res;
		ReturnCode status = factorial(num, &res);
		if (status != OK) {
			handleError(status);
			return status;
		}
		printf("%d! = %lld\n", num, res);
		return status;

	} else if (flag == 'a') {
		int res;
		ReturnCode status = sum(num, &res);
		if (status != OK) {
			handleError(status);
			return status;
		}
		printf("sum of numbers from 1 to %d = %d\n", num, res);
		return status;

	} else if (flag == 'e') {
		if (num < 1 || num > 10) {
			handleError(INVALID_NUMBER_INPUT);
			return INVALID_NUMBER_INPUT;
		}
		int res[11][11];
		int curSize = 0;
		ReturnCode status = stepenb(num, res, &curSize);
		if (status != OK) {
			handleError(status);
			return status;
		}
		for (int i = 1; i <= num; i++) {
			for (int j = 1; j <= 10; j++) {
				printf("%d^%d=%d ", j, i, res[j][i]);
			}
			printf("\n");
		}
		return status;


	} else if (flag == 's') {
		char *hexRes;
		
		ReturnCode status = hexNumber(numberInp, &hexRes);
		if (status != OK) {
			handleError(status);
			free(hexRes);
			return status;
		}
		for (int i = 0; hexRes[i] != '\0'; i++ ) {
			printf("%c ", hexRes[i]);
		}
		printf("\n");
		free(hexRes);
		return status;
		

	}

	return OK;
}