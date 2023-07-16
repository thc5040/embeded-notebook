#include <iostream>
#include <memory>
using namespace std;

void fun(const shared_ptr<string> s) {
    cout << "s.user_count: " << s.use_count() << endl;
}

int main(void) {

    shared_ptr<string> s(new string("hello world"));
    cout << "s.user_count: " << s.use_count() << endl;

    shared_ptr<string> s2 = s;  //此时s s2共享的是同一块内存 计数+1
    cout << "s.user_count: " << s.use_count() << endl;

    fun(s); //进入函数内计数+1, 出来后局部变量销毁，调用析构，计数-1
    cout << "s.user_count: " << s.use_count() << endl;

    //手动销毁该智能指针 计数-1
    s2.reset();
    cout << "s.user_count: " << s.use_count() << endl;
    
    //重新赋值，计数+1
    s2 = s;
    cout << "s.user_count: " << s.use_count() << endl;

    return 0;
}