#include <iostream>
using namespace std;

static int a = 1;           // 这个变量限定在file1.c文件中使用

static void print(void) {	    // 这个函数限定在file1.c文件中使用
    printf("a:%d", a);
}

int main(void) {
    print();
    return 0;
}