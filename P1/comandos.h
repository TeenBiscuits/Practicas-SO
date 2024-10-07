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

#include "color.h"
#include "list.h"


#define MAX_FILES 100

typedef struct {
    int desc;
    char filename[PATH_MAX];
    char mode[3];
} OpenFile;

struct CMD{
    char * comando;
    void (* funcion) (int, char **);
};

// Estructura de una función de comandos
// void comando(int NumTrozos, char *trozos[]);

void Cmd_authors(int NumTrozos, char *trozos[]);

void Cmd_pid(int NumTrozos, char *trozos[]);

void Cmd_ppid(int NumTrozos, char *trozos[]);

void Cmd_cd(int NumTrozos, char *trozos[]);

void Cmd_date(int NumTrozos, char *trozos[]);

void Cmd_open(int NumTrozos, char *trozos[]);

void Cmd_close(int NumTrozos, char *trozos[]);

void Cmd_dup(int NumTrozos, char *trozos[]);

void Cmd_infosys(int NumTrozos, char *trozos[]);

void Cmd_help(int NumTrozos, char *trozos[]);

void Cmd_historic(int NumTrozos, char *trozos[], tList *historial);

void Cmd_exit();

#endif //COMANDOS_H
