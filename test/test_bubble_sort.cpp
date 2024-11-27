#include "../Sort/bubble_sort.h"

using namespace std::string_literals;

int main() {
    bubbleSort(false, 1, 2, 0, 4, 1);                               // All int
    bubbleSort(true, "123", "2"s, "abc", "ASTF", "Tsing", "k34");   // const char[] and std::string
    bubbleSort(false, 1, 2.0, 1.5, -10.1, -'c');                    // int double char
    return 0;
}