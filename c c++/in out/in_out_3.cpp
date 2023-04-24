#include <stdio.h>
int main(void) {
    char str[1024] = "Please enter: ";
    puts(str);
    
    gets(str);
    puts(str);
    return 0;
}