cmake_minimum_required(VERSION 3.10)

project(Algorithm VERSION 0.1)

include_directories(Data-Structure
                    Other
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(TEST_STACK_SOURCE
    Data-Structure/stack.h
    test/test_stack.cpp
)

set(TEST_BUBBULE_SORT
    Sort/bubble_sort.h
    test/test_bubble_sort.cpp
)

set(TEST_INSERTION_SORT
    Sort/insertion_sort.h
    test/test_insertion_sort.cpp
)

add_executable(Test-Stack ${TEST_STACK_SOURCE})
add_executable(Test-Bubble-Sort ${TEST_BUBBULE_SORT})
add_executable(Test-Insertion-Sort ${TEST_INSERTION_SORT})