#include <stdio.h>

#include "addational.h"

int main() {
    //a
    const char *str_a = "hello world";
    void *res_a = memchr(str_a, 'w', 11);

    printf("memchr: %s\n", res_a);

    //b
    const char *str1_b = "abc";
    const char *str2_b = "abd";
    int res_b = memcmp(str1_b, str2_b, 3);
    printf("memcmp: %d\n", res_b);

    //c
    char dest_c[10];
    memcpy(dest_c, "11hellbro", 5);
    dest_c[5] = '\0';
    printf("memcpy: %s\n", dest_c);

    //d
    char str_d[10];
    memset(str_d, 'A', 5);
    str_d[5] = '\0';
    printf("memset: %s\n", str_d);

    //e
    char dest_e[20] = "hello";
    strncat(dest_e, "world", 3);
    printf("strncat: %s\n", dest_e);

    //f
    const char *str_f = "hello";
    char *res_f = strchr(str_f, 'l');
    printf("strchr: %s\n", res_f);

    //g
    int res_g = strncmp("abc", "abd", 3);
    printf("strncmp: %d\n", res_g);

    //h
    char dest_h[10];
    strncpy(dest_h, "hello world", 5);
    dest_h[5] = '\0';
    printf("strncpy: %s\n", dest_h);

    //i
    size_t res_i = strcspn("hello world", "l");
    printf("strcspn: %zu\n", res_i);

    //j
    char *res_j = strerror(0);
    printf("strerror: %s\n", res_j);

    //k
    size_t res_k = strlen("");
    printf("strlen: %zu\n", res_k);

    //l
    char *res_l = strpbrk("hello world", "w");
    printf("strpbrk: %s\n", res_l ? res_l : "NULL");

    //m
    char *res_m = strrchr("hello", 'l');
    printf("strrchr: %s\n", res_m ? res_m : "NULL");

    //n
    char *res_n = strstr("hello world", "world");
    printf("strstr: %s\n", res_n ? res_n : "NULL");

    //o
    char str_o[] = "hello,world";
    char *token = strtok(str_o, ",");
    printf("strtok first: %s\n", token);
    token = strtok(NULL, ",");
    printf("strtok second: %s\n", token);

    return 0;
}