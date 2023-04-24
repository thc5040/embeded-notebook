#include <stdio.h>
int main(void) {
    char str[1024] = "Please enter:";
    fputs(str, stdout);

    fgets(str, 1024, stdin);
    fputs(str, stdout);
    return 0;
}