cmake_minimum_required(VERSION 3.26)
project(TestR1 C)

set(CMAKE_C_STANDARD 11)

add_executable(TestR1 main.c
        network.c
        network.h
        connexite.c
        connexite.h
        centralite.c
        centralite.h
        dynamique.c
        dynamique.h
        dotgraphe.c
        dotgraphe.h
        complexite.c
        complexite.h)
