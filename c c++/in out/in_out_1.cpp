#include <stdio.h>
// 4 3.15 hellword
int main(void) {
    int a;
    float f;
    char str[1024];
    scanf("%d %f %s", &a, &f, str);
    printf("%d %f %s\n", a, f, str);
    return 0;
}