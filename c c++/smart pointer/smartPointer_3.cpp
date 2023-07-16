#include <iostream>
#include <memory>
#include <vector>
using namespace std;
int main(void) {
    shared_ptr<int> p1 = make_shared<int>(10);  // int* 
    cout << *p1 << endl;

    auto p2 = make_shared<string>("hello world");   // *string
    cout << *p2 << endl;

    auto p3 = make_shared<vector<int>>();   // *vector
    p3->push_back(100);
    cout << (*p3)[0] << endl;

    return 0;
}