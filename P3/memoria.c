// Pablo Portas López           pablo.portas
// Pablo Míguez Mouiño          pablo.miguez.moino

#include "memoria.h"
#include "memlist.h"
#include "help.h"
#include "auxiliar.h"
#include "color.h"

#include <string.h>
#include <sys/mman.h>
#include <errno.h>

// COMANDOS DE MEMORIA P2

void Cmd_allocate(int NumTrozos, char *trozos[]) {
    if (NumTrozos >= 1 && strcmp(trozos[1], "-?") == 0) {
        Help_allocate();
        return;
    }

    if (NumTrozos == 0) {
        MList_print(-1);
        return;
    }

    if (strcmp(trozos[1], "-malloc") == 0) Aux_allocate_malloc(NumTrozos, trozos);
    if (strcmp(trozos[1], "-mmap") == 0) Aux_allocate_mmap(NumTrozos, trozos);
    if (strcmp(trozos[1], "-createshared") == 0) Aux_allocate_createshared(NumTrozos, trozos);
    if (strcmp(trozos[1], "-shared") == 0) Aux_allocate_shared(NumTrozos, trozos);
}

void Cmd_deallocate(int NumTrozos, char *trozos[]) {
    if (NumTrozos >= 1 && strcmp(trozos[1], "-?") == 0) {
        Help_deallocate();
        return;
    }

    if (NumTrozos == 0) {
        MList_print(-1);
    } else {
        if (!strcmp(trozos[1], "-malloc")) {
            if (NumTrozos >= 2) Aux_deallocate_malloc(NumTrozos, trozos);
            else MList_print(MALLOC);
        }
        if (!strcmp(trozos[1], "-mmap")) {
            if (NumTrozos >= 2) Aux_deallocate_mmap(NumTrozos, trozos);
            else MList_print(MAPPED);
        }
        if (!strcmp(trozos[1], "-shared")) {
            if (NumTrozos >= 2) Aux_deallocate_delkey(NumTrozos, trozos);
            else MList_print(SHARED);
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

// Auxiliares

void Aux_allocate_malloc(int NumTrozos, char *trozos[]) {
    void *paux;
    if (NumTrozos >= 2) {
        if (atoi(trozos[2]) == 0)
            Aux_general_Imprimir_Error("No se asignan bloques de 0 bytes");
        else if ((paux = MList_add_malloc(atoi(trozos[2]))) == NULL) Aux_general_Imprimir_Error("");
        else printf(ANSI_COLOR_GREEN "Asignados %d bytes en %p" ANSI_COLOR_RESET "\n", atoi(trozos[2]), paux);
    } else MList_print(MALLOC);
}

void Aux_deallocate_malloc(int NumTrozos, char *trozos[]) {
    MList_remove_malloc(atoi(trozos[2]));
}

void Aux_allocate_mmap(int NumTrozos, char *trozos[]) {
    void *paux;
    char *perm;
    int protection = 0;

    if (NumTrozos >= 2) {
        if ((perm = trozos[3]) != NULL && strlen(perm) < 4) {
            if (strchr(perm, 'r') != NULL) protection |= PROT_READ;
            if (strchr(perm, 'w') != NULL) protection |= PROT_WRITE;
            if (strchr(perm, 'x') != NULL) protection |= PROT_EXEC;
        }
        if ((paux = MList_add_mmap(trozos[2], protection)) == NULL) Aux_general_Imprimir_Error("");
        else printf(ANSI_COLOR_GREEN "Fichero %s mapeado en %p" ANSI_COLOR_RESET "\n", trozos[2], paux);
    } else MList_print(MAPPED);
}

void Aux_deallocate_mmap(int NumTrozos, char *trozos[]) {
    MList_remove_mmap(trozos[2]);
}

void Aux_allocate_createshared(int NumTrozos, char *trozos[]) {

}

void Aux_deallocate_delkey(int NumTrozos, char *trozos[]) {

}

void Aux_allocate_shared(int NumTrozos, char *trozos[]) {

}

void Aux_deallocate_shared(int NumTrozos, char *trozos[]) {

}
