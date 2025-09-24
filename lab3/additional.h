#pragma once
#include <stdbool.h>

typedef enum {
	NumberOne = 0,
	Prime,
	Composite,
	InvalidNumber,
	Zero
} PrimeStatus;

typedef enum ReturnCode {
	OK = 0,
	INVALID_INPUT,
	INVALID_FLAG_INPUT,
	INVALID_NUMBER_INPUT,
	NUM_OVERFLOW,
	MEMORY_ALLOCATION_ERROR

}ReturnCode;


void handleError(ReturnCode status);
int parseFloat(char *str, float *num);
int validate(int argc, char *argv[], char *flag, float *nums);

int for_q(float *nums, float res[6][2], int *cnt);
int for_t(float *nums, bool *res);
int for_m(float *nums, bool *res);