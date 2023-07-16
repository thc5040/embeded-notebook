#include <iostream>
#include <functional>
using namespace std;

double divide(double x, double y) {
    return x/y;
}

class A {
public:
    double sub(double x, double y) {
        return x - y;
    }
    int data = 0;
};

int main(void) {

    auto fun1 = bind(&divide, 10, 3);   // bind的arg参数顺序是 函数divide的参数顺序
    cout << fun1() << endl;     // 减少到没有参数 10/3   输出 3.3333

    auto fun2 = bind(&divide, 10, placeholders::_1);
    cout << fun2(3) << endl;    // 固定了一个参数 x=10， 这里调用是 10/3  x=10, y=3  输出3.3333

    auto fun3 = bind(&divide, placeholders::_2, placeholders::_1);
    cout << fun3(10, 3) << endl;        // 这里调换了参数位置 x=3 y=10  3/10 输出0.3333

    A a;
    // 绑定类的成员函数
    auto bound_member_fun = bind(&A::sub, &a, placeholders::_1, placeholders::_2);
    cout << bound_member_fun(10, 1) << endl;
    // 绑定类的成员数据
    auto bound_menber_data = bind(&A::data, &a);
    cout << bound_menber_data() << endl;        // 输出 0
    a.data = 10;
    cout << bound_menber_data() << endl;        // 输出 10

    return 0;
}