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
        case ERROR_INVALID_DIG:
            printf("enter the correct number in base system???\n");
            break;
        case ERROR_FILE_WRITING:
            printf("occured error while writing in file\n");
            break;
        case INVALID_NUMBER_INPUT:
            printf("gotten numbers is invalid\n");
            break;
        case INVALID_POINTER:
            printf("no numbers were received\n");
            break;
    }
}


