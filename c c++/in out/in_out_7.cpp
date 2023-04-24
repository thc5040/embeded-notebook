#include <iostream>
using namespace std;
int main(void) {
    char s[1024];
    cin.getline(s, 1024);   //获取一行

    int cnt = cin.gcount(); //读取到的字符数
    cout << "cin get count: " << cnt << endl;

    cout << s << endl;
    return 0;
}