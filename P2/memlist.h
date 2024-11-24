// Pablo Portas López           pablo.portas
// Pablo Míguez Mouiño          pablo.miguez.moino

#ifndef MEMLIST_H
#define MEMLIST_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// Implementación de una lista enlazada sencilla

#define MNULL NULL              // Elemento nulo de la lista, equivalente pero no reemplazable por NULL
#define MAX_MLIST_SIZE 1000     // Tamaño máximo de la lista

// Tipo de dato posición de lista, es un puntero a un nodo
typedef struct tNodeMem *tPosMemL;

typedef void *tDirL;

enum tAllocL { MALLOC, SHARED, MAPPED };

typedef char tFNameL[FILENAME_MAX];


// Struct de nodo, formado por la información guardada y un puntero al siguiente elemento.
struct tNodeMem {
    tDirL dir; // Dirección de la memoria asignada
    int size; // Tamaño en bits de la memoria asignada
    time_t time; // Fecha de asignación de memoria
    enum tAllocL alloc; // Tipo de asignación de memoria. Valores válidos: MALLOC, SHARED, MAPPED
    int smb_key; // Clave para memory blocks
    tFNameL file_name; // Nombre del archivo para archivos mapeados
    int file_desc; // Descriptor del archivo para archivos mapeados
    tPosMemL siguiente; // Puntero al siguiente nodo de la lista
};

// Tipo dato lista, compuesto de un contador de elementos y un puntero al primer elemento
typedef struct tMemList {
    int contador;
    tPosMemL start;
} tMemList;

// Asigna size bytes de memoria con malloc y lo registra en el memorial.
// Devuelve la dirección de la memoria asignada o NULL en caso de fallo.
void *MList_add_malloc(int size);

// Elimina la primera dirección asignada con malloc que encuentre del mismo tamaño size
// Si no lo encuentra imprime por pantalla un error
void MList_remove_malloc(int size);

// Libera toda la memoria asignada y borra el memorial completo
void MList_delete_all();

// Imprime por pantalla la lista de bloques asignados dependiendo de cada tipo de asignación
// De enviarse como parámetro -1 se imprimen todos los tipos de asignaciones
void MList_print(enum tAllocL type_of_alloc);

// AUXILIARES / INTERNAS

// Dado la dirección de memoria de una variable tMemList, inicializar una lista vacía
void MList_aux_createEmptyList(tMemList *lista);

// Comprueba si una lista (tMemList) está vacía
bool MList_aux_isEmptyList(tMemList lista);

// Devuelve la posición del primer elemento de la lista
tPosMemL MList_aux_first(tMemList lista);

// Devuelve la posición del último elemento de la lista
tPosMemL MList_aux_last(tMemList lista);

// Devuelve la posición del elemento siguiente a la posición dada
tPosMemL MList_aux_next(tPosMemL posicion, tMemList lista);

// Devuelve la posición del elemento anterior a la posición dada
tPosMemL MList_aux_previous(tPosMemL posicion, tMemList lista);

// Inserta un item en la posición indicada, de no indicarse ninguna (MNULL) se añade al final de la lista.
// Devuelve true/false dependiendo de si se ha podido o no insertar a la lista. El tamaño máximo es 1000.
bool MList_aux_insertItem(tDirL direccion, int size, time_t alloct_time, enum tAllocL type_of_alloc, int smb_key,
                          tFNameL file_name, int file_descriptor, tPosMemL posicion, tMemList *lista);

// Elimina el elemento de la posición indicada. No se devuelve si la eliminación fue ejecutada.
void MList_aux_deleteAtPosition(tPosMemL posicion, tMemList *lista);

void MList_aux_printNode(tPosMemL posicion);

#endif //MEMLIST_H
