#include <iostream>
#include <thread>
#include <atomic>
using namespace std;

atomic<int> sum(0);

void thread_fun(const int loops) {
    for(int i=0; i<loops; i++) {
        sum++;
    }
}

int main(void) {

    sum.store(0);   // store 可以设置对应类型的实体

    thread t1(thread_fun, 100000);
    thread t2(thread_fun, 100000);

    t1.join();
    t2.join();

    cout << sum.load() << endl;   // load 得到对应类型的实体

    return 0;
}