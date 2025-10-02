#include "additional.h"
#include <string.h>
#include <stdlib.h>

int validate(int argc, char **argv, char *flagOut, char **outputFileName){
	if (argc != 3 && argc != 4) {
		return INVALID_INPUT;
	}

	char *flagInp = argv[1];
	char *inputFileName = argv[2];
	if (flagInp[0] != '-' && flagInp[0] != '/') {
		return INVALID_FLAG_INPUT;
	}
	if (strlen(flagInp) != 2 && strlen(flagInp) != 3) {
		return INVALID_FLAG_INPUT;
	}

	switch(strlen(flagInp)) {
		case 2:
			if (argc != 3) {
				return INVALID_INPUT;
			}
			*flagOut = flagInp[1];
			*outputFileName = malloc(sizeof(char) * (strlen(inputFileName) + 5));
			if (*outputFileName == NULL){
				handleError(MEMORY_ALLOCATION_ERROR);
				return MEMORY_ALLOCATION_ERROR;
			}
			sprintf(*outputFileName, "out_%s", inputFileName);

			switch (*flagOut){
				case 'd': break;
				case 'i': break;
				case 'a': break;
				case 's': break;
				default: return INVALID_FLAG_INPUT;
			}
			break;
		case 3:
			if (argc != 4) {
				return INVALID_INPUT;
			}
			*flagOut = flagInp[2];
			if (flagInp[1] != 'n'){
				return INVALID_FLAG_INPUT;
			}
			*outputFileName = argv[3];

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
	return OK;
}

void handleError(ReturnCode status) {
	switch (status) {
		case OK:
			printf("function completed successfully\n");
			break;
		case INVALID_INPUT:
			printf("error occured: invalid input data received\n\n");
			break;
		case NUM_OVERFLOW:
			printf("error occured: number overflow\n");
			break;
		case INVALID_NUMBER_INPUT:
			printf("error occured. incorrect number received\n");
			break;
		case INVALID_FLAG_INPUT:
			printf("error occured incorrect flag received\n");
			break;
		case MEMORY_ALLOCATION_ERROR:
			printf("error occured during memory allocation\n");
			break;
		case ERROR_OPEN_FILE:
			printf("error occured during opening the file\n");
			break;
		case ERROR_WRITING_IN_FILE:
			printf("error occured while writing in file\n");
			break;

	}
}