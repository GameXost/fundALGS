#include "additional.h"
#include <stdio.h>


void handleError(ReturnCode status) {
    switch (status) {
        case OK:
            printf("function completed successfully\n");
            return;
        case INVALID_INPUT:
            printf("error occured: invalid input data received\n\n");
            return;
        case MEMORY_ALLOCATING_ERROR:
            printf("error occured: while allocating memory \n");
            break;
        default:
            printf("cant find such error lol\n");
    }
}