## C++多线程

+ 使用标准库 thread 实现多线程，创建完成后子线程即可调度运行
+ join是指阻塞等待这个线程完成
+ detach是线程分离，主线程不需要等待，主线程可以先于子线程退出，而子线程由系统运行时库接管，在后台运行
+ 子线程创建后是joinable状态，必须在子线程结束前使用join或者detach，此时线程变为unjoinable。如果线程析构后还是处于joinable状态，将会调用terminate()，终止整个程序，造成错误

```c++
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
```

## mutex 锁

+ 加锁，cout并不是线程安全的，多个线程抢占同一资源，可能会造成意外的后果

不加锁的话：

```c++
#include <iostream>
#include <thread>
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
```

运行结果可能为如下，每次都不一样

```
sum: 1010448
sum: 1000112
...
```

但我们本意显然是让sum加上两轮，加锁后的程序为：

```c++
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
```

此时不会存在数据竞争，打印的结果一定为：

```
sum: 2000000
```

+ 利用unique_mutex进行mutex的管理，自动加锁、解锁

```c++
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
```

## atomic 原子操作

+ 原子操作 atomic, 也可以用原子操作，以更低的开销保证线程安全。原子操作将读-修改-写绑定在一起，要么不执行，要么读-修改-写三者一起执行完，从而避免数据竞争

```c++
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
```

## consition_variable 条件变量

+ 条件变量是一种线程间同步的机制，一个线程等待某个 “条件” 而阻塞，另一个线程使 "条件" 成立，给出信号，从而唤醒阻塞的线程
+ 条件变量经常用于生产者-消费者模式中（设计模式的一种），如下例子。生产者线程不断产出，push到队列中；消费者不断从队列中取出。其中要解决队列空 或 满这两种特殊情况，就要用到条件变量。当满了，生产者需要等待一个条件变量，也就是消费者取出后，给生产者发送一个条件。空了也同理。
+ 为什么此时要用条件变量呢？如果没有条件变量，解决的方法很可能是用while+mutex去不断地查看队列是满还是空，这样太浪费性能
+ 条件变量要结合锁mutex使用，刚开始用一个unique_lock<mutex lck 进行lock，但是在cond.wait(lck)的时候会自动unlock，此时阻塞。在得到一个条件变量后，wait出来，又会自动地lock上，这样就解决了que临界区访问的问题

```c++
#include <iostream>
#include <thread>
#include <condition_variable>
#include <chrono>
#include <queue>
using namespace std;

mutex mtx;
condition_variable cond_not_full;
condition_variable cond_not_empty;
queue<int> que;             // 数据队列
const int queMaxNum = 10;   // 数据队列最大项目数

// 生产者
void producer() {
  int cnt = 0;
  while(1) {
    this_thread::sleep_for(chrono::seconds(3));   // 间隔一定的时间生产
    unique_lock<mutex> lck(mtx); 
    while(que.size() == queMaxNum) {  // 满了不能生产
      cout << "queue full" << endl;
      cond_not_full.wait(lck);
    }
    cout << "thread id: " << this_thread::get_id() << " produce cnt:" << cnt << endl;
    que.push(cnt);    // 生产
    cond_not_empty.notify_one();
    cnt++;
  }
}

void consumer() {
  while(1) {
    this_thread::sleep_for(chrono::seconds(1));   // 间隔一定的时间消费
    unique_lock<mutex> lck(mtx);
    while(que.size() == 0) {    // 空了不能消费
      cout << "que empty" << endl;
      cond_not_empty.wait(lck);
    }
    int cnt = que.front();
    que.pop();    // 消费
    cout << "thread id: " << this_thread::get_id() << " consumer cnt:" << cnt << endl;
    cond_not_full.notify_one();
  }
}

int main(void) {

  thread pro(producer);
  thread con(consumer);

  pro.join();
  con.join();

  return 0;
}
```



