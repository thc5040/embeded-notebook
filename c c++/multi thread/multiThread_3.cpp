#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

mutex mut;
int sum = 0;

void thread_fun(const int loops) {
    for(int i=0; i<loops; i++) {
        mut.lock();     // lock
        sum++;          // 临界区
        mut.unlock();   // unlock
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