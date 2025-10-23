#pragma once

typedef enum ReturnCode {
	OK = 0,
	INVALID_INPUT,
	INVALID_FLAG_INPUT,
	INVALID_NUMBER_INPUT,
	NUM_OVERFLOW,
	MEMORY_ALLOCATION_ERROR

}ReturnCode;

typedef struct Primes {
	int *array;
	int size;
	int capacity;
	int lastNum;
}Primes;


int parseInt(char *str, int *num);
void freePrimes(Primes *val);
int simpleSolution(int num, Primes *val);
int reallocatingMem(int num, Primes *val);
int readNum(int *res,Primes *val);
int initPrimeArray(int capacity, Primes *val);
void handleError(ReturnCode status);
