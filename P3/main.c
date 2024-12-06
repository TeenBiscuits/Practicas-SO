// Pablo Portas López           pablo.portas
// Pablo Míguez Mouiño          pablo.miguez.moino

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <limits.h>
#include <signal.h>

#include "auxiliar.h"
#include "color.h"
#include "comandos.h"
#include "hislist.h"
#include "help.h"
#include "memoria.h"
#include "procesos.h"

#define MAX_ARG 1000
#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX 255  // Definir HOST_NAME_MAX si no está declarado
#endif

// Imprime el prompt nombre de usuario + nombre de host + directorio actual
void imprimirPrompt();

// Leer la entrada por teclado del usuario.
void leerEntrada(char comando[MAXITEM]);

// De no ser nulo el comando recibido, se añade al histórico y se envían los parámetros a la función correcta
void procesarEntrada(char comando[MAXITEM], int argc, char * argv[], char *env[]);

// Dado un comando con sus parámetros (ya sean válidos o no) trocearlo en segmentos.
// El primero es la línea de texto sin procesar y el segundo un array de arrays de chars. Siendo [0] el comando y los siguientes los parámetros
int dividir_comando(char *input, char **trozos);

int main(int argc, char * argv[], char *env[]) {
    signal(SIGSEGV, Aux_general_handler);
    while (true) {
        char comando[MAXITEM];
        imprimirPrompt();
        leerEntrada(comando);
        procesarEntrada(comando, argc, argv, env);
    }
}

void imprimirPrompt() {
    char *user = getenv("USER");
    char cwd[PATH_MAX], hostname[HOST_NAME_MAX];
    if (user == NULL) {
        Aux_general_Imprimir_Error("Imposible conseguir el nombre de usuario");
        user = "usuario";
    }
    if (gethostname(hostname, sizeof(hostname)) != 0) {
        Aux_general_Imprimir_Error("Imposible conseguir el nombre de la máquina");
        strcpy(hostname, "maquina");
    }
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        Aux_general_Imprimir_Error("Imposible conseguir la ruta del directorio actual");
        strcpy(cwd, "NULL");
    } else {
        printf(ANSI_COLOR_MAGENTA "%s@%s" ANSI_COLOR_RESET ":" ANSI_COLOR_BLUE "%s" ANSI_COLOR_RESET "$ ", user,
               hostname, cwd);
    }
};

void leerEntrada(char comando[MAXITEM]) {
    fgets(comando, MAXITEM, stdin);
    comando[strcspn(comando, "\n")] = '\0'; // Substituimos el salto de línea por el fin de cadena
};

// Comandos y sus respectivas funciones
struct CMD C[] = {
    {"authors", Cmd_authors},
    {"pid", Cmd_pid},
    {"ppid", Cmd_ppid},
    {"cd", Cmd_cd},
    {"date", Cmd_date},
    {"historic", Cmd_historic},
    {"open", Cmd_open},
    {"close", Cmd_close},
    {"dup", Cmd_dup},
    {"infosys", Cmd_infosys},
    {"help", Cmd_help},
    {"quit", Cmd_exit},
    {"exit", Cmd_exit},
    {"bye", Cmd_exit},
    {"makefile", Cmd_makefile},
    {"makedir", Cmd_makedir},
    {"listfile", Cmd_listfile},
    {"cwd", Cmd_cwd},
    {"listdir", Cmd_listdir},
    {"reclist", Cmd_reclist},
    {"revlist", Cmd_revlist},
    {"erase", Cmd_erase},
    {"delrec", Cmd_delrec},
    {"allocate", Cmd_allocate},
    {"deallocate", Cmd_deallocate},
    {"memfill", Cmd_memfill},
    {"memdump", Cmd_memdump},
    {"memory", Cmd_memory},
    {"readfile", Cmd_readfile},
    {"writefile", Cmd_writefile},
    {"read", Cmd_read},
    {"write", Cmd_write},
    {"recurse", Cmd_recurse},
    {"getuid", Cmd_getuid},
    {"setuid", Cmd_setuid},
    {"showvar", Cmd_showvar},
    {"changevar", Cmd_changevar},
    {"subsvar", Cmd_subsvar},
    {"environ", Cmd_environ},
    {"fork", Cmd_fork},
    {"search", Cmd_search},
    {"exec", Cmd_exec},
    {"execpri", Cmd_execpri},
    {"fg", Cmd_fg},
    {"fgpri", Cmd_fgpri},
    {"back", Cmd_back},
    {"backpri", Cmd_backpri},
    {"listjobs", Cmd_listjobs},
    {"deljobs", Cmd_deljobs}
};

void procesarEntrada(char comando[MAXITEM], int argc, char * argv[], char *env[]) {
    if (strcmp(comando, "\0") == 0) return; // De ser un comando nulo, ni se procesa ni se añade al histórico

    HList_add(comando);

    char *Trozos[MAX_ARG];
    const int NumeroT = dividir_comando(comando, Trozos);

    for (int i = 0; i < sizeof(C) / sizeof(C[0]); i++) {
        if (strcmp(Trozos[0], C[i].comando) == 0) {
            C[i].funcion(NumeroT, Trozos, argc, argv, env);
            return;
        }
    }

    printf(ANSI_COLOR_YELLOW "Comando no reconocido...\n" ANSI_COLOR_RESET);
};

int dividir_comando(char *input, char **trozos) {
    char *rebanadas;
    int i = 0;
    // Partimos el input original, una cadena de texto terminada en '\0'
    rebanadas = strtok(input, " \t");
    for (; rebanadas != NULL; i++) {
        trozos[i] = rebanadas; // Se almacena la rebanada, en la primera iteración el comando
        rebanadas = strtok(NULL, " \t"); // Se prosigue desde donde dejo el corte anterior
    }
    trozos[i] = NULL;
    return i - 1; // Devolvemos el número de parámetros recibido
}
