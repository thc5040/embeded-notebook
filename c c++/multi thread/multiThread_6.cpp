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

// 消费者
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