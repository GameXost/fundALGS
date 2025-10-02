#include "additional.h"
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

int main(int argc, char **argv) {
	setlocale(LC_ALL, "");

	//getting data from argv
	char *flagInp = argv[1];
	char *inputFileName = argv[2];
	char *outputFileName; // выходной файл
	char flagOut; // флаг очие=щенный для свитча

	ReturnCode status = validate(argc, argv, flagInp, inputFileName, &flagOut, &outputFileName);
	if (status != OK){
		handleError(status);
		return status;
	}
	//take away from main
	//allocate memory for outputFileName

	// openfile for reading
	FILE *resFileInput = fopen(inputFileName, "r");
	if (resFileInput == NULL){
		printf("BBBBB");
		handleError(ERROR_OPEN_FILE);
		return ERROR_OPEN_FILE;
	}
	// open file for writing
	FILE *resFileOutput = fopen(outputFileName, "w");
	if (resFileOutput == NULL) {
		printf("AAAAAAA");
		handleError(ERROR_OPEN_FILE);
		return ERROR_OPEN_FILE;
	}

	switch(flagOut){
		case 'd':
			status = for_d(resFileInput, resFileOutput);
			if (status != OK){
				handleError(status);
				break;
			}
			break;
		case 'i':
			status = for_i(resFileInput, resFileOutput);
			if (status != OK){
				handleError(status);
				break;
			}
			break;
		case 'a':
			status = for_a(resFileInput, resFileOutput);
			if (status != OK){
				handleError(status);
				break;
			}
			break;
		case 's':
			status = for_s(resFileInput, resFileOutput);
			if (status != OK){
				handleError(status);
				break;
			}
			break;
		default: 
			handleError(INVALID_FLAG_INPUT);	
			return INVALID_FLAG_INPUT;
	}
	fclose(resFileInput);
	fclose(resFileOutput);
	free(outputFileName);
	return OK;
}