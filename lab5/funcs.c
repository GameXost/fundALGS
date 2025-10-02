#include "additional.h"
#include <stdio.h>
#include <ctype.h>
#include <wctype.h>
#include <wchar.h>
//TODO: ебануть везде wide char т.к хуй знает что введут
int for_d(FILE *inputFileName, FILE *ouputFileOutput){
	if (inputFileName == NULL || ouputFileOutput == NULL){
		return ERROR_OPEN_FILE;
	}
	int c = 0;
	while((c = getc(inputFileName)) != EOF){
		if (isdigit(c)){
			continue;
		}
		if(fputc(c, ouputFileOutput) == EOF){
			return ERROR_OPEN_FILE;
		}
	}
	return OK;
}

int for_i(FILE *inputFileName, FILE *outputFileName){
	if (inputFileName == NULL || outputFileName == NULL){
		return ERROR_OPEN_FILE;
	}
	int c = 0;
	int cnt = 0;
	while((c = getc(inputFileName)) != EOF){
		if (isalpha(c)){
			cnt++;
		}
		if (c == '\n'){
			fprintf(outputFileName, "%d\n", cnt);
			cnt = 0;
		}
	}
	return OK;
}


int for_s(FILE *inputFileName, FILE *outputFileName){
	if (inputFileName == NULL || outputFileName == NULL){
		return ERROR_OPEN_FILE;
	}
	wint_t c = 0;
	int cnt = 0;
	while((c = fgetwc(inputFileName)) != WEOF){
		if ( 'a' <= c && c <= 'z' || 'A' <= c && c <= 'Z' || '0' <= c && c <= '9' || c == L' '){continue;}
		if (c == L'\n'){
			fwprintf(outputFileName, L"%d\n", cnt);
			cnt = 0;
		} else{
			cnt++;
		}
	}
	if (cnt > 0){
		fwprintf(outputFileName, L"%d\n", cnt);
	}
	return OK;
}

int hexNumber(int num, char *res) {
	if (num == 0) {
		res[0] = '0';
		res[1] = '\0';
		return OK;
	}
	char digits[] = "0123456789ABCDEF";
	int size = 0;
	for (;num > 0;) {
		int x = num % 16;
		res[size] = digits[x];
		size++;
		num /= 16; 
	}
	res[size] = '\0';
	return OK;
}

int for_a(FILE *inputFileName, FILE *outputFileName){
	if (inputFileName == NULL || outputFileName == NULL){
		return ERROR_OPEN_FILE;
	}
	int c = 0;
	while ((c = getc(inputFileName)) != EOF){
		if (isdigit(c) || c == '\n'){
			continue;
		}
		char res[3];
		ReturnCode status = hexNumber(c, res);
		if(status != OK){
			return status;
		}
		fprintf(outputFileName, "%s", res);
	}
	return OK;
}