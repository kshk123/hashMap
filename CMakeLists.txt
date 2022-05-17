cmake_minimum_required(VERSION 3.21)
project(hashMap VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)

include_directories(inc)

set(SOURCES src/HastTest.cpp)

add_executable(hashMap ${SOURCES})
