#include "additional.h"
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <string.h>



void handleError(ReturnCode status) {
	switch (status) {
		case OK:
			printf("function completed successfully\n");
			return;
		case INVALID_INPUT:
			printf("error occured: invalid input data received\n\n");
			return;
		case NUM_OVERFLOW:
			printf("error occured: number overflow\n");
			return;
		case INVALID_NUMBER_INPUT:
			printf("error occured. incorrect number received\n");
			return;
		case INVALID_FLAG_INPUT:
			printf("error occured incorrect flag received\n");
			return;
		case MEMORY_ALLOCATION_ERROR:
			printf("error occured during memory allocation");
	}
	return;

}


int parseFloat(char *str, float *num){
	char *end;
	double res = strtod(str, &end);
	if (end == str || *end != '\0'){
		return INVALID_NUMBER_INPUT;
	}
	if (res > FLT_MAX || res < -FLT_MAX){
		return NUM_OVERFLOW;
	}
	*num = (float)res;
	return OK;
}

int parseInt(char *str, int *num) {
	char *end;
	long res = strtol(str, &end, 10);
	if (end == str || *end != '\0') {
		return INVALID_NUMBER_INPUT;
	}
	if (res > INT_MAX || res < INT_MIN) {
		return NUM_OVERFLOW;
	}
	if (res < 0) {
		return INVALID_NUMBER_INPUT;
	}
	*num = (int)res;
	return OK;
}


int validate(int argc, char *argv[], char *flag){
	if (argc < 4 || argc > 6){
		return INVALID_INPUT;
	}
	if (argv[1][0] != '-' && argv[1][0] != '/' || strlen(argv[1]) != 2){
		return INVALID_FLAG_INPUT;
	}
	*flag = argv[1][1];
	switch (*flag){
		case 'q':
			if (argc != 6){
				return INVALID_INPUT;
			};
			break;
		case 'm':
			if(argc != 4){
				return INVALID_INPUT;
			};
			break;
		case 't':
			if (argc != 6){
				return INVALID_INPUT;
			};
			break;
		default: return INVALID_FLAG_INPUT;
	}
	return OK;
}
