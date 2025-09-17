cmake_minimum_required(VERSION 3.22)
project(Practicas-SO C)

set(CMAKE_C_STANDARD 99)

add_executable(Shell main.c
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
        auxiliar.h
        memlist.c
        memlist.h
        procesos.c
        procesos.h
        searchlist.c
        searchlist.h
        proclist.c
        proclist.c)
