// Pablo Portas López           pablo.portas
// Pablo Míguez Mouiño          pablo.miguez.moino

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include "memlist.h"
#include "auxiliar.h"
#include "color.h"

// Variable global del memorial
tMemList memorial = {-1,NULL};

void *MList_add_malloc(int size) {
    void *addr = malloc(size);
    if (addr == NULL) return NULL;
    tFNameL empty = "";
    MList_aux_insertItem(addr, size, time(NULL), MALLOC, -1, empty, -1, MNULL, &memorial);
    return addr;
}

void *MList_add_mmap(tFNameL dir, int protection) {
    int df, map = MAP_PRIVATE, modo = O_RDONLY;
    struct stat s;
    void *p;

    if (protection & PROT_WRITE)
        modo = O_RDWR;
    if (stat(dir, &s) == -1 || (df = open(dir, modo)) == -1)
        return NULL;
    if ((p = mmap(NULL, s.st_size, protection, map, df, 0)) == MAP_FAILED)
        return NULL;
    MList_aux_insertItem(p, s.st_size, time(NULL), MAPPED, -1, dir, df, MNULL, &memorial);
    return p;
}

void MList_remove_malloc(int size) {
    if (!MList_aux_isEmptyList(memorial)) {
        for (tPosMemL posaux = MList_aux_first(memorial); posaux != NULL; posaux = MList_aux_next(posaux, memorial)) {
            if (posaux->alloc == MALLOC && posaux->size == size) {
                // Dirección encontrada
                free(posaux->address); // Liberamos la memoria
                MList_aux_deleteAtPosition(posaux, &memorial); // Eliminamos los registros
                return;
            }
        }
        printf(ANSI_COLOR_RED "No hay bloque de ese tamaño asignado con malloc" ANSI_COLOR_RESET "\n");
    } else printf(ANSI_COLOR_RED "Asigna memoria primero" ANSI_COLOR_RESET "\n");
}

void MList_remove_mmap(tFNameL dir) {
    if (!MList_aux_isEmptyList(memorial)) {
        for (tPosMemL posaux = MList_aux_first(memorial); posaux != NULL; posaux = MList_aux_next(posaux, memorial)) {
            if (posaux->alloc == MAPPED && !strcmp(posaux->file_name, dir)) {
                // Archivo encontrado
                close(posaux->file_desc);
                munmap(posaux->address, posaux->size); // Liberamos la memoria
                MList_aux_deleteAtPosition(posaux, &memorial); // Eliminamos los registros
                return;
            }
        }
        printf(ANSI_COLOR_RED "No hay archivos con ese nombre mapeados en memoria" ANSI_COLOR_RESET "\n");
    } else printf(ANSI_COLOR_RED "Asigna memoria primero" ANSI_COLOR_RESET "\n");
}

void MList_delete_all() {
    if (MList_aux_isEmptyList(memorial)) return;

    tPosMemL posaux;
    while (!MList_aux_isEmptyList(memorial)) {
        posaux = MList_aux_first(memorial);
        if (posaux->alloc == MALLOC) free(posaux->address);
        if (posaux->alloc == MAPPED) {
            close(posaux->file_desc);
            munmap(posaux->address, posaux->size);
        }
        MList_aux_deleteAtPosition(posaux, &memorial);
    }
}

void MList_print(enum tAllocL type_of_alloc) {
    tPosMemL posaux;
    if (MList_aux_isEmptyList(memorial)) {
        printf(ANSI_COLOR_RED "No hay bloques de memoria asignados para el proceso %d" ANSI_COLOR_RESET "\n", getpid());
        return;
    }
    char *allocname = NULL;
    switch (type_of_alloc) {
        case MALLOC: // Imprime las asignaciones por malloc
            allocname = "malloc";
        case SHARED: // Imprime las asignaciones por memoria compartida
            if (allocname == NULL) allocname = "shared";
        case MAPPED: // Imprime las asignaciones por mapeo
            if (allocname == NULL) allocname = "mmap";
            printf(ANSI_COLOR_YELLOW "*** Lista de bloques asignados %s para el proceso %d" ANSI_COLOR_RESET "\n",
                   allocname, getpid());
            for (posaux = MList_aux_first(memorial); posaux != NULL; posaux = MList_aux_next(posaux, memorial)) {
                if (posaux->alloc == type_of_alloc) MList_aux_printNode(posaux);
            }
            break;
        default: // Imprime todos los tipos de asignaciones
            printf(ANSI_COLOR_YELLOW "*** Lista de bloques asignados para el proceso %d" ANSI_COLOR_RESET "\n",
                   getpid());
            for (posaux = MList_aux_first(memorial); posaux != NULL; posaux = MList_aux_next(posaux, memorial))
                MList_aux_printNode(posaux);
            break;
    }
}

// AUXILIARES / INTERNAS

void MList_aux_createEmptyList(tMemList *lista) {
    lista->contador = -1;
    lista->start = MNULL;
}

bool MList_aux_isEmptyList(tMemList lista) {
    if (lista.contador == -1) return true;
    return false;
}

tPosMemL MList_aux_first(tMemList lista) {
    return lista.start;
}

tPosMemL MList_aux_last(tMemList lista) {
    tPosMemL puntero;
    for (puntero = lista.start; puntero->siguiente != MNULL; puntero = puntero->siguiente);
    return puntero;
}

tPosMemL MList_aux_next(tPosMemL posicion, tMemList lista) {
    return posicion->siguiente;
}

tPosMemL MList_aux_previous(tPosMemL posicion, tMemList lista) {
    if (posicion == lista.start) return MNULL;
    tPosMemL aux;
    for (aux = lista.start; aux->siguiente != posicion; aux = aux->siguiente);
    return aux;
}

bool MList_aux_insertItem(tAddressL direccion, int size, time_t alloct_time, enum tAllocL type_of_alloc, int smb_key,
                          tFNameL file_name, int file_descriptor, tPosMemL posicion, tMemList *lista) {
    if (!MList_aux_isEmptyList(*lista) && lista->contador == MAX_MLIST_SIZE) return false;

    tPosMemL aux1 = malloc(sizeof(struct tNodeMem));

    if (aux1 == NULL) return false;

    // Creación del nodo
    aux1->address = direccion;
    aux1->size = size;
    aux1->time = alloct_time;
    aux1->alloc = type_of_alloc;
    aux1->smb_key = smb_key;
    strcpy(aux1->file_name, file_name);
    aux1->file_desc = file_descriptor;
    aux1->siguiente = MNULL;

    if (lista->start == MNULL)
        lista->start = aux1;
    else if (posicion == MNULL) {
        tPosMemL aux2 = MList_aux_last(*lista);
        aux2->siguiente = aux1;
    } else if (posicion == MList_aux_first(*lista)) {
        aux1->siguiente = posicion;
        lista->start = aux1;
    } else {
        tPosMemL aux2 = MList_aux_previous(posicion, *lista);
        aux2->siguiente = aux1;
        aux1->siguiente = posicion;
    }

    lista->contador += 1;
    return true;
}

void MList_aux_deleteAtPosition(tPosMemL posicion, tMemList *lista) {
    tPosMemL aux, anterior;

    if (MList_aux_next(posicion, *lista) == MNULL) {
        if (posicion == lista->start) {
            lista->start = MNULL;
        } else {
            aux = MList_aux_previous(posicion, *lista);
            aux->siguiente = MNULL;
        }
    } else {
        if (posicion == lista->start) {
            lista->start = MList_aux_next(posicion, *lista);
        } else {
            anterior = MList_aux_previous(posicion, *lista);
            anterior->siguiente = MList_aux_next(posicion, *lista);
        }
    }
    lista->contador -= 1;
    free(posicion);
}

void MList_aux_printNode(tPosMemL posicion) {
    char datebuffer[80];
    struct tm *tm_info = localtime(&posicion->time);
    strftime(datebuffer, sizeof(datebuffer), "%d %b %y %H:%M", tm_info);
    switch (posicion->alloc) {
        case MALLOC:
            printf("\t%p %15d %s %s\n", posicion->address, posicion->size, datebuffer, "malloc");
            break;
        case SHARED:
            printf("\t%p %15d %s %s (key %d)\n", posicion->address, posicion->size, datebuffer, "shared",
                   posicion->smb_key);
            break;
        case MAPPED:
            printf("\t%p %15d %s %s (descriptor %d)\n", posicion->address, posicion->size, datebuffer,
                   posicion->file_name, posicion->file_desc);
            break;
    }
}
