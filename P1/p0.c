// Pablo Portas López           pablo.portas
// Pablo Míguez Mouiño          pablo.miguez.moino

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <limits.h>
// No compilable en mac
// #include <linux/limits.h>
#include "list.h"
#include "color.h"
#include "comandos.h"

#define MAX_FILES 100
#define MAX 2048
#define MAX_ARG 1000
#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX 255  // Definir HOST_NAME_MAX si no está declarado
#endif

void imprimirPrompt();

void leerEntrada(char comando[MAX]);

bool procesarEntrada(char comando[MAX]);

int dividir_comando(char *comando, char **args);

int main() {
    bool terminado = false;
    while (!terminado) {
        char comando[MAX];
        imprimirPrompt();
        leerEntrada(comando);
        terminado = procesarEntrada(comando);
    }
    return 0;
}

void imprimirPrompt() {
    char cwd[PATH_MAX];
    char hostname[HOST_NAME_MAX];
    char *user = getenv("USER");
    if (user == NULL) {
        printf(ANSI_COLOR_RED "Error: Imposible conseguir el nombre de usuario.\n" ANSI_COLOR_RESET);
        user = "usuario";
    }
    if (gethostname(hostname, sizeof(hostname)) != 0) {
        printf(ANSI_COLOR_RED "Error: Imposible conseguir el nombre de la máquina.\n" ANSI_COLOR_RESET);
        strcpy(hostname, "maquina");
    }
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf(ANSI_COLOR_MAGENTA "%s@%s" ANSI_COLOR_RESET ":" ANSI_COLOR_BLUE "%s" ANSI_COLOR_RESET "$ ", user, hostname,
               cwd);
    } else {
        printf(ANSI_COLOR_RED "Error: Imposible conseguir la ruta del directorio.\n" ANSI_COLOR_RESET);
        printf(ANSI_COLOR_MAGENTA "%s@%s" ANSI_COLOR_RESET "$ ", user, hostname);
    }
};

void leerEntrada(char comando[MAX]) {
    fgets(comando, MAX, stdin);
    comando[strcspn(comando, "\n")] = '\0';
    if (strcmp(comando, "\0") != 0) add_to_historic(comando);
};

struct CMD C[] = {
    {"authors",Cmd_authors},
    {"pid",Cmd_pid},
    {"ppid",Cmd_ppid},
    {"cd",Cmd_cd},
    {"date",Cmd_date},
    {"open",Cmd_open},
    {"close",Cmd_close},
    {"dup",Cmd_dup},
    {"infosys",Cmd_infosys},
    {"help",Cmd_help},
    {"historic",Cmd_historic},
    {"exit",Cmd_exit},
    {"quit",Cmd_exit},
    {"bye",Cmd_exit}
};

bool procesarEntrada(char comando[MAX]) {
    if (strcmp(comando, "\0") == 0) return false;

    char *Trozos[MAX_ARG];
    const int NumeroT = dividir_comando(comando, Trozos);

    for (int i = 0; i < 13; i++) {
        if (strcmp(Trozos[0], C[i].comando) == 0) {
            C[i].funcion(NumeroT, Trozos);
            return false;
        }
    }

    printf(ANSI_COLOR_YELLOW "Comando no reconocido...\n" ANSI_COLOR_RESET);
    return false;
};

int dividir_comando(char *comando, char **args) {
    char *tokens;
    int i = 0;

    tokens = strtok(comando, " ");
    while (tokens != NULL) {
        args[i++] = tokens;
        tokens = strtok(NULL, " ");
    }
    args[i] = NULL;
    return i - 1;
}
