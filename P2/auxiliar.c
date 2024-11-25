// Pablo Portas López           pablo.portas
// Pablo Míguez Mouiño          pablo.miguez.moino

#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "auxiliar.h"
#include "color.h"

void Imprimir_Error() {
    printf(ANSI_COLOR_RED "Error %d: %s\n" ANSI_COLOR_RESET,errno, strerror(errno));
}