#pragma once
#include <stdbool.h>
#include <stdio.h>
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
	MEMORY_ALLOCATION_ERROR,
	ERROR_OPEN_FILE

}ReturnCode;


void handleError(ReturnCode status);
int validate(int argc, char **argv, char *flagInp, char *input, char *flagOut, char **outputFileName);
int hexNumber(int num, char *res);

int for_d(FILE *inputFileName, FILE *ouputFileOutput);
int for_i(FILE *inputFileName, FILE *outputFileName);
int for_a(FILE *inputFileName, FILE *outputFileName);
int for_s(FILE *inputFileName, FILE *outputFileName);