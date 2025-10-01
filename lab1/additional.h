#pragma once


typedef enum {
	NumberOne,
	Prime,
	Composite,
	InvalidNumber,
	Zero
} PrimeStatus;

typedef enum ReturnCode {
	OK,
	INVALID_INPUT,
	INVALID_FLAG_INPUT,
	INVALID_NUMBER_INPUT,
	NUM_OVERFLOW,
	MEM_ALLOCATION_ERROR,

}ReturnCode;


void handleError(ReturnCode status);
int parseInt(char *str, int *num);
int validate(int argc, char *numInp, char *flagInp, int *num, char *flag);

int kratno(int number, int *res, int *size);
int simple(int number, PrimeStatus *status);
int sum(int number, int *res);
int factorial(int number, long long *res);
int stepenb(int number,int (*res)[11], int *size);
int hexNumber(const char *numStr, char *res);
