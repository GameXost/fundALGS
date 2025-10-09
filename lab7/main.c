#include "additional.h"
#include <stdio.h>


int main(int argc, char **argv) {

    if (argc != 3) {
        handleError(INVALID_INPUT);
        return INVALID_INPUT;
    }




    FILE *inputFile = fopen(argv[1], "r");
    if (inputFile == NULL) {
        handleError(ERROR_FILE_OPENING);
        return ERROR_FILE_OPENING;
    }


    FILE *outputFile = fopen(argv[2], "w");
    if (outputFile == NULL) {
        fclose(inputFile);
        handleError(ERROR_FILE_OPENING);
        return ERROR_FILE_OPENING;
    }


    int numsCnt = 0;
    int numsSkipped = 0;
    ReturnCode finStatus = OK;
    while (1) {
        Number num = {NULL, NULL, 0, '+'};
        ReturnCode status = readNumberString(inputFile, &num);
        if (status != OK) {
            handleError(status);
            freeNum(&num);
            finStatus = status;
            break;
        }

        if (num.originalNumber == NULL) {
            break;
        }
        status = fullProcess(&num);
        if (status == OK) {
            status = writeResult(outputFile, &num);
            if (status != OK) {
                handleError(status);
                freeNum(&num);
                finStatus = status;
                break;
            }
            numsCnt++;
        } else {
            numsSkipped++;
        }
        freeNum(&num);
    }
    fclose(inputFile);
    fclose(outputFile);
    return finStatus;
}
