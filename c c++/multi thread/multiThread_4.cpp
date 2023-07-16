#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

mutex mut;
int sum = 0;

void thread_fun(const int loops) {
    unique_lock<mutex> lck(mut);    // 创建的时候自动加锁，析构的时候解锁，防止有时候忘记解锁出错
    for(int i=0; i<loops; i++) {
        sum++;          // 临界区
    }
}

int main(void) {

    thread t1(thread_fun, 1000000);
    thread t2(thread_fun, 1000000);

    t1.join();
    t2.join();

    cout << "sum: " << sum << endl;

    return 0;
}