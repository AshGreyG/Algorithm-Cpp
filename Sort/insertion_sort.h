#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include <type_traits>
#include <iostream>

template<typename...Args>
void print(Args...args) {
    int _[] { 0, (std::cout << args << " ")... };
    std::cout << std::endl;
}

template<typename T, size_t N>
void print(const T (&arr) [N]) {
    for (size_t i = 0; i < N; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

template<typename...Args, typename Ty = std::common_type_t<Args...>>
void insertionSort(bool invert, Args...args) {
    Ty input[] = { static_cast<Ty>(args)... };
    if (invert) {
        for (int i = 2; i <= sizeof...(args); ++i) {
            Ty key = input[i - 1];
            int j = i - 1;
            while (j >= 1 && input[j - 1] > key) {
                input[j] = input[j - 1];
                j--;
            }
            input[j] = key;
            print(input);
        }
    } else {
        for (int i = 2; i <= sizeof...(args); ++i) {
            Ty key = input[i - 1];
            int j = i - 1;
            while (j >= 1 && input[j - 1] < key) {
                input[j] = input[j - 1];
                j--;
            }
            input[j] = key;
            print(input);
        }
    }
}

#endif