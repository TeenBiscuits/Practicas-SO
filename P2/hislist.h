// Pablo Portas López           pablo.portas
// Pablo Míguez Mouiño          pablo.miguez.moino

#ifndef LIST_H
#define LIST_H

// Implementación de una lista enlazada sencilla

#define MAXITEM 2048    // Tamaño máximo de un elemento
#define LNULL NULL      // Elemento nulo de la lista, equivalente pero no remplazable por NULL
#define MAXSIZE 1000    // Tamaño máximo de la lista

// Tipo de dato posición de lista, es un puntero a un nodo
typedef struct tNode *tPosL;

// Tipo item, una cadena de caracteres de tamaño máximo MAXITEM
typedef char tItemL[MAXITEM];

// Struct de nodo, formado por la información guardada y un puntero al siguiente elemento.
struct tNode {
    tItemL comando;
    tPosL siguiente;
};

// Tipo dato lista, compuesto de un contador de elementos y un puntero al primer elemento
typedef struct tList {
    int contador;
    tPosL start;
} tList;

// Añade un input al final del histórico
void HList_add(char comando[MAXITEM]);

// Muestra todas las entradas del historial en orden ascendente
void HList_show_all();

// Muestra la entrada n
void HList_show_n(int n);

// Muestra las últimas n entradas en orden descendente
void HList_show_last_n(int n);

// Devuelve el total de elementos en el historial
int HList_total();

// Borra el historial completo
void HList_delete_all(void);

// AUXILIARES / INTERNAS

// Dado la dirección de memoria de una variable tList, inicializar una lista vacía
void HList_aux_createEmptyList(tList *lista);

// Comprueba si una lista (tList) está vacía
bool HList_aux_isEmptyList(tList lista);

// Devuelve la posición del primer elemento de la lista
tPosL HList_aux_first(tList lista);

// Devuelve la posición del último elemento de la lista
tPosL HList_aux_last(tList lista);

// Devuelve la posición del elemento siguiente a la posición dada
tPosL HList_aux_next(tPosL posicion, tList lista);

// Devuelve la posición del elemento anterior a la posición dada
tPosL HList_aux_previous(tPosL posicion, tList lista);

// Inserta un item en la posición indicada, de no indicarse ninguna (LNULL) se añade al final de la lista.
// Devuelve true/false dependiendo de si se ha podido o no insertar a la lista. El tamaño máximo es 1000.
bool HList_aux_insertItem(tItemL item, tPosL posicion, tList *lista);

// Elimina el elemento de la posición indicada. No se devuelve si la eliminación fue ejecutada.
void HList_aux_deleteAtPosition(tPosL posicion, tList *lista);

#endif //LIST_H
