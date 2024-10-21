cmake_minimum_required(VERSION 3.29)
project(Practicas_SO C)

set(CMAKE_C_STANDARD 11)

include_directories(P0)
include_directories(P1)

add_executable(Practicas_SO
    P0/PDFs/helpcode.c
    P0/color.h
    P0/comandos.c
    P0/comandos.h
    P0/list.c
    P0/list.h
    P0/p0.c
    P1/PDFs/helpcode.c
    P1/color.h
    P1/comandos.c
    P1/comandos.h
    P1/list.c
    P1/list.h
    P1/p0.c
        P1/main.c)
