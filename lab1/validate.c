#include "additional.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void handle_error(returnCode status) {
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
	}
	return;

}

int parseInt(char *str, int *num) {
	char *end;
	errno = 0;
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

// валидирует аргументы, полученные mainом, преобразует В 
int validate(int argc, char *numberInp, char *flagInp, int *num, char *flag){
	if (argc != 3) {
		return INVALID_INPUT;
	}
	
	returnCode status = parseInt(numberInp, num);
	if (status != OK) {
		return status;
	}

	if (flagInp[0] != '-' && flagInp[0] != '/') {
		return INVALID_FLAG_INPUT;
	}
	if (strlen(flagInp) != 2) {
		return INVALID_FLAG_INPUT;
	}

	*flag = flagInp[1];
	switch(*flag) {
		case 'p': break;
		case 'h': break;
		case 's': break;
		case 'e': break;
		case 'a': break;
		case 'f': break;
		default:
			return INVALID_FLAG_INPUT;
	}
	return OK;
}
