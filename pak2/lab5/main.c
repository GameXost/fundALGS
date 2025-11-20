#include "additional.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    bool flag = true;
    while (flag) {
        printf("enter first fileName: \n");
        char *path1 = NULL;
        StatusCode status = readPath(&path1);
        if (status != OK) {
            handleError(status);
            free(path1);
            if (status == END_OF_INPUT) {
                printf("the end bruh\n");
                flag = false;
                break;
            }
            continue;
        }
        if (strcmp(path1, "exit") == 0 || strcmp(path1, "") == 0) {
            free(path1);
            printf("the end of the program\n");
            break;
        }
        printf("enter second fileName: \n");
        char *path2 = NULL;
        status = readPath(&path2);
        if (status != OK) {
            handleError(status);
            free(path1);
            free(path2);
            if (status == END_OF_INPUT) {
                printf("the end bruh\n");
                flag = false;
            }
            continue;
        }

        status = fileValidate(path1, path2);
        if (status != OK) {
            handleError(status);
            free(path1);
            free(path2);
            continue;
        }

        status = processFile(path1, path2);
        if (status != OK) {
            handleError(status);
            free(path1);
            free(path2);
            return status;
        }

        printf("%s\n%s\n", path1, path2);
        free(path1);
        free(path2);
    }
}


