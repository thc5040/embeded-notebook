## 1 const 常量

使用const修饰的变量，意为常量，不能再被修改

### 1.1 基本用法 const常变量

+ 在项目、功能、对象中，有些参数是固定的，或者不希望这个变量被修改，那么就可以用const修饰

+ 修饰函数参数，指示在这个函数内不能修改这个变量，让程序更加健壮

```c++
#include <iostream>
using namespace std;

const float PI = 3.1415926f;  // const常量

// 在这个函数体内，para不能被修改，否则编译器会报错
void func(int a, const int para) {
    // 函数代码
}

int main(void) {
    cout << "PI: " << PI << endl;
    return 0;
}
```

### 1.2 const与define

在上面这个定义常量PI的例子中，经常也使用#define来实现。当用于基本的常变量用法时，两者的区别有：

+ const修饰的是一个真正的有数据类型的变量，只是这个变量不能被修改，在编译、运行阶段作用。比如const常变量可以取地址操作、全局的const常变量位于程序的数据段、可以debug调试看到这个常变量的值
+ define是宏定义，在预编译阶段进行简单的字符替换，给出的是立即数/常字符串，这些常量存储在代码段
+ const常变量在程序运行过程只有一份拷贝，而#define每用一次就会在代码段多出一份，const可以节省空间
+ const常变量，编译器会对其进行类型安全检查，更可靠健壮，而define只是单纯的字符替换
+ 由于const常变量是存在数据段，而define存储在代码段。所以在单片机/嵌入式中，还是会经常用#define来定义常量，因为单片机中RAM的资源远比flash要小的多，宝贵的多，单片机在启动的时候会把整个数据段搬到RAM，如果代码中有很多const常变量的话，那么RAM会很吃紧，而#define的方式放在代码区放在flash中，节省RAM。
+ const也还有其他很多其他作用，define也还有很多其他作用

### 1.3 const与指针

+ 指向const的指针，所指向的内存区不能修改，至少不能用这个指针修改

+ const指针，指针的值不能改变了

+ 指向const的const指针，是上面两者的结合

```c++
#include <iostream>
using namespace std;

int main(void) {
    int a1 = 10;
    int a2 = 12;
    const int c1 = 1;
    const int c2 = 2;

    const int *p = &c1;     // 指向const的指针 
    // int const *p = &c1;  // 另一种写法
    // *p = 100;            // error 不能用该指针修改常量区内存
    p = &c2;                // ok，指向const的指针可以修改
    p = &a1;                // ok，也可以指向非const变量

    int* const p2 = &a1;    // const指针，该指针不能变 
    // int* const p2 = &c1; // error, 只能指向普通变量
    // p2 = &a2;            // error, 指针不能指向别处
    *p2 = 11;               // ok，可以通过该指针修改指向的内存区， 此时 a1 = 11

    const int* const p3 = &c1;  // 指向const的const指针， 两者的结合

    return 0;
}
```

###1.4 const + 引用 + 函数参数

这是c++常用的一种传参方式，通过引用可以提高传参效率，但不希望该函数改变外面定义的变量，用const限定

```c++
#include <iostream>
using namespace std;

class A {
public:
    int num;
    A(int n) : num(n) {}
};

void print_num(const A& a) {
    cout << a.num << endl;
}

int main(void) {
    A a(10);
    print_num(a);
    return 0;
}
```

### 1.5 const + 类 + 函数

+ c++中，类的成员函数如果不会改变类的成员数据时，一般用const修饰这个成员函数
+ const修饰的成员函数，与没有const修饰的成员函数是不同的函数
+ const对象实例只能调用类中的const成员函数

```c++
#include <iostream>
using namespace std;

class A {
public:
    A(int n) : num(n) {}
    void print(void) {
        printf("normal function, num:%d\n", num);
    }
    // 类的成员函数如果不会改变类的成员数据时，一般用const修饰这个成员函数
    // const修饰的成员函数，与没有const修饰的成员函数是不同的函数
    void print(void) const {
        printf("const function, num:%d\n", num);
    }
private:
    int num;
};

int main(void) {
    A a1(10);
    a1.print();

    const A a2(20);  //const对象实例只能调用类中的const成员函数
    a2.print();
    return 0;
}
```

输出：

```
normal function, num:10
const function, num:20
```

## 2 static 静态

+ 有static变量, static函数两种，常用来限定作用域

```c
#include <iostream>
using namespace std;

static int a = 1;           // 这个变量限定在file1.c文件中使用

static void print(void) {	    // 这个函数限定在file1.c文件中使用
    printf("a:%d", a);
}

int main(void) {
    print();
    return 0;
}
```

+ 函数内的static变量只有一份，存放在全局数据段中，只会定义一次，每次调用该函数修改static变量都会共享

```c
#include <iostream>
using namespace std;

void add_print(void) {
    static int val = 0;
    val++;
    printf("val:%d\n", val);
}

int main(void) {
    for(int i=0; i<3; i++) {
        add_print();
    }
    return 0;
}
```

输出：

```
val:1
val:2
val:3
```

+ c++类中，static数据成员需要再外部定义，在类中只是一个声明

+ c++类中，static成员函数不依赖对象实例就可以调用，建议用类名::成员函数的方式调用类中的static成员函数

```c++
#include <iostream>
using namespace std;

class A {
public:
    //  这只是一个声明，必须要在外部定义。并且该类的所有对象实例维护同一份数据拷贝
    static int val; 
    // static成员函数不依赖对象实例就可以调用，建议用类名::成员函数的方式调用类中的static成员函数
    static void add_print(void) { 
        val++;
        printf("val:%d\n", val);
    }
};

int A::val = 0; // 实际的定义

int main(void) {
    for(int i=0; i<3; i++) {
        A::add_print();
    }
    return 0;
}
```

输出：

```
val:1
val:2
val:3
```

## 3 volatile 易变

+ 被volatile修饰的变量，是易变的，编译器不能对这个变量做任何假设去优化程序，每次使用这个变量都要从内存中重新获取，而不是寄存器中直接拿。编译器不会对volatile修饰的变量相关操作进行优化。
+ 与硬件寄存器相关的指针一般都要用volatile，比如STM32的某些外设库的代码就包含了大量的volatile，因为这些硬件寄存器的值除了你代码可以设置之外，由于外部变化，硬件自己也可以改变这个寄存器的值，所以每次都要从该内存/硬件寄存器中获取这个值

例如以下这段程序，对一个外设进行初始化，这个外设的某个寄存器端口为 0xff800000。

如果没有volatiel，编译器可能会进行代码优化，直接执行*output=0x88, 不会执行前面的赋值内容，但是前面的赋值内容对硬件寄存器来说是有意义的，那么就会出错。所以此时必须用volatile

```c
volatile unsigned int *output = (unsigned int *)0xff800000U;	//定义一个IO端口；
void init(void)
{
	*output = 0x55;
    *output = 0x66;
    *output = 0x88;
}
```
