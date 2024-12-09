// Pablo Portas López           pablo.portas
// Pablo Míguez Mouiño          pablo.miguez.moino

#ifndef MEMORIA_H
#define MEMORIA_H

#include <stddef.h>
#include <sys/types.h>
#include <stdbool.h>

#define TAMANO 2048 // Tamaño de array en Aux_recurse_Recursiva()

// COMANDOS DE MEMORIA P2

// Asignar memoria
void Cmd_allocate(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]);

// Desasignar memoria
void Cmd_deallocate(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]);

void Cmd_memfill(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]);

void Cmd_memdump(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]);

void Cmd_memory(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]);

void Cmd_readfile(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]);

void Cmd_writefile(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]);

void Cmd_read(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]);

void Cmd_write(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]);

void Cmd_recurse(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]);

// Auxiliares

void Aux_allocate_malloc(int NumTrozos, char *trozos[]);

void Aux_deallocate_malloc(int NumTrozos, char *trozos[]);

void Aux_allocate_mmap(int NumTrozos, char *trozos[]);

void Aux_deallocate_mmap(int NumTrozos, char *trozos[]);

// Crea un bloque de memoria compartida con cierta clave y tamaño dados
void Aux_allocate_createshared(int NumTrozos, char *trozos[]);

// Elimina el bloque de clave dada del sistema PERO NO DESASIGNA LA MEMORIA
void Aux_deallocate_delkey(int NumTrozos, char *trozos[]);

// Asigna a memoria un bloque de memoria compartida al espacio del proceso
// La clave debe ser creada de antemano, fuera o no asignada a memoria
void Aux_allocate_shared(int NumTrozos, char *trozos[]);

// Desasigna la memoria dada una clave
void Aux_deallocate_shared(int NumTrozos, char *trozos[]);

void Aux_recurse_Recursiva(int n);

void Aux_memfill_LlenarMemoria(void *p, size_t cont, unsigned char byte);

void Aux_memory_dopmap(void);

void Aux_memory_funcs();

void Aux_memory_vars();

ssize_t Aux_readfile_LeerFichero(char *f, void *p, size_t cont);

bool Aux_validar_Parámetros (int fd, void *addr, size_t count);

#endif //MEMORIA_H
