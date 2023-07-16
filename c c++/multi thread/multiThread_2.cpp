#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

int sum = 0;

void thread_fun(const int loops) {
    for(int i=0; i<loops; i++) {
        sum++;
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