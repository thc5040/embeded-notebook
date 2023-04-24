#include <iostream>
using namespace std;

class A {
public:
    //  这只是一个声明，必须要在外部定义。并且该类的所有对象实例维护同一份数据拷贝
    static int val; 
    // static成员函数不依赖对象实例就可以调用，建议用类名::成员函数的方式调用类中的static成员函数
    static void add_print(void) { 
        val++;
        printf("val:%d\n", val);
    }
};

int A::val = 0; // 实际的定义

int main(void) {
    for(int i=0; i<3; i++) {
        A::add_print();
    }
    return 0;
}