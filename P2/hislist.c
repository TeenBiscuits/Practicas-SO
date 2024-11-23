// Pablo Portas López           pablo.portas
// Pablo Míguez Mouiño          pablo.miguez.moino

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "hislist.h"

// Variable global del historial
tList historial = {-1,NULL};

void HList_add(char comando[MAXITEM]) {
    HList_aux_insertItem(comando,LNULL, &historial);
}

void HList_show_all() {
    tPosL posaux = HList_aux_first(historial);
    for (int i = 1; posaux != LNULL; i++) {
        printf("%d. %s\n", i, posaux->comando);
        posaux = HList_aux_next(posaux, historial);
    }
}

void HList_show_n(int n) {
    tPosL posaux = HList_aux_first(historial);
    for (int i = n; i > 0; i--) {
        if (i == 1) {
            printf("%d. %s\n", n, posaux->comando);
        }
        posaux = HList_aux_next(posaux, historial);
    }
}

void HList_show_last_n(int n) {
    tPosL posaux = HList_aux_last(historial);
    for (int i = historial.contador; i > historial.contador + n && posaux != LNULL; i--) {
        printf("%d. %s\n", i + 1, posaux->comando);
        posaux = HList_aux_previous(posaux, historial);
    }
}

int HList_total() {
    return historial.contador + 1;
}

void HList_delete_all(void) {
    if (historial.start == NULL) return;
    while (!HList_aux_isEmptyList(historial)) {
        HList_aux_deleteAtPosition(HList_aux_first(historial), &historial);
    }
}

// AUXILIARES / INTERNAS

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
