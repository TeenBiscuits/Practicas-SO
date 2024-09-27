// Pablo Portas López
// Pablo Míguez Mouiño

#include "list.h"

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
    tPosL aux1, aux2;

    if (!isEmptyList(*lista)) {
        int totalUsers = 0;

        for (tPosL auxPos = first(*lista); next(auxPos, *lista) != LNULL; auxPos = next(auxPos, *lista)) {
            totalUsers += 1;
        }

        if (totalUsers == MAXSIZE) return false;
    }

    aux1 = malloc(sizeof(struct tNode));

    if (aux1 == NULL) // Se crea espacio en memoria para un nodo
        return false; // No hay memoria disponible
    else {
        strcpy(aux1->comando, item); // Se guarda en el nodo la información del usuario
        aux1->siguiente = LNULL; // Se le inicializa sin apuntar a ningún nodo
        if (lista->start == LNULL) // Si la lista está vacía el nodo es el primer elemento
            lista->start = aux1;
        else if (posicion == LNULL) {
            aux2 = last(*lista);
            aux2->siguiente = aux1; // El último nodo ahora apunta al nuevo nodo
        } else if (posicion == lista->start) { // Se quiere añadir en la primera posición de la lista
            aux1->siguiente = posicion; // El nodo apunta al primer elemento
            lista->start = aux1; // La lista apunta al nuevo nodo
        } else {
            aux2 = previous(posicion, *lista);
            aux2->siguiente = aux1; // El nodo anterior apunta al nuevo nodo
            aux1->siguiente = posicion; // El nuevo nodo apunta a la posición indicada
        }
        return true;
    }
}

void deleteAtPosition(tPosL posicion, tList *lista) {
    tPosL aux, anterior;

    if (next(posicion, *lista) == LNULL) { // Si la posición a eliminar es la última
        if (posicion == lista->start) { // Si la lista está compuesta por un único item
            lista->start = LNULL; // La lista se queda sin elementos
        } else {
            aux = previous(posicion, *lista); // El elemento anterior a él debe apuntar a NULL
            aux->siguiente = LNULL;
        }
    } else {
        if (posicion == lista->start) {
            lista->start = next(posicion, *lista);
            // Al ser el primer elemento, la lista ahora empieza en el segundo (el siguiente)
        } else {
            anterior = previous(posicion, *lista);
            anterior->siguiente = next(posicion, *lista);
            // El elemento anterior apunta al siguiente a la posición eliminada
        }
    }
    free(posicion);
};
