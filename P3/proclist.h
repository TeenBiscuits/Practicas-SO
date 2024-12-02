// Pablo Portas López           pablo.portas
// Pablo Míguez Mouiño          pablo.miguez.moino

#ifndef PROLIST_H
#define PROLIST_H

#include <stdbool.h>
#include <sys/types.h>

#define PNULL NULL              // Elemento nulo de la lista, equivalente pero no reemplazable por NULL
#define MAX_PLIST_SIZE 1000     // Tamaño máximo de la lista

// Tipo de dato posición de lista, es un puntero a un nodo
typedef struct tNodeProc *tPosProcL;

typedef void *tAddressL;

enum tStatusL { FINISHED, STOPPED, SIGNALED, ACTIVE };

typedef char tCommandLine[2048];

// Struct de nodo, formado por la información guardada y un puntero al siguiente elemento.
struct tNodeProc {
    pid_t pid; // PID
    time_t time; // Fecha de lanzamiento
    enum tStatusL status; // Estado
    tCommandLine command; // Command Line
    tPosProcL siguiente; // Puntero al siguiente nodo de la lista
};

// Tipo dato lista, compuesto de un contador de elementos y un puntero al primer elemento
typedef struct tProcList {
    int contador;
    tPosProcL start;
} tProcList;


// AUXILIARES / INTERNAS

// Dado la dirección de memoria de una variable tProcList, inicializar una lista vacía
void PList_aux_createEmptyList(tProcList *lista);

// Comprueba si una lista (tProcList) está vacía
bool PList_aux_isEmptyList(tProcList lista);

// Devuelve la posición del primer elemento de la lista
tPosProcL PList_aux_first(tProcList lista);

// Devuelve la posición del último elemento de la lista
tPosProcL PList_aux_last(tProcList lista);

// Devuelve la posición del elemento siguiente a la posición dada
tPosProcL PList_aux_next(tPosProcL posicion, tProcList lista);

// Devuelve la posición del elemento anterior a la posición dada
tPosProcL PList_aux_previous(tPosProcL posicion, tProcList lista);

// Inserta un item en la posición indicada, de no indicarse ninguna (MNULL) se añade al final de la lista.
// Devuelve true/false dependiendo de si se ha podido o no insertar a la lista. El tamaño máximo es 1000.
bool PList_aux_insertItem(pid_t pid, time_t time, tCommandLine command, tPosProcL posicion, tProcList *lista);

// Elimina el elemento de la posición indicada. No se devuelve si la eliminación fue ejecutada.
void PList_aux_deleteAtPosition(tPosProcL posicion, tProcList *lista);

#endif //PROLIST_H
