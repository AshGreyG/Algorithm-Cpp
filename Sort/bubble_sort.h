#ifndef SORT_BUBBLE_H
#define SORT_BUBBLE_H

#include <utility>
#include <type_traits>
#include <iostream>

template<typename...Args>
void print(Args...args) {
    int _[] { 0, (std::cout << args << " ", 0)...};
    std::cout << std::endl;
}

template<typename T, size_t N>
void print(const T (&arr)[N]) {
    for (size_t i = 0; i < N; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

template<typename...Args, typename Ty = std::common_type_t<Args...>>
void bubbleSort(bool invert, Args...args) {
    Ty input[] { static_cast<Ty>(args)... };
    bool flag = true;
    if (invert) {
        while (flag) {
            flag = false;
            for (int i = 0; i < sizeof...(args) - 1; ++i) {
                if (input[i] < input[i + 1]) {
                    flag = true;
                    std::swap(input[i], input[i + 1]);
                }
                print(input);
            }
        }
    } else {
        while (flag) {
            flag = false;
            for (int i = 0; i < sizeof...(args) - 1; ++i) {
                if (input[i] > input[i + 1]) {
                    flag = true;
                    std::swap(input[i], input[i + 1]);
                }
                print(input);
            }
        }
    }
}

#endif