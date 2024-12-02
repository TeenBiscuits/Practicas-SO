// Pablo Portas López           pablo.portas
// Pablo Míguez Mouiño          pablo.miguez.moino

#include "procesos.h"
#include "help.h"
#include "auxiliar.h"
#include "color.h"

#include <stdio.h>
#include <unistd.h>
#include <pwd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

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

    execv(trozos[1], &trozos[1]);
    exit(255);
}

void Cmd_execpri(int NumTrozos, char *trozos[]) {
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
