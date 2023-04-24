/* 输入流测试 */
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include <string.h>
#include <stdlib.h>
using namespace std;

void print(const vector<string>& strVec) {
    for(string str:strVec) {
        cout << str << "\t";
    }
    cout << endl;
}

/* c++ 使用stringstream，结合getline，非常方便*/
vector<string> split_fun1(const string& str, const char spliter) {
    vector<string> res;
    string line;
    stringstream ss(str);
    while(getline(ss, line, spliter)) {
        if(line.size() > 0) {
            res.push_back(line);
        }
    }
    return res;
}

/* c++ 使用string 的 find substr */
vector<string> split_fun2(string str, const char spliter) {
    vector<string> res;
    //结尾加上一个 spliter
    str.push_back(spliter);
    int pos = str.find(spliter);
    while( pos >= 0) {
        string s = str.substr(0, pos);
        if(s.size() > 0) {
            res.push_back(s);
        }
        str = str.substr(pos+1);
        pos = str.find(spliter);
    }
    return res;
}

/* 使用c语言风格 strtok 进行分割 */
vector<string> split_fun3(string str, const char spliter) {
    vector<string> res;
    char s[1024];
    memcpy(s, str.c_str(), str.size());
    char *p = strtok(s, &spliter);
    while(p) {
        res.push_back(string(p));
        p = strtok(NULL, &spliter);
    }
    return res;
}

int main(void) {

    string str("  hello  huang  tan 3.14 world ");
    char spliter = ' ';

    vector<string> res1 = split_fun1(str, spliter);
    print(res1);

    vector<string> res2 = split_fun2(str, spliter);
    print(res2);    

    vector<string> res3 = split_fun3(str, spliter);
    print(res3);    

    return 0;
}
