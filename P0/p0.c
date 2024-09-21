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

void imprimirPrompt();
void leerEntrada(char comando[MAX]);
bool procesarEntrada(char comando[MAX]);

int main(){
    bool terminado = false;
    char comando[MAX];
    while (!terminado){
        imprimirPrompt();
        leerEntrada(comando);
        terminado = procesarEntrada(comando);
    }
    return 0;
}

void imprimirPrompt(){
    char cwd[PATH_MAX];
    if (getcwd(cwd,sizeof(cwd)) != NULL){
        printf("pablo@ordenador-de-pablo:%s$ ",cwd);
    }else{
        printf("pablo@ordenador-de-pablo$ (getcwd return error) ");
    }
};

void leerEntrada(char comando[MAX]){
    fgets(comando,MAX,stdin);
    comando[strcspn(comando, "\n")] ='\0';
};

bool procesarEntrada(char comando[MAX]){
    if (strcmp(comando, "exit\0") == 0){
        printf("Saliendo del shell...\n");
        return true;
    }
};

void dividir_comando(char *comando, char **args){
    char *tokens;
    int i=0;

    tokens = strtok(comando, " ");
    while (tokens!=NULL){
        args[i++] = tokens;
        tokens = strtok(NULL, " ");
    }
    args[i]=NULL;
}