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

