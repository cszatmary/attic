cmake_minimum_required(VERSION 3.9)
project(attic C)

set(CMAKE_C_STANDARD 11)

include_directories(src)

add_executable(attic main.c src/utils.c src/utils.h)