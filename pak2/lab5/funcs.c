#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "additional.h"



int readPath(char **res){
    int c;
    size_t cap = 64;
    size_t len = 0;
    char *buff = (char*)malloc(cap);
    if (buff == NULL) {
        return MEMORY_ALLOCATION;
    }



    while ((c = getchar()) != '\n' && c != EOF) {
        if (len + 1 >= cap) {
            cap *= 2;
            char *temp = (char*)realloc(buff, cap);
            if (temp == NULL) {
                free(buff);
                return MEMORY_ALLOCATION;
            }
            buff = temp;
        }

        buff[len++] = (char)c;
    }
    if (c == EOF && len == 0) {
        free(buff);
        return END_OF_INPUT;
    }
    buff[len] = '\0';
    *res = buff;
    return OK;

}

int readFull(FILE *input, char **res) {
    size_t cap = 4096;
    size_t len = 0;

    char *str = (char*)malloc(cap);
    if (str == NULL) {
        return MEMORY_ALLOCATION;
    }
    while (true) {
        if (fgets(str + len, cap - len, input) == NULL) {
            if (len == 0) {
                free(str);
                return END_OF_INPUT;
            }
            break;
        }
        len = strlen(str);
        if (len > 0 && str[len -1 ] == '\n') {
            str[len - 1] = '\0';
            break;
        }

        if (len < cap - 1) {
            break;
        }
        cap *= 2;
        char *temp = (char*)realloc(str, cap);
        if (temp == NULL){
            free(str);
            return MEMORY_ALLOCATION;
        }
        str = temp;
    }
    *res = str;
    return OK;
}


void checkPrint(FILE *output, char **words, size_t cntWords, size_t lenStr) {
    if (cntWords == 0) {
        return;
    }
    if (cntWords == 1) {
        fprintf(output, "%s\n", words[0]);
        return;
    }

    size_t gaps = cntWords - 1;
    size_t spaceCnt = 80 - lenStr;
    size_t spacePerGap = spaceCnt / gaps;
    size_t rest = spaceCnt % gaps;

    for (size_t i = 0; i < cntWords; i++) {
        fprintf(output, "%s", words[i]);
        if (i < gaps) {
            for (size_t g = 0; g < spacePerGap; g++) {
                fputc(' ', output);
            }
            if (rest > 0) {
                fputc(' ', output);
                rest--;
            }
        }
    }
    fprintf(output, "\n");
}

int handleString(char *str, FILE *output) {
    char *ptr = strdup(str);
    if (ptr == NULL) {
        return MEMORY_ALLOCATION;
    }

    char **words = NULL;
    size_t cntWords = 0;
    size_t lenStr = 0;
    char *word = strtok(ptr,  " ");
    while (word != NULL) {
        if (strlen(word) == 0) {
            word = strtok(NULL, " ");
            continue;
        }

        if (strlen(word) > 80) {
            if (cntWords > 0) {

                checkPrint(output, words, cntWords, lenStr);
                free(words);
                words = NULL;
                cntWords = 0;
                lenStr = 0;
            }
            size_t curWordLen = 0;
            while (curWordLen < strlen(word)) {
                fprintf(output, "%.80s\n", word + curWordLen);
                curWordLen += 80;
            }
            word = strtok(NULL, " ");
            continue;
        }
        if (cntWords > 0 && (lenStr + cntWords + strlen(word) > 80)) {
            checkPrint(output, words, cntWords, lenStr);
            free(words);
            words = NULL;
            cntWords = 0;
            lenStr = 0;
        }
        char **temp = (char**)realloc(words, (cntWords + 1) * sizeof(char*));
        if (temp == NULL) {
            free(ptr);
            if (words) {
                free(words);
            }
            return MEMORY_ALLOCATION;
        }
        words = temp;
        words[cntWords] = word;
        cntWords++;
        lenStr += strlen(word);
        word = strtok(NULL, " ");
    }
    if (cntWords > 0) {
        checkPrint(output, words, cntWords, lenStr);
        free(words);
        words = NULL;
        cntWords = 0;
        lenStr = 0;
    }
    free(ptr);
    return OK;

}

int processFile(char *inputPath, char *outputPath) {
    FILE *input = fopen(inputPath, "r");
    if (input == NULL) {
        return INVALID_FILE_NAME;
    }

    FILE *output = fopen(outputPath, "w");
    if (output == NULL) {
        fclose(input);
        return INVALID_FILE_NAME;
    }
    char *buf = NULL;
    StatusCode status;
    while (( status = readFull(input, &buf)) == OK) {
        status = handleString(buf, output);
        if (status != OK) {
            free(buf);
            fclose(input);
            fclose(output);
            return status;
        }
        free(buf);
        buf = NULL;
    }
    if (status != END_OF_INPUT) {
        fclose(input);
        fclose(output);
        return status;
    }
    fclose(input);
    fclose(output);
    return OK;


}