#include <stdio.h>
#include <stdlib.h>
int main(void) {
    FILE* fp = fopen("E:\\technique doc\\embeded-notebook\\c c++\\file\\writeTest.txt", "w+");
    char str[1024] = "hello world\ni love you\nautor:thc\n";
    fseek(fp, 0, 0);            //设置光标位置为0
    fpos_t fpos;
    fgetpos(fp, &fpos);         //获取当前光标位置
    printf("fpos:%d\n", fpos);

    for(int i=0; str[i]!=0; i++) {
        fputc(str[i], fp);
    }
    
    fputs(str, fp);

    fprintf(fp, "%s", str);

    fgetpos(fp, &fpos);
    printf("fpos:%d\n", fpos);
    
    fclose(fp);
    return 0;
}