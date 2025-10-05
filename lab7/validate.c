#include <stdio.h>
#include "additional.h"

void handleError(ReturnCode status) {
    switch (status) {
        case OK:
            break;
        case INVALID_INPUT:
            printf("invalid input data gotten, pls check\n");
            break;
        case ERROR_FILE_OPENING:
            printf("error occured while opening the file\n");
            break;
        case ERROR_MEMORY_ALLOCATION:
            printf("occured allocation memory error");
            break;
    }
}


