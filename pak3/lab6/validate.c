#include "add.h"
#include <stdio.h>

void handleError(StatusCode status) {
    switch (status) {
        case OK:
            printf("everything is fine\n");
            break;
        case INVALID_INPUT:
            printf("invalid input received\n");
            break;
        case EQUAL_FILE_PATHS:
            printf("dont try to overwrite file\n");
            break;
        case INVALID_FILE_NAME:
            printf("smth wrong with your file name or with it's path\n");
            break;
        case MEMORY_ALLOCATION:
            printf("haha LOL memory error\n");
            break;
        case END_OF_INPUT:
            printf("that's the end of user's input\n");
            break;
        case NOT_BALANCED:
            printf("Input String is NOT BALANCED\n");
            break;
        default:
            printf("wtf???\n");
    }
}