cmake_minimum_required(VERSION 3.26)
project(projetinffoing2 C)

set(CMAKE_C_STANDARD 23)

add_executable(projetinffoing2 main.c
        network.c
        connexite.c
        centralite.h
        centralite.c
        dynamique.h
        dynamique.c
        dotgraphe.c
        dotgraphe.h
        complexite.c
        complexite.h)
