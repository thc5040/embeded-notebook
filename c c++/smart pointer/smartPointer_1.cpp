#include <iostream>
#include <memory>
#include <vector>
using namespace std;

//普通指针需要自己回收内存
void useNormalPointer(void) {
    string *s = new string("hello world");
    cout << "useNormalPointer: " << *s << endl;
    delete s;

    vector<int> *v = new vector<int>(10);
    cout << "v->capacity: " << v->capacity() << endl;
    delete v;

    int *p = new int[10];   //数组的动态内存分配
    p[0] = 10;
    delete[] p;
}

/* 智能指针会在析构函数自动回收内存 */
void useSmartPointer(void) {
    unique_ptr<string> s(new string("hello world"));
    cout << "useSmartPointer: " << *s << endl;

    unique_ptr<vector<int>> v(new vector<int>(10));
    cout << "v->capacity: " << v->capacity() << endl;

    unique_ptr<int[]> p(new int[10]);   //int数组的指针指针定义
    p[0] = 100;
}

int main(void) {
    useNormalPointer();
    useSmartPointer();
    return 0;
}