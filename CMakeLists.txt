cmake_minimum_required(VERSION 3.15)
project(crypto_rand CXX)

set(CMAKE_C_STANDARD 17)
SET(CMAKE_VERBOSE_MAKEFILE true)

include_directories(src)

add_executable(example example.cpp)
