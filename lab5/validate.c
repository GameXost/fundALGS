#include "additional.h"
#include <string.h>
#include <stdlib.h>

int validate(int argc, char **argv, char *flagInp, char *input, char *flagOut, char **outputFileName){
	if (argc != 3 && argc != 4) {
		return INVALID_INPUT;
	}

	if (flagInp[0] != '-' && flagInp[0] != '/') {
		return INVALID_FLAG_INPUT;
	}
	if (strlen(flagInp) != 2 && strlen(flagInp) != 3) {
		return INVALID_FLAG_INPUT;
	}

	switch(strlen(flagInp)) {
		case 2:
			*flagOut = flagInp[1];
			switch (*flagOut){
				case 'd': break;
				case 'i': break;
				case 'a': break;
				case 's': break;
				default: return INVALID_FLAG_INPUT;
			}
			break;
		case 3:
			*flagOut = flagInp[2];
			if (flagInp[1] != 'n'){
				return INVALID_FLAG_INPUT;
			}
			switch (*flagOut){
				case 'd': break;
				case 'i': break;
				case 'a': break;
				case 's': break;
				default: return INVALID_FLAG_INPUT;
			}
			break;
		default:
			return INVALID_FLAG_INPUT;
	}
	if (argc == 3) {
		*outputFileName = malloc(sizeof(char) * (strlen(input) + 5));
		if (*outputFileName == NULL){
			handleError(MEMORY_ALLOCATION_ERROR);
			return MEMORY_ALLOCATION_ERROR;
		}
		sprintf(*outputFileName, "out_%s", input);
	} else if (argc == 4) {
		*outputFileName = argv[3];
	}
	return OK;
}

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
			printf("error occured during memory allocation\n");
			return;
		case ERROR_OPEN_FILE:
			printf("error occured during opening the file\n");
			return;
	}
	return;

}