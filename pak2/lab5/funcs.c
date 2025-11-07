#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PATH_MAX 4096

typedef enum {
    OK,
    INVALID_INPUT,
    EQUAL_FILE_PATHS,
    INVALID_FILE_NAME,
    MEMORY_ALLOCATION,
    END_OF_INPUT
}StatusCode;

void handleError(StatusCode status) {
    switch (status) {
        case OK:
            printf("everything is fine\n");
            break;
        case INVALID_INPUT:
            printf("shit here what you inserted bruh\n");
            break;
        case EQUAL_FILE_PATHS:
            printf("bruh dont try to overwrite the file nigga\n");
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
                size_t gaps = cntWords - 1;
                if (gaps > 0) {
                    size_t spacesCnt = 80 - lenStr;
                    size_t spacePerGap = spacesCnt / gaps;
                    size_t rest = spacesCnt % gaps;
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
                } else {
                    fprintf(output, "%s\n", words[0]);
                }
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
        for (size_t i = 0; i < cntWords; i++) {
            fprintf(output, "%s%s", words[i], (i < cntWords - 1) ? " ":"");
        }
        fprintf(output, "\n");
        free(words);
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
    printf("the end gahah\n");
}