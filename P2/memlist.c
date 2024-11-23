// Pablo Portas López           pablo.portas
// Pablo Míguez Mouiño          pablo.miguez.moino

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#include "memlist.h"
#include "color.h"

// Variable global del memorial
tMemList memorial = {-1,NULL};

void *MList_add_malloc(int size) {
    void *addr = malloc(size);
    if (
        addr == NULL &&
        !MList_aux_insertItem(addr, size, time(NULL), MALLOC, -1, NULL, -1,MNULL, &memorial)
    )
        return NULL;

    return addr;
}

void MList_remove_malloc(int size) {
    if (!MList_aux_isEmptyList(memorial)) {
        for (tPosMemL posaux = MList_aux_first(memorial); posaux != NULL; posaux = MList_aux_next(posaux, memorial)) {
            if (posaux->alloc == MALLOC && posaux->size == size) {
                // Dirección encontrada
                free(posaux->dir); // Liberamos la memoria
                MList_aux_deleteAtPosition(posaux, &memorial); // Eliminamos los registros
                return;
            }
        }
        printf(ANSI_COLOR_RED "No hay bloque de ese tamaño asignado con malloc" ANSI_COLOR_RESET "\n");
    } else printf(ANSI_COLOR_RED "Asigna memoria primero" ANSI_COLOR_RESET "\n");
}

void MList_delete_all() {
    if (MList_aux_isEmptyList(memorial)) return;

    tPosMemL posaux;
    while (!MList_aux_isEmptyList(memorial)) {
        posaux = MList_aux_first(memorial);
        if (posaux->alloc == MALLOC) free(posaux->dir);
        MList_aux_deleteAtPosition(posaux, &memorial);
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

bool MList_aux_insertItem(tDirL direccion, int size, time_t alloct_time, enum tAllocL type_of_alloc, int smb_key,
                          tFNameL file_name, int file_descriptor, tPosMemL posicion, tMemList *lista) {
    if (!MList_aux_isEmptyList(*lista) && lista->contador == MAX_MLIST_SIZE) return false;

    tPosMemL aux1 = malloc(sizeof(struct tNodeMem));

    if (aux1 == NULL) return false;

    // Creación del nodo
    aux1->dir = direccion;
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
