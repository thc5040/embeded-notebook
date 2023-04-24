#include <iostream>
#include <fstream>
using namespace std;

int main(void) {

    fstream fs("E:\\technique doc\\embeded-notebook\\c c++\\file\\writeTest.txt", ios::out);

    fs.seekp(0, ios::beg);
    char str[] = "hello world\ni love you\nauthor:thc\n";
    fs.write(str, sizeof(str)-1);

    for(int i=0; i<sizeof(str)-1; i++) {
        fs.put(str[i]);        
    }

    fs.close();
    return 0;
}