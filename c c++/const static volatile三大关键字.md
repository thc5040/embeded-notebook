## 1 const 常量

使用const修饰的变量，意为常量，不能再被修改

### 1.1 基本用法 const常变量

+ 在项目、功能、对象中，有些参数是固定的，或者不希望这个变量被修改，那么就可以用const修饰

```c++
// file.cpp
const float PI = 3.1415926
```

+ 修饰函数参数，指示在这个函数内不能修改这个变量，让程序更加健壮

```c++
// 在这个函数体内，para不能被修改，否则编译器会报错
void func(int a, const int para) {
    // 函数代码
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

```c++
int a = 10;
const int c1 = 1， c2 = 2;

const int *p = &c1;		// 指向const的指针
// int const *p = *c1;  另一种写法

// *p = 2;  error,错误写法，指向常量的指针，常量是不可以修改的
p = &c2;	 // 正确，这个指针还是可以改变的

p = &a;	// 正确，指向常量的指针也可以指向普通变量, 但不能通过这个指针修改
```

+ const指针，指针的值不能改变了

```c++
int a = 10, b = 20;
const int c1 = 1;

int* const p = &a;	// const指针
// int* const p = &c1;  // error, 必须要用指向const的指针

*p = 2;	 // 可以通过这种方式修改a的值, 此时 a = 2;

// p = &b; // error， const指针不能变
```

+ 指向const的const指针，是上面两者的结合

```c++
const int c = 1;

const int* const p = &a;	// const指针 p不能再变，也不能通过*p去改变 该内存区的值
```

###1.4 const + 引用 + 函数参数

这是c++常用的一种传参方式，通过引用可以提高传参效率，但不希望该函数改变外面定义的变量，用const限定

```c++
void fun(const A& a) {
    // A是一个类，不允许改变a内部值
}
```

### 1.5 const + 类 + 函数

+ c++中，类的成员函数如果不会改变类的成员数据时，一般用const修饰这个成员函数
+ const修饰的成员函数，与没有const修饰的成员函数是不同的函数
+ const对象实例只能调用类中的const成员函数

```c++
#include <iostream>
using namespace std;

class R {
public:
    int r1, r2;
    R(const int _r1, const int _r2) {
        r1 = _r1;
        r2 = _r2;
    }

    //const区分成员重载函数
    void print();
    void print() const;
};

void R::print() {
    cout << "normal function: ";
    cout << r1 << " " << r2 << endl;
}

void R::print() const {
    cout << "const function: ";
    cout << r1 << " " << r2 << endl;
}

int main(void) {
    R r(1, 2);
    r.print();
    
    const R cr(3, 4);  //常对象只能调用常成员函数
    cr.print();

    return 0;
}
```

## 2 static 静态

+ 有static变量, static函数两种，常用来限定作用域

```c
// file1.c
static int a = 1;  // 这个变量限定在file1.c文件中使用

static void fun(void) {	// 这个函数限定在file1.c文件中使用
    // 函数内容
}
```

+ 函数内的static变量只有一份，存放在全局数据段中，只会定义一次，每次调用该函数修改static变量都会共享

```c
void fun_add(void) {	// val的作用域在该函数中，每次调用该函数，都会使val+1
    static int val = 1;
    val++;
    // 其他内容
}
```

+ c++类中，static数据成员需要再外部定义，在类中只是一个声明

```c++
class A {
   static int val;	//  这只是一个声明，必须要在外部定义。并且该类的所有对象实例维护同一份数据拷贝
}；

int A::val = 1;		// 实际的定义
```

+ c++类中，static成员函数不依赖对象实例就可以调用，建议用类名::成员函数的方式调用类中的static成员函数

```c++
#include <iostream>
using namespace std;

class A {
  static void print(void) {
      cout << "static print fun" << endl;
  }  
};

int main(void) {
    A::print();
    return 0;
}
```

## 3 volatile 易变

+ 被volatile修饰的变量，是易变的，编译器不能对这个变量做任何假设去优化程序，每次使用这个变量都要从内存中重新获取，而不是寄存器中直接拿。编译器不会对volatile修饰的变量相关操作进行优化。
+ 与硬件寄存器相关的指针一般都要用volatile，比如STM32的某些外设库的代码就包含了大量的volatile，因为这些硬件寄存器的值除了你代码可以设置之外，由于外部变化，硬件自己也可以改变这个寄存器的值，所以每次都要从该内存/硬件寄存器中获取这个值

例如以下这段程序，对一个外设进行初始化，这个外设的某个寄存器端口为 0xff800000。

如果没有volatiel，编译器可能会进行代码优化，直接执行*output=0x88, 不会执行前面的赋值内容，但是前面的赋值内容对硬件寄存器来说是有意义的，那么就会出错。所以此时必须用volatile

```c
volatile int *output = (unsigned int *)0xff800000;//定义一个IO端口；
int init(void)
{
	*output = 0x55;
    *output = 0x66;
    *output = 0x88;
}
```



















