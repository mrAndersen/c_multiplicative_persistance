cmake_minimum_required(VERSION 3.13)
project(persistance)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-lpthread -march=native -O2")
set(CMAKE_C_FLAGS "lpthread -march=native -O2")

add_executable(persistance main.cpp)