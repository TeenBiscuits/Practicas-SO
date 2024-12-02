// Pablo Portas López           pablo.portas
// Pablo Míguez Mouiño          pablo.miguez.moino

#ifndef SELIST_H
#define SELIST_H

#include <stdbool.h>
#include <linux/limits.h>

#define LNULL NULL      // Elemento nulo de la lista, equivalente pero no remplazable por NULL
#define MAXSIZE 1000    // Tamaño máximo de la lista

// Tipo de dato posición de lista, es un puntero a un nodo
typedef struct tNodeSearch *tPosSearchL;

// Tipo path, una cadena de caracteres de tamaño máximo PATH_MAX
typedef char tPathL[PATH_MAX];

// Struct de nodo, formado por la información guardada y un puntero al siguiente elemento.
struct tNodeSearch {
    tPathL path;
    tPosSearchL siguiente;
};

// Tipo dato lista, compuesto de un contador de elementos y un puntero al primer elemento
typedef struct tSearchList {
    int contador;
    tPosSearchL start;
} tSearchList;

// Añade un input al final del buscatal
void SList_add(tPathL path);

// Muestra todas las entradas del historial en orden ascendente
void SList_show_all();

// Muestra la entrada n
void SList_show_n(int n);

// Muestra las últimas n entradas en orden descendente
void SList_show_last_n(int n);

// Devuelve el total de elementos en el historial
int SList_total();

// Borra el historial completo
void SList_delete_all(void);

// AUXILIARES / INTERNAS

// Dado la dirección de memoria de una variable tSearchList, inicializar una lista vacía
void SList_aux_createEmptyList(tSearchList *lista);

// Comprueba si una lista (tSearchList) está vacía
bool SList_aux_isEmptyList(tSearchList lista);

// Devuelve la posición del primer elemento de la lista
tPosSearchL SList_aux_first(tSearchList lista);

// Devuelve la posición del último elemento de la lista
tPosSearchL SList_aux_last(tSearchList lista);

// Devuelve la posición del elemento siguiente a la posición dada
tPosSearchL SList_aux_next(tPosSearchL posicion, tSearchList lista);

// Devuelve la posición del elemento anterior a la posición dada
tPosSearchL SList_aux_previous(tPosSearchL posicion, tSearchList lista);

// Inserta un item en la posición indicada, de no indicarse ninguna (LNULL) se añade al final de la lista.
// Devuelve true/false dependiendo de si se ha podido o no insertar a la lista. El tamaño máximo es 1000.
bool SList_aux_insertItem(tPathL item, tPosSearchL posicion, tSearchList *lista);

// Elimina el elemento de la posición indicada. No se devuelve si la eliminación fue ejecutada.
void SList_aux_deleteAtPosition(tPosSearchL posicion, tSearchList *lista);

#endif //SELIST_H
