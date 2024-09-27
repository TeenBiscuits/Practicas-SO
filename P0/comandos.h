// Pablo Portas López
// Pablo Míguez Mouiño

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

void authors(int NumTrozos, char *trozos[]);

void pid();

void ppid();

void Cmd_cd(int NumTrozos, char *trozos[]);

void Cmd_date(int NumTrozos, char *trozos[]);

void Cmd_open(int NumTrozos, char *trozos[]);

void Cmd_close(int NumTrozos, char *trozos[]);

void Cmd_dup(int NumTrozos, char *trozos[]);

void Cmd_infosys(int NumTrozos, char *trozos[]);

void Cmd_help(int NumTrozos, char *trozos[]);

void Cmd_historic(int NumTrozos, char *trozos[], tList *historial);

#endif //COMANDOS_H
