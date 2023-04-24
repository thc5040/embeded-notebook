## inline 内联函数

短小精悍的追求效率的函数可以用inline，免去函数调用开销

```c
#include <iostream>
using namespace std;

// 短小精悍的追求效率的函数可以用inline，免去函数调用开销，
inline double calArea(double radius) {
    return 3.14 * radius * radius;
}

int main(void) {
 
    double A = calArea(2.0);
    double B = calArea(3.0);

    printf("A:%lf, B:%lf\n", A, B);
 
    return 0;
}
```

## union 联合体

union 成员内共用内存单元 

```c++
#include <iostream>
using namespace std;

union myUnion   //union 成员内共用内存单元
{
    struct 
    {
        int x;
        int y;
        int z;
    }point;
    int k;
}a;

int main(void)
{
    a.point.x = 1;
    a.point.y = 2;
    a.point.z = 3;
    a.k = 100;

    printf("%d %d %d %d\n", a.point.x, a.point.y, a.point.z, a.k);  

    return 0;
}
```

输出：

```
100 2 3 100
```

