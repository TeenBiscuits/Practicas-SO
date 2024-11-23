// Pablo Portas López           pablo.portas
// Pablo Míguez Mouiño          pablo.miguez.moino

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "hislist.h"

void createEmptyList(tList *lista) {
    lista->contador = -1;
    lista->start = LNULL;
}

bool isEmptyList(tList lista) {
    if (lista.contador == -1) return true;
    return false;
}

tPosL first(tList lista) {
    return lista.start;
}

tPosL last(tList lista) {
    tPosL puntero;
    for (puntero = lista.start; puntero->siguiente != LNULL; puntero = puntero->siguiente);
    return puntero;
}

tPosL next(tPosL posicion, tList lista) {
    return posicion->siguiente;
}

tPosL previous(tPosL posicion, tList lista) {
    if (posicion == lista.start) return LNULL;
    tPosL aux;
    for (aux = lista.start; aux->siguiente != posicion; aux = aux->siguiente);
    return aux;
}

bool insertItem(tItemL item, tPosL posicion, tList *lista) {
    if (!isEmptyList(*lista) && lista->contador == MAXSIZE) return false;

    tPosL aux1 = malloc(sizeof(struct tNode));

    if (aux1 == NULL) return false;

    strcpy(aux1->comando, item);
    aux1->siguiente = LNULL;
    if (lista->start == LNULL)
        lista->start = aux1;
    else if (posicion == LNULL) {
        tPosL aux2 = last(*lista);
        aux2->siguiente = aux1;
    } else if (posicion == first(*lista)) {
        aux1->siguiente = posicion;
        lista->start = aux1;
    } else {
        tPosL aux2 = previous(posicion, *lista);
        aux2->siguiente = aux1;
        aux1->siguiente = posicion;
    }
    lista->contador += 1;
    return true;
}

void deleteAtPosition(tPosL posicion, tList *lista) {
    tPosL aux, anterior;

    if (next(posicion, *lista) == LNULL) {
        if (posicion == lista->start) {
            lista->start = LNULL;
        } else {
            aux = previous(posicion, *lista);
            aux->siguiente = LNULL;
        }
    } else {
        if (posicion == lista->start) {
            lista->start = next(posicion, *lista);
        } else {
            anterior = previous(posicion, *lista);
            anterior->siguiente = next(posicion, *lista);
        }
    }
    lista->contador -= 1;
    free(posicion);
};
