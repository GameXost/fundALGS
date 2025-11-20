#include <stdio.h>


int main() {
    FILE *file = NULL;
    char buf1[4096];
    char buf2[4096];
    char buf3[4096];
    char *pb = buf1, ch , c = 0;
    int cs = 0;
    //file -норм открылся
    while (!feof(file)) {
        ch = fgetc(file);
        if (isalpha(ch)) {
            *pb++ = toupper(ch);
        } else if (isalpha(c) && ch != ';') {
            *pb = 0;
            if (++cs%2 == 1) {
                pb = buf2;
            }else {
                pb = buf3;
            }
        }else if (ch == ';'){
            *pb = 0;
            cs = 0;
            pb = buf1;
            foo(buf1, buf2, buf3);
        }

    }
}