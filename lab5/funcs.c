#include "additional.h"
#include <stdio.h>
#include <ctype.h>
#include <wchar.h>
#include <wctype.h>



int for_d(FILE *inputFileName, FILE *outputFileOutput){
	if (inputFileName == NULL || outputFileOutput == NULL){
		return ERROR_OPEN_FILE;
	}

	wint_t c = 0;
	while((c = getwc(inputFileName)) != WEOF){
		if (iswdigit(c)){
			continue;
		}
		if(fputwc(c, outputFileOutput) == WEOF){
			return ERROR_WRITING_IN_FILE;
		}
	}
	return OK;
}

int for_i(FILE *inputFileName, FILE *outputFileName){
	if (inputFileName == NULL || outputFileName == NULL){
		return ERROR_OPEN_FILE;
	}

	wint_t c = 0;
	int cnt = 0;
	while((c = getwc(inputFileName)) != WEOF){
		if (L'a' <= c && c <= L'z' || L'A' <= c && c <= L'Z'){
			cnt++;
		}
		if (c == L'\n'){
			fwprintf(outputFileName, L"%d\n", cnt);
			cnt = 0;
		}
	}
	if (cnt >= 0) {
		fwprintf(outputFileName, L"%d\n", cnt);
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
		if ( L'a' <= c && c <= L'z' || L'A' <= c && c <= L'Z' || L'0' <= c && c <= L'9' || c == L' ') {
			continue;
		}
		if (c == L'\n'){
			fwprintf(outputFileName, L"%d\n", --cnt);
			cnt = 0;
		} else{
			cnt++;
		}
	}
	if (cnt >= 0){
		fwprintf(outputFileName, L"%d\n", --cnt);
	}
	return OK;
}

int hexNumber(wint_t num, wchar_t *res) {
	if (num == WEOF) {
		return INVALID_NUMBER_INPUT;
	}
	if (num == 0) {
		res[0] = L'0';
		res[1] = L'\0';
		return OK;
	}

	wchar_t digits[] = L"0123456789ABCDEF";
	int size = 0;
	for(;num > 0;) {
		wint_t x = num % 16;
		res[size] = digits[x];
		size++;
		num /= 16;
	}
	res[size] = L'\0';

	for (int i = 0; i < size / 2; i++) {
		wchar_t temp = res[i];
		res[i] = res[size - i - 1];
		res[size - i - 1] = temp;
	}

	return OK;
}

int for_a(FILE *inputFileName, FILE *outputFileName){
	if (inputFileName == NULL || outputFileName == NULL){
		return ERROR_OPEN_FILE;
	}
	wint_t c = 0;
	while ((c = getwc(inputFileName)) != WEOF){
		if (iswdigit(c)){
			continue;
		}
		if (c == L'\n') {
			if (fputwc(L'\n',outputFileName) == WEOF) {
				return ERROR_WRITING_IN_FILE;
			}
			continue;
		}
		if (c == L'\r') {
			continue;
		}
		wchar_t res[20];
		hexNumber(c, res);
		fwprintf(outputFileName, L"%ls", res);
	}
	return OK;
}
