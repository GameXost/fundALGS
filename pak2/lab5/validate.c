#include "additional.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
        default:
            printf("wtf???\n");
    }
}


int fileValidate(char *path1, char *path2) {
    char pathReal1[PATH_MAX];
    char pathReal2[PATH_MAX];
    if (realpath(path1, pathReal1) == NULL) {
        return INVALID_FILE_NAME;
    }

    if (realpath(path2, pathReal2) == NULL) {
        if (path2[0] == '/'){
            strncpy(pathReal2, path2, PATH_MAX-1);
            pathReal2[PATH_MAX-1] = '\0';
        } else {
            if (getcwd(pathReal2, PATH_MAX) == NULL) {
                return INVALID_FILE_NAME;
            }
            size_t len = strlen(pathReal2);
            if (len + strlen(path2) + 2 > PATH_MAX) {
                return INVALID_FILE_NAME;
            }
            if (pathReal2[len-1] != '/') {
                pathReal2[len++] = '/';
            }
            strcpy(pathReal2 + len, path2);
        }
    }

    if (strcmp(pathReal1, pathReal2) == 0) {
        return EQUAL_FILE_PATHS;
    }
    return OK;
}
