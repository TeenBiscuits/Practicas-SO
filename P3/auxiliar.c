// Pablo Portas López           pablo.portas
// Pablo Míguez Mouiño          pablo.miguez.moino

#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "auxiliar.h"
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
