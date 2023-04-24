#include <stdio.h>
int main(void) {
    char c;
    while(c = fgetc(stdin)) {
        fputc(c, stdout);
    }
    return 0;
}