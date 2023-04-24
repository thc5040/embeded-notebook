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