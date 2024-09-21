#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"

#define MAX 2048
#define MAX_ARG 1000


//BUCLE BÁSICO DEL SHELL
int main(){
    char comando[MAX];
    char argumentos[MAX_ARG];
    while (1){
        printf("/home/user/pablopablo's/shell> ");
        fgets(comando,MAX,stdin);
        comando[strcspn(comando, "\n")]=='\0';
        if (strcmp(comando, "exit")== '\0'){
            printf("Saliendo del shell...\n ");
            break;
        }
    
    return 0;
}


//FUNCIÓN QUE DIVIDE LAS CADENAS DE COMANDOS EN TOKENS
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

