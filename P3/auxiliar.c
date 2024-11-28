// Pablo Portas López           pablo.portas
// Pablo Míguez Mouiño          pablo.miguez.moino

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

#include "auxiliar.h"

#include <stdlib.h>

#include "color.h"

void Aux_general_Imprimir_Error(char *msg) {
    if (errno == 0) {
        if (!strcmp(msg, "")) fprintf(stderr,ANSI_COLOR_RED "Error Desconocido\n" ANSI_COLOR_RESET);
        else fprintf(stderr,ANSI_COLOR_RED "Error: %s\n" ANSI_COLOR_RESET, msg);
    } else {
        if (!strcmp(msg, "")) fprintf(stderr,ANSI_COLOR_RED "Error %d: %s\n" ANSI_COLOR_RESET,errno, strerror(errno));
        else fprintf(stderr,ANSI_COLOR_RED "Error %d: %s - %s\n" ANSI_COLOR_RESET,errno, msg, strerror(errno));
    }
}

void Aux_general_handler(int sig) {
    if (sig == SIGSEGV) {
        fprintf(stderr,
                ANSI_COLOR_RED ""
                "•.,¸,.•*`•.,¸¸,.•*¯ ╭---------------╮\n"
                "•.,¸,.•*¯`•.,¸,.•*¯.|::::::::::/\\___/\\ \n"
                "•.,¸,.•*¯`•.,¸,.•* <|:::::::::(｡ ●ω●｡)\n"
                "•.,¸,.•¯•.,¸,.•╰ * し------し---   Ｊ\n"
                "SI ESTÁS VIENDO ESTE GATETE VOLADOR HA HABIDO UN SEGMENTATION FAULT\n"
                "Seguramente has intentado acceder a regiones de la memoria que tenías\n"
                "claramente prohibido mirar, o simplemente aporreaste el teclado, en\n"
                "cualquier caso: Lo siento mucho :("
                ANSI_COLOR_RESET);
        exit(EXIT_FAILURE);
    }
}
