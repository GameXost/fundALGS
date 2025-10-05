#include "additional.h"
#include <stdio.h>


int main(int argc, char **argv) {

    if (argc < 3) {
        handleError(INVALID_INPUT);
        return INVALID_INPUT;
    }

    const char *inputFileName = argv[1];
    const char *outputFileName = argv[2];


    FILE *inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL) {
        handleError(ERROR_FILE_OPENING);
        return ERROR_FILE_OPENING;
    }


    FILE *outputFile = fopen(outputFileName, "w");
    if (outputFile == NULL) {
        fclose(inputFile);
        handleError(ERROR_FILE_OPENING);
        return ERROR_FILE_OPENING;
    }


    char *str[16192];
    ReturnCode status =

    fclose(inputFile);
    fclose(outputFile);

}
