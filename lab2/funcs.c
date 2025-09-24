#include <math.h>
#include <stdbool.h>
#include "lab2_additional.h"
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>





int parseInt(char *str, int *num) {
	char *end;
	long res = strtol(str, &end, 10);
	if (end == str || *end != '\0') {
		return INVALID_NUMBER_INPUT;
	}
	if (res > INT_MAX || res < INT_MIN) {
		return NUM_OVERFLOW;
	}
	*num = (int)res;
	return OK;
}


int simpleSolution(int num, int *array, int *curSize, int *totalCap, int *lastNum){
	for (int i = *lastNum+2; *curSize < num; i +=2) {
		bool flag = true;
		int squareI = (int)sqrt(i) ;
		for (int j = 0;  j < *curSize && array[j] < squareI + 1 ; j ++){
			if (i % array[j] == 0) {
				flag = false;
				break;
			}
		}
		if (flag == true){
			array[*curSize] = i;
			(*curSize)++;
		}
		*lastNum = (i > *lastNum) ? i: *lastNum;
	}
	return OK;
}


// TODO: разюить main на более мелкие блоки	
// функция расширения массивва , если число больше
// функция считывания чисел и запуск функции основной

int reallocatingMem(int num, int *capacity, int **array){
	while (num > *capacity){
		(*capacity) *= 2;
	}
	int *temp = realloc(*array, sizeof(int) * (*capacity));
	if (temp == NULL) {
		return MEMORY_ALLOCATION_ERROR; 
	}
	*array = temp;
	return OK;
}



int readNum(int **array, int *capacity, int *size, int *res, int *lastNum) {
	int num;
	char str[256];
	scanf("%s", str);
	ReturnCode status = parseInt(str, &num);
	if (status != OK){
		return status;
	}
	//start block
	status = reallocatingMem(num, capacity, array);
	//next block 
	if (status != OK) {
		return status;
	}
	if (num - 1 < *size) {
		*res = (*array)[num-1];
		return OK;
	}

	status = simpleSolution(num, *array, size, capacity, lastNum);
	if (status != OK) {
		return status;
	}
	*res = (*array)[num-1];
	return OK;
}


int initPrimeArray(int capacity, Primes *val){
	val->array = malloc(sizeof(int) * capacity);
	if (val->array == NULL) {
		return MEMORY_ALLOCATION_ERROR;
	}
	val->capacity = capacity;
	val->lastNum = 3;
	val->size = 2;


	val->array[0] = 2;
	val->array[1] = 3;

	return OK;
}

