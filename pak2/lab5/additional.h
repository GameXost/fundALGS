#pragma once
#include <stdio.h>
#define PATH_MAX 4096

typedef enum {
    OK,
    INVALID_INPUT,
    EQUAL_FILE_PATHS,
    INVALID_FILE_NAME,
    MEMORY_ALLOCATION,
    END_OF_INPUT
}StatusCode;

int readPath(char **res);
int readFull(FILE *input, char **res);
int handleString(char *str, FILE *output);
int processFile(char *inputPath, char *outputPath);
void handleError(StatusCode status);
int fileValidate(char *path1, char *path2);
