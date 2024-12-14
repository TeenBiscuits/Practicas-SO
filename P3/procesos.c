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
#include <time.h>

extern char **environ;

void Cmd_getuid(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]) {
    if (NumTrozos >= 1 && !strcmp(trozos[1], "-?")) {
        Help_getuid();
        return;
    }
    printf("Credencial real: %d, (%s)\n", getuid(), getpwuid(getuid())->pw_name);
    printf("Credencial efectiva: %d, (%s)\n", geteuid(), getpwuid(geteuid())->pw_name);
}

void Cmd_setuid(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]) {
    if (NumTrozos == 1 && (!strcmp(trozos[1], "-?") || !strcmp(trozos[1], "-l")))
        Help_setuid();
    else if (NumTrozos == 1 && setuid(atoi(trozos[1])) == -1)
        Aux_general_Imprimir_Error("Imposible cambiar credencial");
    else if (NumTrozos >= 2 && !strcmp(trozos[1], "-l") && seteuid(getpwnam(trozos[2])->pw_uid) == -1)
        Aux_general_Imprimir_Error("Imposible cambiar credencial");
    else Cmd_getuid(0, trozos, argc, argv, env);
}

void Cmd_showvar(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]) {
    if (NumTrozos == 0) {
        Aux_processos_show(env, "main arg3");
        return;
    }
    if (!strcmp(trozos[1], "-?")) {
        Help_showvar();
        return;
    }
    for (int i = 1; i <= NumTrozos; i++) {
        if (getenv(trozos[i]) == NULL) Aux_general_Imprimir_Error("Variable no encontrada");
        else {
            size_t longitud_var = strlen(trozos[i]);
            for (int j = 0; env[j] != NULL; j++)
                if (!strncmp(trozos[i], env[j], longitud_var))
                    printf("Con arg3 main %s(%p) @%p\n", env[j], env[j], env);
            for (int j = 0; environ[j] != NULL; j++)
                if (!strncmp(trozos[i], environ[j], longitud_var))
                    printf("  Con environ %s(%p) @%p\n", environ[j], environ[j], environ);
            printf("   Con getenv %s\n", getenv(trozos[i]));
        }
    }
}

void Cmd_changevar(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]) {
    if (NumTrozos < 3) {
        Help_changevar();
        return;
    }

    size_t longitud_var = strlen(trozos[2]);
    char newenv[1024]; // Por poner un valor
    strcpy(newenv, trozos[2]);
    strcat(newenv, "=");
    strcat(newenv, trozos[3]);
    char *aux = NULL;
    char **environment = NULL;

    if (!strcmp(trozos[1], "-a") || !strcmp(trozos[1], "-e")) {
        if (!strcmp(trozos[1], "-a")) environment = env;
        if (!strcmp(trozos[1], "-e")) environment = environ;
        if (environment == NULL) return;

        for (int i = 0; environment[i] != NULL; i++)
            if (!strncmp(trozos[2], environment[i], longitud_var))
                aux = environment[i];

        if (aux == NULL) Aux_general_Imprimir_Error("Variable no encontrada");
        else strcpy(aux, newenv);
    }
    if (!strcmp(trozos[1], "-p") && putenv(newenv) != 0)
        Aux_general_Imprimir_Error("");
}

void Cmd_subsvar(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]) {
    if (NumTrozos < 4) {
        Help_subsvar();
        return;
    }

    size_t longitud_var = strlen(trozos[2]);
    char newenv[1024]; // Por poner un valor
    strcpy(newenv, trozos[3]);
    strcat(newenv, "=");
    strcat(newenv, trozos[4]);
    char *aux = NULL;
    char **environment = NULL;

    if (!strcmp(trozos[1], "-a")) environment = env;
    if (!strcmp(trozos[1], "-e")) environment = environ;
    if (environment == NULL) return;

    for (int i = 0; environment[i] != NULL; i++)
        if (!strncmp(trozos[2], environment[i], longitud_var))
            aux = environment[i];

    if (aux == NULL) Aux_general_Imprimir_Error("Variable no encontrada");
    else strcpy(aux, newenv);
}

void Cmd_environ(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]) {
    if (NumTrozos == 0) Aux_processos_show(env, "main arg3");
    else {
        if (!strcmp(trozos[1], "-?")) Help_environ();
        if (!strcmp(trozos[1], "-environ")) Aux_processos_show(environ, "environ");
        if (!strcmp(trozos[1], "-addr")) Aux_processos_show(env, "main arg3");
    }
}

void Cmd_fork(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]) {
    if (NumTrozos >= 1 && !strcmp(trozos[1], "-?")) {
        Help_fork();
        return;
    }
    pid_t pid = fork();
    if (pid == -1) Aux_general_Imprimir_Error("No se pudo crear el proceso");
    else waitpid(pid, NULL, 0);
}

void Cmd_search(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]) {
    if (NumTrozos == 0) {
        SList_show_all();
        return;
    }
    if (!strcmp(trozos[1], "-?")) Help_search();
    if (!strcmp(trozos[1], "-clear")) SList_delete_all();
    if (!strcmp(trozos[1], "-path")) SList_import_path();
    if (!strcmp(trozos[1], "-add") && NumTrozos >= 2) SList_add(trozos[2]);
    if (!strcmp(trozos[1], "-del") && NumTrozos >= 2) SList_delete(trozos[2]);
}

void Cmd_exec(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]) {
    if (NumTrozos == 0 || (NumTrozos >= 1 && !strcmp(trozos[1], "-?"))) {
        Help_exec();
        return;
    }

    char *newenv[MAX_INPUT];
    int i = Aux_procesos_progspec((NumTrozos - 1), &trozos[1], newenv);
    if (Aux_procesos_Execpve(&trozos[i + 1], newenv,NULL) < 0) Aux_general_Imprimir_Error("");
}

void Cmd_execpri(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]) {
    if (NumTrozos < 2) {
        Help_execpri();
        return;
    }
    int prio = atoi(trozos[1]);
    char *newenv[MAX_INPUT];
    int i = Aux_procesos_progspec((NumTrozos - 2), &trozos[2], newenv);
    int aux = Aux_procesos_Execpve(&trozos[i + 2],NULL, &prio);
    if (aux == -1) Aux_general_Imprimir_Error("");
    if (aux == -2) Aux_general_Imprimir_Error("Imposible cambiar prioridad");
}

void Cmd_fg(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]) {
    if (NumTrozos == 0 || (NumTrozos >= 1 && !strcmp(trozos[1], "-?"))) {
        Help_fg();
        return;
    }
    pid_t pid = fork();

    if (pid == -1) Aux_general_Imprimir_Error("Error al crear el proceso");
    else if (pid == 0) {
        char *newenv[MAX_INPUT];
        int i = Aux_procesos_progspec((NumTrozos - 1), &trozos[1], newenv);
        printf("%d", i);
        Aux_procesos_Execpve(&trozos[i + 1],NULL,NULL);
        Aux_general_Imprimir_Error("");
        exit(EXIT_FAILURE);
    } else waitpid(pid, NULL, 0);
}

void Cmd_fgpri(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]) {
    if (NumTrozos < 2) {
        Help_fgpri();
        return;
    }
    pid_t pid = fork();
    int prio = atoi(trozos[1]);

    if (pid == -1) Aux_general_Imprimir_Error("Error al crear el proceso");
    else if (pid == 0) {
        char *newenv[MAX_INPUT];
        int i = Aux_procesos_progspec((NumTrozos - 2), &trozos[2], newenv);
        Aux_procesos_Execpve(&trozos[i + 2],NULL, &prio);
        Aux_general_Imprimir_Error("");
        exit(EXIT_FAILURE);
    } else waitpid(pid, NULL, 0);
}

void Cmd_back(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]) {
    if (NumTrozos == 0 || (NumTrozos >= 1 && !strcmp(trozos[1], "-?"))) {
        Help_back();
        return;
    }
    pid_t pid = fork();

    char *newenv[MAX_INPUT];
    int i = Aux_procesos_progspec((NumTrozos - 1), &trozos[1], newenv);

    if (pid == -1) Aux_general_Imprimir_Error("Error al crear el proceso");
    else if (pid == 0) {
        pid_t sid = setsid();
        if (sid < 0) {
            Aux_general_Imprimir_Error("Error al crear una nueva sesión");
            exit(EXIT_FAILURE);
        }
        Aux_procesos_Execpve(&trozos[i + 1],NULL,NULL);
        Aux_general_Imprimir_Error("");
        exit(EXIT_FAILURE);
    } else PList_add(pid, ACTIVE, &trozos[i + 1]);
}

void Cmd_backpri(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]) {
    if (NumTrozos < 2) {
        Help_backpri();
        return;
    }
    pid_t pid = fork();
    int prio = atoi(trozos[1]);

    char *newenv[MAX_INPUT];
    int i = Aux_procesos_progspec((NumTrozos - 2), &trozos[2], newenv);

    if (pid == -1) Aux_general_Imprimir_Error("Error al crear el proceso");
    else if (pid == 0) {
        pid_t sid = setsid();
        if (sid < 0) {
            Aux_general_Imprimir_Error("Error al crear una nueva sesión");
            exit(EXIT_FAILURE);
        }
        Aux_procesos_Execpve(&trozos[i + 2],NULL, &prio);
        Aux_general_Imprimir_Error("");
        exit(EXIT_FAILURE);
    } else PList_add(pid, ACTIVE, &trozos[i + 2]);
}

void Cmd_listjobs(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]) {
    if (NumTrozos >= 1 && !strcmp(trozos[1], "-?")) {
        Help_listjobs();
        return;
    }
    PList_print_all();
}

void Cmd_deljobs(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]) {
    if (NumTrozos == 0) {
    } else if (!strcmp(trozos[1], "-?")) {
        Help_deljobs();
        return;
    } else if (!strcmp(trozos[1], "-term")) PList_delete(FINISHED);
    else if (!strcmp(trozos[1], "-sig")) PList_delete(SIGNALED);
    PList_print_all();
}

// Auxiliares

void Aux_procesos_Ejecutar_General(int NumTrozos, char *trozos[]) {
    pid_t pid = fork();

    if (pid == -1) Aux_general_Imprimir_Error("Error al crear el proceso");
    else if (pid == 0) {
        char *newenv[MAX_INPUT];
        int i = Aux_procesos_progspec(NumTrozos, trozos, newenv);
        Aux_procesos_Execpve(&trozos[i], newenv,NULL);
        Aux_general_Imprimir_Error("");
        exit(1);
    } else waitpid(pid, NULL, 0); // Proceso padre
}

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

void Aux_processos_show(char **env, char *nombre_entorno) {
    int i = 0;

    while (env[i] != NULL) {
        printf("%p->%s[%d]=(%p) %s\n", &env[i],
               nombre_entorno, i, env[i], env[i]);
        i++;
    }
}

char *Aux_procesos_search_env(char *variable, char **env) {
    size_t longitud_var = strlen(variable);
    for (int i = 0; env[i] != NULL; i++) {
        if (!strncmp(variable, env[i], longitud_var)) return env[i];
    }
    return NULL;
}

int Aux_procesos_progspec(int NumTrozos, char **trozos, char **newenv) {
    char *aux;
    for (int i = 0; i <= NumTrozos; i++) {
        if ((aux = Aux_procesos_search_env(trozos[i], environ)) == NULL) {
            return i;
        } else newenv[i] = aux;
    }
    return 0;
}
