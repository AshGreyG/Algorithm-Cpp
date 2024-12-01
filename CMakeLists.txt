cmake_minimum_required(VERSION 3.10)

project(Algorithm VERSION 0.1)

include_directories(Data-Structure
                    Other
                    Sort
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# BEGIN SET DATA-STRUCTURE

set(TEST_STACK_SOURCE
    Data-Structure/stack.h
    test/test_stack.cpp
)

# END SET DATA-STRUCTURE

# BEGIN SET SORT

set(TEST_BUBBULE_SORT
    Sort/bubble_sort.h
    test/test_bubble_sort.cpp
)

set(TEST_INSERTION_SORT
    Sort/insertion_sort.h
    test/test_insertion_sort.cpp
)

# END SET SORT

# BEGIN SET OTHER

set(TEST_ARBITARY_PERCISION
    Other/arbitary_percision.h
    test/test_arbitary_percision.cpp
)

add_executable(Test-Stack ${TEST_STACK_SOURCE})
add_executable(Test-Bubble-Sort ${TEST_BUBBULE_SORT})
add_executable(Test-Insertion-Sort ${TEST_INSERTION_SORT})
add_executable(Test-Arbitary-Percision ${TEST_ARBITARY_PERCISION})