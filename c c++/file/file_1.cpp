#include <stdio.h>
#include <stdlib.h>
int main(void) {
    FILE* fp = fopen("E:\\technique doc\\embeded-notebook\\c c++\\file\\readTest.txt", "r+");
    char c;
    while( (c = fgetc(fp)) != EOF) {    //使用fgetc 每次读取文件的一个字符
        printf("%c", c);
    }

    printf("\n\n");
    fseek(fp, 0, 0);    //将光标移动到文件头部
    
    char str[1024];
    while( fgets(str, 1024, fp) > 0) {  //每次读取一行，最后的换行符也读取进来
        printf("%s", str);
    }

    printf("\n\n");
    fseek(fp, 0, 0);
    while( fscanf(fp, "%s", str) > 0) {  // fscanf 遇到空格就停止了
        printf("%s\n", str);
    }

    fclose(fp);
    return 0;
}