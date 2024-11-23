// Pablo Portas López           pablo.portas
// Pablo Míguez Mouiño          pablo.miguez.moino

#ifndef COMANDOS_H
#define COMANDOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <limits.h>
#include <stdbool.h>
#include <sys/utsname.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>

#include "list.h"

// COMANDOS BÁSICOS P0 + P1

#define MAX_FILES 100   // Máximos archivos posibles de abrir

// Struct para almacenar los archivos abierto
typedef struct {
    int desc;
    char filename[PATH_MAX];
    char mode[3];
} OpenFile;

// Struct para almacenar las equivalencias entre "comando" y función
struct CMD {
    char *comando;

    void (*funcion)(int, char **);
};

// Estructura de una función de comandos
// void comando(int NumTrozos, char *trozos[]);

// P0

// Imprime por pantalla los autores del proyecto. Acepta dos parámetros:
// [-l|-n] Solo logins y solo nombres respectivamente
void Cmd_authors(int NumTrozos, char *trozos[]);

// Imprime por pantalla el pid del shell
void Cmd_pid(int NumTrozos, char *trozos[]);

// Imprime por pantalla el ppid del shell
void Cmd_ppid(int NumTrozos, char *trozos[]);

// Cambia el cwd del shell al path específicado [dir]
void Cmd_cd(int NumTrozos, char *trozos[]);

// Imprime por pantalla la fecha actual. Acepta dos parámetros:
// [-t|-d] Solo hora y solo fecha respectivamente
void Cmd_date(int NumTrozos, char *trozos[]);

// Lista los archivos abiertos o abre el archivo especificado
// dado un path y un modo. Los modos aceptados son:
// cr, ap, ex, ro, rw, wo, tr.
void Cmd_open(int NumTrozos, char *trozos[]);

// Cierra el archivo especificado dado un file descriptor
void Cmd_close(int NumTrozos, char *trozos[]);

// Duplica el file descriptor especificado
void Cmd_dup(int NumTrozos, char *trozos[]);

// Imprime por pantalla la información del equipo
void Cmd_infosys(int NumTrozos, char *trozos[]);

// Imprime una lista de los comandos disponibles o la ayuda
// de un comando dado
void Cmd_help(int NumTrozos, char *trozos[]);

// Imprime por pantalla el historial de todos los inputs del usuario
// Acepta dos parámetros: [N|-N] Imprimir el comando N o imprimir los
// últimos N comandos
void Cmd_historic(int NumTrozos, char *trozos[]);

// Termina con el shell y borra el historial
void Cmd_exit();

// P1

void Cmd_makefile(int NumTrozos, char *trozos[]);

void Cmd_makedir(int NumTrozos, char *trozos[]);

void Cmd_listfile(int NumTrozos, char *trozos[]);

void Cmd_cwd(int NumTrozos, char *trozos[]);

void Cmd_listdir(int NumTrozos, char *trozos[]);

void Cmd_reclist(int NumTrozos, char *trozos[]);

void Cmd_revlist(int NumTrozos, char *trozos[]);

void Cmd_erase(int NumTrozos, char *trozos[]);

void Cmd_delrec(int NumTrozos, char *trozos[]);

// FUNCIONES AUXILIARES

// Imprime por pantalla el "Error [N de Error]: [Descripción del error]"
// en rojo porque mola el color rojo
void Imprimir_Error();

// Añade un input al histórico
void add_to_historic();

// Borra el historial completo
void delete_historic(tList *historial);

int get_open_flags(const char *mode);

void list_open_files();

void Aux_reclist(char *dir_name, bool show_hidden, bool show_long, bool show_acc, bool show_link);

void Aux_revlist(char *dir_name, bool show_long, bool show_acc, bool show_link, bool show_hid, char *parent_dir);

void print_permissions(mode_t mode);

char LetraTF(mode_t m);

char *ConvierteModo(mode_t m, char *permisos);

void Aux_fileinfo(char *path, char *name, bool show_long, bool show_acc, bool show_link);

void Aux_delrec(char *dir_name);

#endif
