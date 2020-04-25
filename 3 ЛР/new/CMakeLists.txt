
cmake_minimum_required(VERSION 3.9)

project(lab3 CXX)

add_executable(lab3
    src/main.cpp
    src/test.cpp
)

target_include_directories(lab3
    PUBLIC src/tree/
)
