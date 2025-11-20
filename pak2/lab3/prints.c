    #include "additional.h"
    #include <stdio.h>
    #include <stdarg.h>
    #include <stdbool.h>
    #include <string.h>

    #include "../lab5/additional.h"
    #define BUF_SIZE 128

    int overfprintf(FILE *fptr, const char *str, ...) {
        if (fptr == NULL || str == NULL) {
            return -1;
        }

        char *ptr = str;
        char buf[BUF_SIZE];
        va_list args;
        va_start(args, str);
        while (*ptr != '\0') {
            if (*ptr == '%') {
                ptr++;
                if (*ptr == '\0'){
                    va_end(args);
                    return -1;
                }
                bool custom = false;
                char spec[3] = {*ptr, *(ptr + 1), '\0'};
                if (*(ptr+1) != '\0') {
                    if (*(ptr + 1) != '\0') {
                        if (strncmp(spec, "Ro", 2) == 0 ||
                            strncmp(spec, "Zr", 2) == 0 ||
                            strncmp(spec, "Cv", 2) == 0 ||
                            strncmp(spec, "CV", 2) == 0 ||
                            strncmp(spec, "to", 2) == 0 ||
                            strncmp(spec, "TO", 2) == 0 ||
                            strncmp(spec, "mi", 2) == 0 ||
                            strncmp(spec, "mu", 2) == 0 ||
                            strncmp(spec, "md", 2) == 0 ||
                            strncmp(spec, "mf", 2) == 0) {
                            custom = true;
                            }
                        }
                    if (custom) {
                        StatusCode status = OK;
                        char *res = NULL;
                        if (strncmp(buf, "Ro", 2) == 0) {
                            int x = va_arg(args, int);
                            char *res = intToRoman(x, &status);

                            fprintf(fptr, "%s\n", res);
                        } else if (strncmp(buf, "Zr", 2) == 0) {
                            unsigned int x = va_arg(args, unsigned int);
                            char *res = zec(x, &status);

                            fprintf(fptr, "%s\n", res);
                        }else if (strncmp(buf, "Cv", 2) == 0) {
                            int num = va_arg(args, int);
                            int base = va_arg(args, int);
                            char *res = toBase(num, base, 0, &status);

                            fprintf(fptr, "%s\n", res);
                        }else if (strncmp(buf, "CV", 2) == 0) {
                            int num = va_arg(args, int);
                            int base = va_arg(args, int);
                            char *res = toBase(num, base, 1, &status);

                            fprintf(fptr, "%s\n", res);
                        }else if (strncmp(buf, "to", 2) == 0) {
                            char *num = va_arg(args, char*);
                            int base = va_arg(args, int);
                            char *res = toDec(num, base, &status);

                            fprintf(fptr, "%s\n", res);
                        }else if (strncmp(buf, "TO", 2) == 0) {
                            char *num = va_arg(args, char*);
                            int base = va_arg(args, int);
                            char *res = toDec(num, base, &status);

                            fprintf(fptr, "%s\n", res);
                        }else if (strncmp(buf, "mi", 2) == 0) {
                            void *x = va_arg(args, void*);
                            char *res = dumpDumpDumpIt(x, sizeof(int), &status);

                            fprintf(fptr, "%s\n", res);
                        }else if (strncmp(buf, "mu", 2) == 0) {
                            void *x = va_arg(args, void*);
                            char *res = dumpDumpDumpIt(x, sizeof(unsigned int), &status);

                            fprintf(fptr, "%s\n", res);
                        }else if (strncmp(buf, "md", 2) == 0) {
                            void *x = va_arg(args, void*);
                            char *res = dumpDumpDumpIt(x, sizeof(double), &status);

                            fprintf(fptr, "%s\n", res);
                        }else if (strncmp(buf, "mf", 2) == 0) {
                            void *x = va_arg(args, void*);
                            char *res = dumpDumpDumpIt(x, sizeof(float), &status);

                            fprintf(fptr, "%s\n", res);
                        }else {
                            //тут хуйня какая-то выходит
                            fprintf(fptr, "%s", buf);
                        }
                        if (res == NULL) {
                            handleError(status);
                            va_end(args);
                            return status;
                        }
                        if (fprintf(fptr, "%s", res) < 0) {
                            free(res);
                            va_end(args);
                            return -1;
                        }
                        free(res);
                        ptr+=2;
                    } else {
                        charBuf[BUF_SIZE] = {0};
                        size_t j = 0;
                        buf[j++] = '%';
                        while (*ptr && strchr(""))
                    }
                }
            }
        }
    }
