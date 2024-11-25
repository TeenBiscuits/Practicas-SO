// Pablo Portas López           pablo.portas
// Pablo Míguez Mouiño          pablo.miguez.moino

#include "memoria.h"
#include "memlist.h"
#include "help.h"
#include "auxiliar.h"
#include "color.h"

#include <string.h>

// COMANDOS DE MEMORIA P2

void Cmd_allocate(int NumTrozos, char *trozos[]) {
    if (NumTrozos >= 1 && strcmp(trozos[1], "-?") == 0) {
        Help_allocate();
        return;
    }

    if (NumTrozos == 0) {
        MList_print(-1);
    } else {
        void *paux;
        if (strcmp(trozos[1], "-malloc") == 0) {
            if (NumTrozos >= 2) {
                if (atoi(trozos[2]) == 0)
                    printf(ANSI_COLOR_RED "No se asignan bloques de 0 bytes." ANSI_COLOR_RESET "\n");
                else if ((paux = MList_add_malloc(atoi(trozos[2]))) == NULL) Aux_general_Imprimir_Error();
                else printf(ANSI_COLOR_GREEN "Asignados %d bytes en %p" ANSI_COLOR_RESET "\n", atoi(trozos[2]), paux);
            } else MList_print(MALLOC);
        }
    }
}

void Cmd_deallocate(int NumTrozos, char *trozos[]) {
    if (NumTrozos >= 1 && strcmp(trozos[1], "-?") == 0) {
        Help_deallocate();
        return;
    }

    if (NumTrozos == 0) {
        MList_print(-1);
    } else {
        if (strcmp(trozos[1], "-malloc") == 0) {
            if (NumTrozos >= 2) MList_remove_malloc(atoi(trozos[2]));
            else MList_print(MALLOC);
        }
    }
}

void Cmd_memfill(int NumTrozos, char *trozos[]) {
}

void Cmd_memdump(int NumTrozos, char *trozos[]) {
}

void Cmd_memory(int NumTrozos, char *trozos[]) {
    if (NumTrozos >= 1 && strcmp(trozos[1], "-?") == 0) {
        Help_memory();
        return;
    }
}

void Cmd_readfile(int NumTrozos, char *trozos[]) {
}

void Cmd_writefile(int NumTrozos, char *trozos[]) {
}

void Cmd_read(int NumTrozos, char *trozos[]) {
}

void Cmd_write(int NumTrozos, char *trozos[]) {
}

void Cmd_recurse(int NumTrozos, char *trozos[]) {
}
