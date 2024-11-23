// Pablo Portas López           pablo.portas
// Pablo Míguez Mouiño          pablo.miguez.moino

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "hislist.h"

void HList_aux_createEmptyList(tList *lista) {
    lista->contador = -1;
    lista->start = LNULL;
}

bool HList_aux_isEmptyList(tList lista) {
    if (lista.contador == -1) return true;
    return false;
}

tPosL HList_aux_first(tList lista) {
    return lista.start;
}

tPosL HList_aux_last(tList lista) {
    tPosL puntero;
    for (puntero = lista.start; puntero->siguiente != LNULL; puntero = puntero->siguiente);
    return puntero;
}

tPosL HList_aux_next(tPosL posicion, tList lista) {
    return posicion->siguiente;
}

tPosL HList_aux_previous(tPosL posicion, tList lista) {
    if (posicion == lista.start) return LNULL;
    tPosL aux;
    for (aux = lista.start; aux->siguiente != posicion; aux = aux->siguiente);
    return aux;
}

bool HList_aux_insertItem(tItemL item, tPosL posicion, tList *lista) {
    if (!HList_aux_isEmptyList(*lista) && lista->contador == MAXSIZE) return false;

    tPosL aux1 = malloc(sizeof(struct tNode));

    if (aux1 == NULL) return false;

    strcpy(aux1->comando, item);
    aux1->siguiente = LNULL;
    if (lista->start == LNULL)
        lista->start = aux1;
    else if (posicion == LNULL) {
        tPosL aux2 = HList_aux_last(*lista);
        aux2->siguiente = aux1;
    } else if (posicion == HList_aux_first(*lista)) {
        aux1->siguiente = posicion;
        lista->start = aux1;
    } else {
        tPosL aux2 = HList_aux_previous(posicion, *lista);
        aux2->siguiente = aux1;
        aux1->siguiente = posicion;
    }
    lista->contador += 1;
    return true;
}

void HList_aux_deleteAtPosition(tPosL posicion, tList *lista) {
    tPosL aux, anterior;

    if (HList_aux_next(posicion, *lista) == LNULL) {
        if (posicion == lista->start) {
            lista->start = LNULL;
        } else {
            aux = HList_aux_previous(posicion, *lista);
            aux->siguiente = LNULL;
        }
    } else {
        if (posicion == lista->start) {
            lista->start = HList_aux_next(posicion, *lista);
        } else {
            anterior = HList_aux_previous(posicion, *lista);
            anterior->siguiente = HList_aux_next(posicion, *lista);
        }
    }
    lista->contador -= 1;
    free(posicion);
};
