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

#include "color.h"
#include "list.h"


#define MAX_FILES 100

typedef struct {
    int desc;
    char filename[PATH_MAX];
    char mode[3];
} OpenFile;

struct CMD {
    char *comando;

    void (*funcion)(int, char **);
};

#endif
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

void Cmd_historic(int NumTrozos, char *trozos[]);

void Cmd_exit();

void add_to_historic();

void delete_historic(tList *historial);

void Cmd_makedir(int NumTrozos, char *trozos[]);

void Cmd_makefile(int NumTrozos, char *trozos[]);

void Cmd_listfile(int NumTrozos, char *trozos[]);

void Cmd_cwd(int NumTrozos, char *trozos[]);

void Cmd_listdir(int NumTrozos, char *trozos[]);

void recursive_list(const char *dirName);

void Cmd_reclist(int NumTrozos, char *trozos[]);

void recursive_revlist(const char *dirName);

void Cmd_revlist(int NumTrozos, char *trozos[]);

void Cmd_erase(int NumTrozos, char *trozos[]);

void Cmd_delrec(const char *path);
