#include <iostream>
using namespace std;

int main(void) {

    int a1 = 10;
    int a2 = 12;

    const int c1 = 1;
    const int c2 = 2;


    const int *p = &c1;     // 指向const的指针 
    // int const *p = &c1;  // 另一种写法

    // *p = 100;            // error 不能用该指针修改常量区内存
    p = &c2;                // ok，指向const的指针可以修改
    p = &a1;                // ok，也可以指向非const变量


    int* const p2 = &a1;    // const指针，该指针不能变 
    // int* const p2 = &c1; // error, 只能指向普通变量
    // p2 = &a2;            // error, 指针不能指向别处
    *p2 = 11;               // ok，可以通过该指针修改指向的内存区， 此时 a1 = 11


    const int* const p3 = &c1;  // 指向const的const指针， 两者的结合



    return 0;
}