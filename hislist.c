// Pablo Portas López           pablo.portas
// Pablo Míguez Muiño           pablo.miguez.moino

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "hislist.h"

// Variable global del historial
tHisList historial = {-1,NULL};

void HList_add(char comando[MAXITEM]) {
    HList_aux_insertItem(comando,LNULL, &historial);
}

void HList_show_all() {
    tPosHisL posaux = HList_aux_first(historial);
    for (int i = 1; posaux != LNULL; i++) {
        printf("%d. %s\n", i, posaux->comando);
        posaux = HList_aux_next(posaux, historial);
    }
}

void HList_show_n(int n) {
    tPosHisL posaux = HList_aux_first(historial);
    for (int i = n; i > 0; i--) {
        if (i == 1) {
            printf("%d. %s\n", n, posaux->comando);
        }
        posaux = HList_aux_next(posaux, historial);
    }
}

void HList_show_last_n(int n) {
    tPosHisL posaux = HList_aux_last(historial);
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

void HList_aux_createEmptyList(tHisList *lista) {
    lista->contador = -1;
    lista->start = LNULL;
}

bool HList_aux_isEmptyList(tHisList lista) {
    if (lista.contador == -1) return true;
    return false;
}

tPosHisL HList_aux_first(tHisList lista) {
    return lista.start;
}

tPosHisL HList_aux_last(tHisList lista) {
    tPosHisL puntero;
    for (puntero = lista.start; puntero->siguiente != LNULL; puntero = puntero->siguiente);
    return puntero;
}

tPosHisL HList_aux_next(tPosHisL posicion, tHisList lista) {
    return posicion->siguiente;
}

tPosHisL HList_aux_previous(tPosHisL posicion, tHisList lista) {
    if (posicion == lista.start) return LNULL;
    tPosHisL aux;
    for (aux = lista.start; aux->siguiente != posicion; aux = aux->siguiente);
    return aux;
}

bool HList_aux_insertItem(tItemL item, tPosHisL posicion, tHisList *lista) {
    if (!HList_aux_isEmptyList(*lista) && lista->contador == MAXSIZE) return false;

    tPosHisL aux1 = malloc(sizeof(struct tNodeHis));

    if (aux1 == NULL) return false;

    strcpy(aux1->comando, item);
    aux1->siguiente = LNULL;
    if (lista->start == LNULL)
        lista->start = aux1;
    else if (posicion == LNULL) {
        tPosHisL aux2 = HList_aux_last(*lista);
        aux2->siguiente = aux1;
    } else if (posicion == HList_aux_first(*lista)) {
        aux1->siguiente = posicion;
        lista->start = aux1;
    } else {
        tPosHisL aux2 = HList_aux_previous(posicion, *lista);
        aux2->siguiente = aux1;
        aux1->siguiente = posicion;
    }
    lista->contador += 1;
    return true;
}

void HList_aux_deleteAtPosition(tPosHisL posicion, tHisList *lista) {
    tPosHisL aux, anterior;

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
