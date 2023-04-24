#include <iostream>
using namespace std;
int main(void) {
    string str;
    while(getline(cin, str, '\n')) {
        cout << str << endl;
    }
    return 0;
}