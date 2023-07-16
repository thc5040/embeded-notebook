#include <iostream>
#include <thread>
#include <chrono>  // Time lib
using namespace std;

void t1_fun(int sleepTime) {

    thread::id tid = this_thread::get_id();     // 获取当前线程id
    cout << "this_thread id:" << tid << endl; 

    this_thread::sleep_for(chrono::seconds(sleepTime)); // 线程休眠
}

int main(void) {
    thread::id tid = this_thread::get_id();     // 获取当前线程id
    cout << "this_thread id:" << tid << endl;     

    thread t1(t1_fun, 3);
    t1.join();      // 等待线程t1执行完后，主线程再继续执行
    // t1.detach();    // 线程分离，t1单独调度

    for(int i=0; i<3; i++) {
        cout << "thread " << tid << " sleep..." << endl;
        this_thread::sleep_for(chrono::seconds(1)); // 线程休眠1s
    }
    return 0;
}