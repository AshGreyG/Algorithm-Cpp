#include "../Data-Structure/stack.h"

void testStackInt_1() {
    Stack<int> test_int(0, 10);
    test_int.pop();
    test_int.push(1);
    test_int.push(3);
}


int main() {
    testStackInt_1();
    return 0;
}