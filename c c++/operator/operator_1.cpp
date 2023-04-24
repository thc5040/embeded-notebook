//重载 + - ++ -- == () 这几个运算符
#include <iostream>
using namespace std;

class A
{
public:
    A(int i) {
        num = i;
    }

    int printNum(void) const {
        cout << num << endl;
    }

    int operator+ (const A& a) {
        return this->num + a.num;
    }

    int operator- (const A& a) {
        return this->num - a.num;
    }

    A& operator++ (void) {  // 前置 ++a;
        this->num++;
        return *this;
    }

    A& operator++ (int) {   //后置 a++;
        this->num++;
        return *this;
    }

    A& operator-- (void) {
        this->num--;
        return *this;
    }

    A& operator-- (int) {
        this->num--;
        return *this;
    }

    bool operator== (const A& a) {
        return this->num == a.num;
    }

    void operator() (int n) {
        this->num = n;
    }


private:
    int num;
};

int main(void) {

    A a(1);
    a.printNum();

    ++a;
    a.printNum();

    a++;
    a.printNum();

    a--;
    --a;
    a.printNum();

    a(10);
    a.printNum();

    printf("%d\n", a == 11);

    A b(20);
    printf("%d %d\n", a + b, a-b);

    return 0;
}