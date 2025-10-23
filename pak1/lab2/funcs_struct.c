#include <math.h>
#include <stdbool.h>
#include "lab2_additional.h"
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>

/*основная идея проверять число на делимость, используя уже найденные простые числа, которые хранятся в отдельном массиве
простой поиск от последнего найденного числа до корня+1 или конца массива с простыми числами
*/

int simpleSolution(const int num, Primes *val){
	if( val->lastNum > INT_MAX - 2){
		return NUM_OVERFLOW;
	}

	if (val->lastNum % 2 == 0){
		val->lastNum++;
	}else{
		val->lastNum += 2;
	}

	for (int i = val->lastNum; val->size < num; i +=2) {
		if( i >= INT_MAX - 2){
			return NUM_OVERFLOW;
		}
		bool flag = true;
		int squareI = (int)sqrt(i) ;
		for (int j = 0;  j < val->size && val->array[j] < squareI + 1 ; j ++){
			if (i % val->array[j] == 0) {
				flag = false;
				break;
			}
		}
		if (flag == true){
			val->array[val->size] = i;
			(val->size)++;
		}
		val->lastNum = (i > val->lastNum) ? i: val->lastNum;
	}
	return OK;
}

int reallocatingMem(const int num, Primes *val){
	while (num > val->capacity){
		if (val->capacity > INT_MAX / 2){
			return MEMORY_ALLOCATION_ERROR;
		}
		(val->capacity) *= 2;
	}
	int *temp = (int*)realloc(val->array, sizeof(int) * (val->capacity));
	if (temp == NULL) {
		return MEMORY_ALLOCATION_ERROR; 
	}
	val->array = temp;
	return OK;
}


int readNum(int *res, Primes *val) {
	int num;
	char str[256];
	if(scanf("%255s", str) != 1) {
		return INVALID_NUMBER_INPUT;
	}

	ReturnCode status = parseInt(str, &num);
	if (status != OK){
		return status;
	}
	if (num <= 0){
		return INVALID_NUMBER_INPUT;
	}

	status = reallocatingMem(num, val);
	if (status != OK) {
		return status;
	}

	if (num - 1 < val->size) {
		*res = (val->array)[num-1];
		return OK;
	}


	status = simpleSolution(num, val);
	if (status != OK) {
		return status;
	}
	
	*res = (val->array)[num-1];
	return OK;
}


int initPrimeArray(int capacity, Primes *val){
	val->array = (int*)malloc(sizeof(int) * capacity);
	if (val->array == NULL) {
		return MEMORY_ALLOCATION_ERROR;
	}
	val->capacity = capacity;
	val->lastNum = 2;
	val->size = 1;


	val->array[0] = 2;

	return OK;
}

void freePrimes(Primes *val){
	free(val->array);
	val->array = NULL;

	val->size = 0;
	val->capacity = 0;
	val->lastNum = 0;
	return;
}

