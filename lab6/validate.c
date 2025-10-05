#include "additional.h"
#include <stdio.h>

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
    }
}