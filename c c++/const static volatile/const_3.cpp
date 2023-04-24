#include <iostream>
using namespace std;

class A {
public:
    int num;
    A(int n) : num(n) {}
};

void print_num(const A& a) {
    cout << a.num << endl;
}

int main(void) {
    A a(10);
    print_num(a);
    return 0;
}