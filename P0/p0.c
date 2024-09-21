#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include <linux/limits.h>

#define MAX 2048
#define MAX_ARG 1000

int main(){
    char comando[MAX];
    char cwd[PATH_MAX];
    while (1){
        if (getcwd(cwd,sizeof(cwd)) != NULL){
            printf("pablo@ordenador-de-pablo:%s$ ",cwd);
        }else{
            printf("pablo@ordenador-de-pablo$ (getcwd return error) ");
        }
        fgets(comando,MAX,stdin);
        comando[strcspn(comando, "\n")]=='\0';
        if (strcmp(comando, "exit")== '\0'){
            printf("Saliendo del shell...\n ");
            break;
        }
    }
    return 0;
}

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