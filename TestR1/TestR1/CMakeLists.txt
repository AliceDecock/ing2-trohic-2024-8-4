cmake_minimum_required(VERSION 3.26)
project(TestR1 C)

set(CMAKE_C_STANDARD 11)

add_executable(TestR1 main.c
        network.c
        network.h
        connexite.c
        connexite.h)
