#include <stdio.h>
#include "additional.h"

int main(int argc, char *argv[]) {
  	if (argc != 3) {
		handle_error(INVALID_INPUT);
    	return INVALID_INPUT;
  	}


	//char *funcNameINp = argv[0]; // название функции - массив чаров
	char *numberInp = argv[1]; // число в представлении массива чаров, мб и не число вовсе  
	char *flagInp = argv[2]; // флаг для функций, тоже массив чаров, т.к -f, /f надо валидировать тоже, мб и не флаг 
	// я ебал эту валидацию
	int num; // куда запишем итоговое число
	char flag;

	returnCode status = validate(argc, numberInp, flagInp, &num, &flag);
	if (status != OK) {
		handle_error(status);
		return status;
	}
	printf("%d %c\n", num, flag);

	if (flag == 'h') {
		int res[100];
		int curSize = 0;
		returnCode status  = kratno(num, res, &curSize);
		if (status != OK) {
			handle_error(status);
			return status;
		}
		for (int i = 0; i < curSize; i++) {
			printf("%d\n", res[i]);
		}
		return status;


	} else if (flag == 'p') {
		PrimeStatus res;
		returnCode status = simple(num, &res);
		if (status != OK) {
			handle_error( status);
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
		returnCode status = factorial(num, &res);
		if (status != OK) {
			handle_error(status);
			return status;
		}
		printf("%d! = %lld\n", num, res);
		return status;

	} else if (flag == 'a') {
		int res;
		returnCode status = sum(num, &res);
		if (status != OK) {
			handle_error(status);
			return status;
		}
		printf("sum of numbers from 1 to %d = %d\n", num, res);
		return status;

	} else if (flag == 'e') {
		if (num < 1 || num > 10) {
			handle_error(INVALID_NUMBER_INPUT);
			return INVALID_NUMBER_INPUT;
		}
		int res[11][11];
		int curSize = 0;
		returnCode status = stepenb(num, res, &curSize);
		if (status != OK) {
			handle_error(status);
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
		char hexRes[10];
		
		returnCode status = hexNumber(num, hexRes);
		if (status != OK) {
			handle_error(status);
			return status;
		}
		for (int i = 0; hexRes[i] != '\0'; i++ ) {
			printf("%c ", hexRes[i]);
		}
		printf("\n");
		return status;
		

	}

	return OK;
}