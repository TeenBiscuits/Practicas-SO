// Pablo Portas López           pablo.portas
// Pablo Míguez Mouiño          pablo.miguez.moino

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

#include "auxiliar.h"
#include "color.h"

void Aux_general_Imprimir_Error() {
    printf(ANSI_COLOR_RED "Error %d: %s\n" ANSI_COLOR_RESET,errno, strerror(errno));
}

int Aux_general_get_flag(const char *mode) {
    if (strcmp(mode, "cr\0") == 0)
        return O_CREAT | O_WRONLY;
    if (strcmp(mode, "ap\0") == 0)
        return O_APPEND | O_WRONLY;
    if (strcmp(mode, "ex\0") == 0)
        return O_CREAT | O_EXCL | O_WRONLY;
    if (strcmp(mode, "ro\0") == 0)
        return O_RDONLY;
    if (strcmp(mode, "rw\0") == 0)
        return O_RDWR;
    if (strcmp(mode, "wo\0") == 0)
        return O_WRONLY;
    if (strcmp(mode, "tr\0") == 0)
        return O_TRUNC | O_WRONLY;

    return -1;
}
