#include <iostream>
#include <fstream>
using namespace std;

int main(void) {

    fstream fs("E:\\technique doc\\embeded-notebook\\c c++\\file\\readTest.txt", ios::in);  //已经open, 或者使用open函数

    string line;
    while(getline(fs, line, '\0')) {
        cout << line << endl;
    }

    printf("\n\n");
    fs.clear();     //读到EOF, 清空流状态
    fs.seekg(0, ios::beg);  //设置光标到开头为止

    char c;
    while( fs.get(c) ) {
        cout << c;
    }

    //获取文件字节数
    fs.clear();
    fs.seekg(0, ios::end);
    int end = fs.tellg();
    printf("\n\nfile bytes:%d\n", end);

    fs.close();
    return 0;
}