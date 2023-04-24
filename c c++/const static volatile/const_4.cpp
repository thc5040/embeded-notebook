#include <iostream>
#include <stdio.h>
using namespace std;

class A {
public:
    A(int n) : num(n) {}
    void print(void) {
        printf("normal function, num:%d\n", num);
    }
    // 类的成员函数如果不会改变类的成员数据时，一般用const修饰这个成员函数
    // const修饰的成员函数，与没有const修饰的成员函数是不同的函数
    void print(void) const {
        printf("const function, num:%d\n", num);
    }
private:
    int num;
};

int main(void) {
    A a1(10);
    a1.print();

    const A a2(20);  //const对象实例只能调用类中的const成员函数
    a2.print();
    return 0;
}