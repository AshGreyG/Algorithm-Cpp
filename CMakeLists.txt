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

add_executable(Test-Stack ${TEST_STACK_SOURCE})