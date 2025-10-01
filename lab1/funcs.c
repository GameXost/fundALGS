#include <ctype.h>
#include <stdbool.h>
#include "additional.h" 
#include <limits.h>
#include <math.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

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
int hexNumber(const char *numStr, char *res) {

	if (numStr == NULL){
		return INVALID_NUMBER_INPUT;
	}

	const char *p = numStr;
	while (*p == '0'){
		p++;
	}

	if(*p == '\0'){
		res[0] = '0';
		res[1] = '\0';
		return OK;
	}

	const char digits[] = "0123456789ABCDEF";
	int hexDigits[1024];
	int length = 0;

	for(const char *p = numStr; *p; p++){
		int d = *p - '0';
		unsigned next = 0;
		for(int i = 0; i < length; i++){
			unsigned val = (unsigned)hexDigits[i] * 10U + next;
			hexDigits[i] = val % 16;
			next = val / 16;
		}
		while (next > 0){
			if (length >=1024){
				return NUM_OVERFLOW;
			}
			hexDigits[length++] = next % 16;
			next /= 16;
		}
		next = (unsigned)d;
		for(int i = 0; i < length; i++){
			unsigned val = (unsigned)hexDigits[i] + next;
			hexDigits[i] = val % 16;
			next  = val / 16;
			if (next  == 0){
				break;
			}
		}
		while(next > 0){
			if (length >= 1024){
				return NUM_OVERFLOW;
			}
			hexDigits[length++] = next % 16;
			next /= 16;
		}
	}
	int ind = 0;
	for(int i = length - 1; i >= 0; i--){
		res[ind++] = digits[hexDigits[i]];
	}
	res[ind] = '\0';
	return OK;
}





