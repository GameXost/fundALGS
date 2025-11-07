#include "additional.h"
#include <stdio.h>

#include <stdarg.h>


int overvfprintf(FILE *fptr, const char *str, va_list args) {
    if (fptr == NULL || str == NULL) {
        return -1;
    }

    int written = 0;

    const char *ptr = str;
    while (*ptr) {
        if (*ptr == '%') {
            if (fputc((unsigned char)*ptr, fptr) == EOF){
                return -1;
            }
            written++;
            ptr++;
            continue;
        }
        ptr++;
        if (*ptr == '%') {
            if (fputc('%', fptr) == EOF) {
                return -1;
            }
            written++;
            ptr++;
            continue;

        }
    if (strncmp(ptr, "Ro"))
    }




}
