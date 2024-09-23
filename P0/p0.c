// Pablo Portas López
// Pablo Míguez Mouiño

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include <stdbool.h>
#include <limits.h>
// No compilable en mac
// #include <linux/limits.h>

#define MAX 2048
#define MAX_ARG 1000
#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX 255  // Definir HOST_NAME_MAX si no está declarado
#endif

void imprimirPrompt();

void leerEntrada(char comando[MAX]);

bool procesarEntrada(char comando[MAX]);

void dividir_comando(char *comando, char **args);

void processid();

int main() {
    bool terminado = false;
    char comando[MAX];
    while (!terminado) {
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
        printf("Error: Imposible conseguir el nombre de usuario.\n");
        user = "usuario";
    }
    if (gethostname(hostname, sizeof(hostname)) != 0) {
        printf("Error: Imposible conseguir el nombre de la máquina.\n");
        strcpy(hostname, "maquina");
    }
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s@%s:%s$ ", user, hostname, cwd);
    } else {
        printf("Error: Imposible conseguir la ruta del directorio.\n");
        printf("%s@%s$ ", user, hostname);
    }
};

void leerEntrada(char comando[MAX]) {
    fgets(comando, MAX, stdin);
    comando[strcspn(comando, "\n")] = '\0';
};

bool procesarEntrada(char comando[MAX]) {
    if (strcmp(comando, "pid\0") == 0) {
        processid();
        return false;
    }
    if (strcmp(comando, "exit\0") == 0) {
        printf("Saliendo del shell...\n");
        return true;
    }
    if (strcmp(comando, "\0") == 0) {
        return false;
    }
    printf("Comando no reconocido...\n");
    return false;
};

void processid() {

}

void dividir_comando(char *comando, char **args) {
    char *tokens;
    int i = 0;

    tokens = strtok(comando, " ");
    while (tokens != NULL) {
        args[i++] = tokens;
        tokens = strtok(NULL, " ");
    }
    args[i] = NULL;
}