#include <stdlib.h>
#include "lab2_additional.h"
#include <stdio.h>
#include <limits.h>

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