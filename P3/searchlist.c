// Pablo Portas López           pablo.portas
// Pablo Míguez Mouiño          pablo.miguez.moino

#include "searchlist.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Variable global del buscatal
tSearchList buscatal = {-1,NULL};

void SList_add(char path[PATH_MAX]) {
    SList_aux_insertItem(path,LNULL, &buscatal);
}

void SList_show_all() {
    tPosSearchL posaux = SList_aux_first(buscatal);
    for (int i = 1; posaux != LNULL; i++) {
        printf("%s\n", posaux->path);
        posaux = SList_aux_next(posaux, buscatal);
    }
}

void SList_show_n(int n) {
    tPosSearchL posaux = SList_aux_first(buscatal);
    for (int i = n; i > 0; i--) {
        if (i == 1) {
            printf("%d. %s\n", n, posaux->path);
        }
        posaux = SList_aux_next(posaux, buscatal);
    }
}

void SList_show_last_n(int n) {
    tPosSearchL posaux = SList_aux_last(buscatal);
    for (int i = buscatal.contador; i > buscatal.contador + n && posaux != LNULL; i--) {
        printf("%d. %s\n", i + 1, posaux->path);
        posaux = SList_aux_previous(posaux, buscatal);
    }
}

int SList_total() {
    return buscatal.contador + 1;
}

void SList_delete_all(void) {
    if (buscatal.start == NULL) return;
    while (!SList_aux_isEmptyList(buscatal)) {
        SList_aux_deleteAtPosition(SList_aux_first(buscatal), &buscatal);
    }
}

// AUXILIARES / INTERNAS

void SList_aux_createEmptyList(tSearchList *lista) {
    lista->contador = -1;
    lista->start = LNULL;
}

bool SList_aux_isEmptyList(tSearchList lista) {
    if (lista.contador == -1) return true;
    return false;
}

tPosSearchL SList_aux_first(tSearchList lista) {
    return lista.start;
}

tPosSearchL SList_aux_last(tSearchList lista) {
    tPosSearchL puntero;
    for (puntero = lista.start; puntero->siguiente != LNULL; puntero = puntero->siguiente);
    return puntero;
}

tPosSearchL SList_aux_next(tPosSearchL posicion, tSearchList lista) {
    return posicion->siguiente;
}

tPosSearchL SList_aux_previous(tPosSearchL posicion, tSearchList lista) {
    if (posicion == lista.start) return LNULL;
    tPosSearchL aux;
    for (aux = lista.start; aux->siguiente != posicion; aux = aux->siguiente);
    return aux;
}

bool SList_aux_insertItem(tPathL path, tPosSearchL posicion, tSearchList *lista) {
    if (!SList_aux_isEmptyList(*lista) && lista->contador == MAXSIZE) return false;

    tPosSearchL aux1 = malloc(sizeof(struct tNodeSearch));

    if (aux1 == NULL) return false;

    strcpy(aux1->path, path);
    aux1->siguiente = LNULL;
    if (lista->start == LNULL)
        lista->start = aux1;
    else if (posicion == LNULL) {
        tPosSearchL aux2 = SList_aux_last(*lista);
        aux2->siguiente = aux1;
    } else if (posicion == SList_aux_first(*lista)) {
        aux1->siguiente = posicion;
        lista->start = aux1;
    } else {
        tPosSearchL aux2 = SList_aux_previous(posicion, *lista);
        aux2->siguiente = aux1;
        aux1->siguiente = posicion;
    }
    lista->contador += 1;
    return true;
}

void SList_aux_deleteAtPosition(tPosSearchL posicion, tSearchList *lista) {
    tPosSearchL aux, anterior;

    if (SList_aux_next(posicion, *lista) == LNULL) {
        if (posicion == lista->start) {
            lista->start = LNULL;
        } else {
            aux = SList_aux_previous(posicion, *lista);
            aux->siguiente = LNULL;
        }
    } else {
        if (posicion == lista->start) {
            lista->start = SList_aux_next(posicion, *lista);
        } else {
            anterior = SList_aux_previous(posicion, *lista);
            anterior->siguiente = SList_aux_next(posicion, *lista);
        }
    }
    lista->contador -= 1;
    free(posicion);
};
