// Pablo Portas López           pablo.portas
// Pablo Míguez Mouiño          pablo.miguez.moino

#include "procesos.h"
#include "help.h"
#include "auxiliar.h"
#include "color.h"

#include <stdio.h>
#include <unistd.h>
#include <pwd.h>
#include <string.h>

void Cmd_getuid(int NumTrozos, char *trozos[]) {
    if (NumTrozos >= 1 && !strcmp(trozos[1], "-?")) {
        Help_getuid();
        return;
    }
    printf("Credencial real: %d, (%s)\n", getuid(), getpwuid(getuid())->pw_name);
    printf("Credencial efectiva: %d, (%s)\n", geteuid(), getpwuid(geteuid())->pw_name);
}

void Cmd_setuid(int NumTrozos, char *trozos[]) {
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
}

void Cmd_search(int NumTrozos, char *trozos[]) {
}

void Cmd_exec(int NumTrozos, char *trozos[]) {
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
