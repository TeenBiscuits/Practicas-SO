cmake_minimum_required(VERSION 3.22)
project(P2 C)

set(CMAKE_C_STANDARD 99)

add_executable(P2 main.c
        hislist.c
        hislist.h
        color.h
        comandos.c
        comandos.h
        help.c
        help.h
        memoria.c
        memoria.h
        auxiliar.c
        auxiliar.h)
