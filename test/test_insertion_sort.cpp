#include "../Sort/insertion_sort.h"

using namespace std::string_literals;

int main() {
    insertionSort(false, 3, 2, 4, 1, 5);
    insertionSort(true, "sort"s, "ppp", "insert", "2333");
    return 0;
}