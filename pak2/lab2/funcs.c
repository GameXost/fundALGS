#include <string.h>
#include <stdbool.h>
#include "addational.h"


// чекнуть о большую и малую по матану

//a
void *memchr(const void *str, int c, size_t n) {
    if (str == NULL) {
        return NULL;
    }
    const unsigned char *ptr = (const unsigned char*)str;
    unsigned char ch = (unsigned char)c;
    for (size_t i = 0; i<n; i++) {
        if (ptr[i] == ch) {
            return (void*)(ptr+i);
        }
    }
    return NULL;
}

//b
// 1 если 1 > 2;
// -1 если 1 < 2;
//0 если 1 == 2
int memcmp(const void *str1, const void *str2, size_t n) {
    if (str1 == NULL || str2 == NULL) {
        return 0;
    }
    const unsigned char *ptr1 = (const unsigned char*)str1;
    const unsigned char *ptr2 = (const unsigned char*)str2;

    for (size_t i = 0; i < n; i++) {
        if (ptr1[i] != ptr2[i]) {
            return (ptr1[i] > ptr2[i]) ? 1 : -1;
        }
    }
    return 0;
}

//c
void *memcpy(void *dest, const void *src, size_t n) {
    if (dest == NULL || src == NULL) {
        return NULL;
    }
    unsigned char *newDest = (unsigned char*)dest;
    const unsigned char *newSrc = (const unsigned char*)src;

    for (size_t i = 0; i < n; i++) {
        newDest[i] = newSrc[i];
    }
    return (void*)dest;
}


//d
void *memset(void *str, int c, size_t n) {
    if (str == NULL) {
        return NULL;
    }
    unsigned char C = (unsigned char)c;
    unsigned char *ptr = (unsigned char*)str;
    for (size_t i = 0; i < n; i++) {
        ptr[i] = C;
    }
    return str;
}

//e
char *strncat(char *dest, const char *src, size_t n) {
    if (dest == NULL || src == NULL) {
        return NULL;
    }
    char *newDest = dest;
    while (*newDest != '\0') {
        newDest++;
    }

    size_t i = 0;
    for (; i < n && src[i] != '\0'; i++) {
        newDest[i] = src[i];
    }

    newDest[i] = '\0';
    return dest;
}

//f
char *strchr(const char *str, int c) {
    if (str == NULL) {
        return NULL;
    }
    unsigned char C = (unsigned char)c;
    while (*str != '\0') {
        if (*(unsigned char*)str == C) {
            return (char*)str;
        }
        str++;
    }
    if (C == '\0') {
        return (char*)str;
    }
    return NULL;
}

//g
int strncmp(const char *str1, const char *str2, size_t n) {
    if (str1 == NULL || str2 == NULL) {
        return 0;
    }
    if (strlen(str1) < n) {
        n = strlen(str1);
    }
    if (strlen(str2) < n) {
        n = strlen(str2);
    }

    for (size_t i = 0; i < n; i++) {
        if (str1[i] != str2[i]) {
            return (unsigned char)str1[i] - (unsigned char)str2[i];
        }
        if (str1[i] == '\0') {
            return 0;
        }
    }
    return 0;
}

//h
char *strncpy(char *dest, const char *src, size_t n) {
    if (dest == NULL || src == NULL) {
        return NULL;
    }
    char *ptr = dest;
    size_t i = 0;
    for (; i < n && *src != '\0'; i++) {
        *ptr = *src;
        ptr++;
        src++;
    }
    while(i < n) {
        *ptr = '\0';
        i++;
        ptr++;
    }
    return dest;
}
//i
size_t strcspn(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return 0;
    }
    size_t len = 0;

    for (size_t i = 0; str1[i] != '\0';i++) {
        for (size_t j = 0; str2[j] != '\0'; j++) {
            if (str1[i] == str2[j]) {
                return len;
            }
        }
        len++;
    }
    return len;
}


char *strerror(int errnum) {
    const char *errorMsg[] = ERROR_MESSAGES;
    #ifdef __APPLE__
        #define MAX_ERRNO 107
    #elif __linux__
        #define MAX_ERRNO 133
    #endif

    if (errnum < 0 || errnum > MAX_ERRNO) {
        return "unknown";
    }

    const char *msg = errorMsg[errnum];
    return (char*)msg;
}

//k
size_t strlen(const char *str) {
    if (str == NULL) {
        return 0;
    }
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}


//l
char *strpbrk(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return NULL;
    }
    while (*str1 != '\0') {
        for (const char *ptr2 = str2; *ptr2 != '\0'; ptr2++) {
            if (*str1 == *ptr2) {
                return (char *)str1;
            }
        }
        str1++;
    }

    return NULL;
}


//m
//проверить ласт символ
char *strrchr(const char *str, int c) {
    if (str == NULL) {
        return NULL;
    }
    unsigned char C = (unsigned char)c;
    char *res = NULL;
    while (*str != '\0') {
        if (*str == C) {
            res = (char*)str;
        }
        str++;
    }
    if (C == '\0') {
        return (char*)str;
    }

    return (char*)res;
}

//n
char *strstr(const char *haystack, const char *needle) {
    if (haystack == NULL || needle == NULL) {
        return NULL;
    }
    if (*needle == '\0') {
        return (char *)haystack;
    }

    while (*haystack != '\0') {
        const char *hay = haystack;
        const char *nee = needle;

        while (*hay != '\0' && *nee != '\0' && *hay == *nee) {
            hay++;
            nee++;
        }
        if (*nee == '\0') {
            return (char*)haystack;
        }
        haystack++;
    }
    return NULL;
}

int is_delim(const char c, const char *delim) {
    while (*delim != '\0') {
        if (c == *delim) {
            return 1;
        }
        delim++;
    }
    return 0;
}

char *strtok(char *str, const char *delim) {
    if (delim == NULL) {
        return NULL;
    }
    static char *saveStr = NULL;

    if (str == NULL) {
        str = saveStr;
        if (str == NULL) {
            return NULL;
        }
    }
    while (*str !='\0' && is_delim(*str, delim)) {
        str++;
    }

    if (*str == '\0') {
        saveStr = NULL;
        return NULL;
    }

    char *token = str;
    while (*str != '\0' && !is_delim(*str, delim)) {
        str++;
    }
    if (*str == '\0') {
        saveStr = NULL;
    } else {
        *str = '\0';
        saveStr = (++str);
    }
    return token;
}
