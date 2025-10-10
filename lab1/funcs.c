#include <stdbool.h>
#include "additional.h" 
#include <limits.h>
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

// -h числа в пределах 100 кратные number
int kratno(int number, int *res, int *size) {
	if(number > 100){
		res[0] = 0;
		return OK;
	}
	bool flag = false;
	for (int i = 1; i <= 100; i++){
		if (i % number == 0) {
			res[*size] = i;
			(*size)++;
			flag = true;
		}
	}
	if (flag == false) {
		res[0] = number;
		(*size)++;
	}
	return OK;
} 

// -p число простое или составное
int simple(int number, PrimeStatus *status) {
	if (number == 1) {
		*status = NumberOne;
		return OK;
	} else if (number == 2) {
		*status = Prime;
		return OK;
	} else if (number == 0) {
		*status = Zero;
		return OK;
	} else if (number < 1) {
		*status = InvalidNumber;
		return OK;
	}
	for (int i = 2; i < (int)sqrt(number) + 1;i++) {
		if (number % i == 0) {
			*status =  Composite;
			return OK;
		}
	}
	*status = Prime;
	return OK;
}

// -a сумма всех натуральных чисел от 1 до Number
int sum(int number, int *res) {
	if (number < 1) {
		return INVALID_INPUT;
	}
	int sum = (number * (1 + number)) / 2 ;
	res[0] = sum;
	return OK;
}

// -f факториал number
int factorial(int number, long long *res) {
	if (number < 0) {
		return INVALID_INPUT;
	} 
	long long fac = 1;
	for (int i = 2; i <= number; i++) {
		if (fac > LLONG_MAX / i) {
			res[0] = LLONG_MAX;
			return NUM_OVERFLOW;
		}
		fac *= i;
	}
	res[0] = fac;
	return OK;
}

// -e таблица степеней от 1 до number
int stepenb(int number,int (*res)[11], int *size) {
	for (int i = 1; i <= number; i++) {
		for (int j = 1; j <= 10; j++) {
			long long val = 1;
			for (int k = 0; k < i; k++) {
				if (val > (long long)INT_MAX / j) {
					return NUM_OVERFLOW;
				}
				val *= j;
			}
			res[j][i] = (int)val;
			(*size)++;
		}
	}
	return OK;
}

//-s перевод в 16 систему
int hexNumber(const char *numStr, char **res) {

	if (numStr == NULL){
		return INVALID_NUMBER_INPUT;
	}

	const char *p = numStr;
	while (*p == '0'){
		p++;
	}
	const char digits[] = "0123456789ABCDEF";
	int resLen = 0;
	int base = 16;
	int cap = 16;
	int *resDig = (int*)malloc(sizeof(int) * cap);
	if (resDig == NULL) {
		return MEM_ALLOCATION_ERROR;
	}


	if (*p == '\0') {
		*res = (char*)malloc(2);
		if (*res == NULL) {
			free(resDig);
			return MEM_ALLOCATION_ERROR;
		}
		strcpy(*res, "0");
		free(resDig);
		return OK;
	}

	while (*p) {
		if (*p < '0' || *p > '9') {
			free(resDig);
			return INVALID_INPUT;
		}
		int digit = *p - '0';
		int  ost = digit;

		for (int i = 0; i < resLen; i++) {
			int val = resDig[i] * 10 + ost;
			resDig[i] = val % base;
			ost = val / base;
		}

		while (ost > 0) {
			if (resLen >= cap) {
				cap *= 2;
				int *temp = (int*)realloc(resDig, sizeof(int) * cap);
				if (temp == NULL) {
					free(resDig);
					return  MEM_ALLOCATION_ERROR;
				}
				resDig = temp;
			}

			resDig[resLen++] = ost % base;
			ost /= base;

		}

		p++;
	}

	*res = malloc(resLen + 1);
	if (!*res) {
		free(resDig);
		return MEM_ALLOCATION_ERROR;
	}
	for (int i = 0; i < resLen; i++) {
		(*res)[i] = digits[resDig[resLen - 1 - i]];
	}
	(*res)[resLen] = '\0';
	free(resDig);
	return OK;
}







