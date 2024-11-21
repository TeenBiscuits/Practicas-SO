//
// Created by Pablo Portas y Pablo Míguez on 18/11/24.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "memoria.h"

#include <time.h>

typedef struct BloqueMemoria {
    void *direccion;
    size_t tamanio;
    time_t timestamp;
    char type[15];
    char extra_info[256];
    struct BloqueMemoria *next;
}BloqueMemoria;

BloqueMemoria *cabecaMemoria = NULL;

void allocate_malloc(size_t size) {
    if (size == 0) {
        printf("Error al alocar memoria\n");
        return;
    }
    void *ptr = malloc(size);
    if (ptr == NULL) {
        perror("malloc");
        return;
    }

    time_t now = time(NULL);
    char timestamp_str[30];
    strftime(timestamp_str, sizeof(timestamp_str), "%Y-%m-%d %H:%M:%S", localtime(&now));
}

void deallocate_malloc(void *address) {
    BloqueMemoria *current = cabecaMemoria;
    BloqueMemoria *prev = NULL;

    while (current != NULL) {
        if (current->direccion == address && strcmp(current->type, "malloc") == 0) {
            free(current->direccion);
            if (prev == NULL) {
                cabecaMemoria = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            printf("Deallocated malloc block at address %p\n", address);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Error: Address %p not found in allocated blocks.\n", address);
}






