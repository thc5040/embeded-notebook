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