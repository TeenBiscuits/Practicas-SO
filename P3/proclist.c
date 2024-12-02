// Pablo Portas López           pablo.portas
// Pablo Míguez Mouiño          pablo.miguez.moino

#include <stdlib.h>

#include "proclist.h"

#include <string.h>
#include <time.h>

// Variable global del procedural
tProcList procedural = {-1,NULL};


// AUXILIARES / INTERNAS

void PList_aux_createEmptyList(tProcList *lista) {
    lista->contador = -1;
    lista->start = PNULL;
}

bool PList_aux_isEmptyList(tProcList lista) {
    if (lista.contador == -1) return true;
    return false;
}

tPosProcL PList_aux_first(tProcList lista) {
    return lista.start;
}

tPosProcL PList_aux_last(tProcList lista) {
    tPosProcL puntero;
    for (puntero = lista.start; puntero->siguiente != PNULL; puntero = puntero->siguiente);
    return puntero;
}

tPosProcL PList_aux_next(tPosProcL posicion, tProcList lista) {
    return posicion->siguiente;
}

tPosProcL PList_aux_previous(tPosProcL posicion, tProcList lista) {
    if (posicion == lista.start) return PNULL;
    tPosProcL aux;
    for (aux = lista.start; aux->siguiente != posicion; aux = aux->siguiente);
    return aux;
}

bool PList_aux_insertItem(pid_t pid, time_t time, tCommandLine command, tPosProcL posicion, tProcList *lista) {
    if (!PList_aux_isEmptyList(*lista) && lista->contador == MAX_PLIST_SIZE) return false;

    tPosProcL aux1 = malloc(sizeof(struct tNodeProc));

    if (aux1 == NULL) return false;

    // Creación del nodo
    aux1->pid = pid;
    aux1->time = time;
    strcpy(aux1->command, command);
    aux1->siguiente = PNULL;

    if (lista->start == PNULL)
        lista->start = aux1;
    else if (posicion == PNULL) {
        tPosProcL aux2 = PList_aux_last(*lista);
        aux2->siguiente = aux1;
    } else if (posicion == PList_aux_first(*lista)) {
        aux1->siguiente = posicion;
        lista->start = aux1;
    } else {
        tPosProcL aux2 = PList_aux_previous(posicion, *lista);
        aux2->siguiente = aux1;
        aux1->siguiente = posicion;
    }

    lista->contador += 1;
    return true;
}

void PList_aux_deleteAtPosition(tPosProcL posicion, tProcList *lista) {
    tPosProcL aux, anterior;

    if (PList_aux_next(posicion, *lista) == PNULL) {
        if (posicion == lista->start) {
            lista->start = PNULL;
        } else {
            aux = PList_aux_previous(posicion, *lista);
            aux->siguiente = PNULL;
        }
    } else {
        if (posicion == lista->start) {
            lista->start = PList_aux_next(posicion, *lista);
        } else {
            anterior = PList_aux_previous(posicion, *lista);
            anterior->siguiente = PList_aux_next(posicion, *lista);
        }
    }
    lista->contador -= 1;
    free(posicion);
}

/*
void PList_aux_printNode(tPosProcL posicion) {
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
*/
