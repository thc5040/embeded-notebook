#include <stdio.h>
int main(void) {
    FILE* fp = fopen("E:\\technique doc\\embeded-notebook\\c c++\\file\\test.bin", "rwb+");
    fseek(fp, 0, 0);

    int array[] = {1, 2, 3, 6, 9};
    fwrite((char*)array, sizeof(int), sizeof(array)/sizeof(int), fp);

    fpos_t fpos;
    fgetpos(fp, &fpos);         //获取当前光标位置
    printf("fpos:%d\n", fpos);

    int array2[10];
    fseek(fp, 0, 0);

    fread(array2, sizeof(int), sizeof(array)/sizeof(int), fp);      //再读取数据
    for(int i=0; i<sizeof(array)/sizeof(int); i++) {
        printf("%d\t", array2[i]);
    }

    fclose(fp);
    return 0;
}