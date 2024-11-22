// Pablo Portas López           pablo.portas
// Pablo Míguez Mouiño          pablo.miguez.moino

#ifndef MEMORIA_H
#define MEMORIA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>


void funcion1();
void funcion2();
void funcion3();

void imprimir_funciones();

void memory_funcs();

void registrar_bloque(void *direccion, size_t tamano);

void liberar_bloque(void *direccion);

void imprimir_bloques_asignados();

void *asignar_memoria(size_t tamano);

void liberar_memoria(void *direccion);

void memory_blocks();

void imprimir_variables();

void memory_vars();

void Do_MemPmap();

void memory_all();

void *direccion_inicio(const char *arg);

size_t cantidad_bytes(const char *arg);

void volcar_memoria(const uint8_t *ptr, size_t cantidad_bytes);

void *convertir_direccion(const char *direccion_str);

FILE *abrirArchivo(const char *filename);

size_t leer_bytes(FILE *file, void *addr, size_t tamano);

void cerrar_archivo(FILE *file);

size_t escribir_bytes(FILE *file, const void *addr, size_t count);

ssize_t leer_desde_descriptor(int fd, void *addr, size_t count);

ssize_t escribir_en_descriptor(int fd, const void *addr, size_t count);

void recursive_function(int n, int *param_address);


//////////////////CABECERAS DE LOS COMANDOS/////////////////////////////////////7
void Cmd_memfill(int NumTrozos, char *trozos[]);

void Cmd_memdump(int NumTrozos, char *trozos[]);

void Cmd_memory(int NumTrozos, char *args[]);

void Cmd_readfile(int NumTrozos, char *args[]);

void Cmd_writefile(int NumTrozos, char *args[]);

void Cmd_read(int NumTrozos, char *args[]);

void Cmd_write(int NumTrozos, char *args[]);

void Cmd_recurse(int NumTrozos, char *args[]);
#endif //MEMORIA_H
