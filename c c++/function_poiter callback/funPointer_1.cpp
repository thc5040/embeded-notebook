#include <iostream>
using namespace std;

//func1是一个函数指针，有一个float输入参数，无输出参数
void (*func1)(float a);

//一种新的类型，该类型是函数指针，有2个int输入参数和1个int返回参数
typedef void (*funPointer)(int, int);

struct Student
{
    int num1;
    int num2;
    funPointer add;
}stu1;

void func_printf_float(float f) {
    printf("printf flaot : %f\n", f);
}

void func_printf_add(int a, int b) {
    printf("a+b:%d\n", a+b);
}

int main(void) {

    func1 = func_printf_float;
    func1(3.14);
    (*func1)(2.17); //也可以用取指针的方式调用函数

    stu1.add = func_printf_add;
    stu1.add(1, 2);

    return 0;
}