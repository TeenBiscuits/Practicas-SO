cmake_minimum_required(VERSION 3.22)
project(P1 C)

set(CMAKE_C_STANDARD 99)

add_executable(P1 main.c
        list.c
        list.h
        color.h
        comandos.c
        comandos.h
        help.c
        help.h)
