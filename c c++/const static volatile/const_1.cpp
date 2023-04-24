#include <iostream>
using namespace std;

const float PI = 3.1415926f;  // const常量

// 在这个函数体内，para不能被修改，否则编译器会报错
void func(int a, const int para) {
    // 函数代码
}

int main(void) {

    cout << "PI: " << PI << endl;

    return 0;
}