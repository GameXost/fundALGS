
#include <stdio.h>
#include "add.h"

void handleError(StatusCode status) {
    switch (status) {
        case STATUS_INVALID_BASE:
            printf("Error: Invalid base (must be power of 2 within 2 - 32).\n");
            break;
        case STATUS_NULL_POINTER:
            printf("Error: Null pointer received\n");
            break;
        case STATUS_OK:
            break;
        default:
            printf("Error: Unknown error\n");
    }
}
void Printing(unsigned long long num, int base) {
    char buf[128];

    StatusCode status = toBinBase(num, base, buf);
    if (status != STATUS_OK) {
        handleError(status);
        return;
    }
    printf("num: %llu, Base: %d  Res: %s\n", num, base, buf);
}
int main() {
    Printing(100, 10);
    Printing(100, 2);
    Printing(-15, 16);



}