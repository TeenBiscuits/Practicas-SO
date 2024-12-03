// Pablo Portas López           pablo.portas
// Pablo Míguez Mouiño          pablo.miguez.moino

#include "procesos.h"
#include "help.h"
#include "auxiliar.h"
#include "color.h"
#include "proclist.h"
#include "searchlist.h"

#include <stdio.h>
#include <unistd.h>
#include <pwd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <errno.h>

void Cmd_getuid(int NumTrozos, char *trozos[]) {
    if (NumTrozos >= 1 && !strcmp(trozos[1], "-?")) {
        Help_getuid();
        return;
    }
    printf("Credencial real: %d, (%s)\n", getuid(), getpwuid(getuid())->pw_name);
    printf("Credencial efectiva: %d, (%s)\n", geteuid(), getpwuid(geteuid())->pw_name);
}

void Cmd_setuid(int NumTrozos, char *trozos[]) {
    if (NumTrozos >= 1 && !strcmp(trozos[1], "-?")) {
        Help_setuid();
        return;
    }
    if (NumTrozos == 0) Cmd_getuid(0, trozos);
    else if (setuid(atoi(trozos[1])) == -1) Aux_general_Imprimir_Error("Imposible cambiar credencial");
}

void Cmd_showvar(int NumTrozos, char *trozos[]) {
}

void Cmd_changevar(int NumTrozos, char *trozos[]) {
}

void Cmd_subsvar(int NumTrozos, char *trozos[]) {
}

void Cmd_environ(int NumTrozos, char *trozos[]) {
}

void Cmd_fork(int NumTrozos, char *trozos[]) {
    if (NumTrozos >= 1 && !strcmp(trozos[1], "-?")) {
        Help_fork();
        return;
    }
    pid_t pid = fork();
    if (pid == -1) Aux_general_Imprimir_Error("No se pudo crear el proceso");
    else waitpid(pid, NULL, 0);
}

void Cmd_search(int NumTrozos, char *trozos[]) {
}

void Cmd_exec(int NumTrozos, char *trozos[]) {
    if (NumTrozos == 0 || (NumTrozos >= 1 && !strcmp(trozos[1], "-?"))) {
        Help_exec();
        return;
    }
    // TODO: CAMBIAR VARIABLES DE ENTORNO
    if (Aux_procesos_Execpve(&trozos[1],NULL,NULL) < 0) Aux_general_Imprimir_Error("");
}

void Cmd_execpri(int NumTrozos, char *trozos[]) {
    if (NumTrozos < 2) {
        Help_execpri();
        return;
    }
    int prio = atoi(trozos[1]);
    int aux = Aux_procesos_Execpve(&trozos[2],NULL, &prio);
    if (aux == -1) Aux_general_Imprimir_Error("");
    if (aux == -2) Aux_general_Imprimir_Error("Imposible cambiar prioridad");
}

void Cmd_fg(int NumTrozos, char *trozos[]) {
}

void Cmd_fgpri(int NumTrozos, char *trozos[]) {
}

void Cmd_back(int NumTrozos, char *trozos[]) {
}

void Cmd_backpri(int NumTrozos, char *trozos[]) {
}

void Cmd_listjobs(int NumTrozos, char *trozos[]) {
}

void Cmd_deljobs(int NumTrozos, char *trozos[]) {
}

// Auxiliares

char *Aux_procesos_Ejecutable(char *s) {
    static char path[PATH_MAX];
    struct stat st;
    tPosSearchL p;

    if (s == NULL || (p = SList_first()) == NULL)
        return s;
    if (s[0] == '/' || !strncmp(s, "./", 2) || !strncmp(s, "../", 3))
        return s; /*is an absolute pathname*/

    strncpy(path, p->path, PATH_MAX - 1);
    strncat(path, "/", PATH_MAX - 1);
    strncat(path, s, PATH_MAX - 1);
    if (lstat(path, &st) != -1)
        return path;
    while ((p = SList_next(p)) != NULL) {
        strncpy(path, p->path, PATH_MAX - 1);
        strncat(path, "/", PATH_MAX - 1);
        strncat(path, s, PATH_MAX - 1);
        if (lstat(path, &st) != -1)
            return path;
    }
    return s;
}

int Aux_procesos_Execpve(char *tr[], char **NewEnv, int *pprio) {
    /*NewEnv contains the address of the new environment*/
    /*pprio the address of the new priority*/
    /*NULL indicates no change in environment and/or priority*/
    char *p;

    if (tr[0] == NULL || (p = Aux_procesos_Ejecutable(tr[0])) == NULL) {
        errno = EFAULT;
        return -1;
    }
    if (pprio != NULL && setpriority(PRIO_PROCESS, getpid(), *pprio) == -1 && errno) {
        return -2;
    }

    if (NewEnv == NULL)
        return execv(p, tr);
    else
        return execve(p, tr, NewEnv);
}
