## c语言输入输出 scanf printf

这是两种最常见的方式，当时scanf遇到空格就断开

```c
#include <stdio.h>
// 4 3.15 hellword
int main(void) {
    int a;
    float f;
    char str[1024];
    scanf("%d %f %s", &a, &f, str);
    printf("%d %f %s\n", a, f, str);
    return 0;
}
```

输入 输出测试：

```
4 3.15 hellword
4 3.150000 hellword
```

## c语言 getchar putchar, gets puts

getchar putchar 每次处理一个字符

```c
#include <stdio.h>
int main(void) {
    char c;
    while(1) {
        c = getchar();
        putchar(c);
    }
    return 0;
}
```

gets puts, 每次处理一个字符数组

```c
#include <stdio.h>
int main(void) {
    char str[1024] = "Please enter: ";
    puts(str);
    
    gets(str);
    puts(str);
    return 0;
}
```

## c语言 fgetc fputc, fgets, fputs

标准输入输出其实是个打开文件流, stdin, stdout，利用这两个FILE* 进行文件读写

fgetc, fputc

```c
#include <stdio.h>
int main(void) {
    char c;
    while(c = fgetc(stdin)) {
        fputc(c, stdout);
    }
    return 0;
}
```

fgets, fputs

```c
#include <stdio.h>
int main(void) {
    char str[1024] = "Please enter:";
    fputs(str, stdout);

    fgets(str, 1024, stdin);
    fputs(str, stdout);
    return 0;
}
```

## c++  输入输出

+ cin cout简单测试， cin遇到空格就停止了
+ cin是一个istream, cout是一个ostream，因此其用法可以参考这两个类

```C++
#include <iostream>
using namespace std;
int main(void) {
    string str; 
    cin >> str;     //输入，直到遇到空格
    cout << str;
    return 0;
}
```

cin.getline

```c++
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
```

std::getline， 从流中获取一行字符串，这个也可以读取file

```c++
#include <iostream>
using namespace std;
int main(void) {
    string str;
    while(getline(cin, str, '\n')) {
        cout << str << endl;
    }
    return 0;
}
```





