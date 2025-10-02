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
int parseInt(char *str, int *num);
float max(const float a,const float b, const float e);

int validate(int argc, char *argv[], char *flag);

int for_q(float a, float b, float c, float e, float res[6][2], int *cnt);
int for_qq(float *nums, float res[6][2], int *cnt);
int for_t(float *nums, bool *res);
int for_m(int *nums, bool *res);