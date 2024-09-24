// Pablo Portas López
// Pablo Míguez Mouiño
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>
#include "comandos.h"
#include "color.h"

//COMANDOS_BÁSICOS

#define MAX_BUFFER

void authors(int NumTrozos, char *trozos[]) {
    printf("%d\n", NumTrozos);
    if (NumTrozos == 0) {
        // Si solo se introduce "authors", imprime ambos nombres y correos
        printf("Pablo Míguez Muiño\nPablo Portas López\n");
        printf("pablo.miguez.muino@udc.es\npablo.portas@udc.es\n");
    }
    else if (NumTrozos == 1 && strcmp(trozos[1], "-l\0") == 0) {
        // Si el segundo argumento es "-l", imprime solo los correos
        printf("pablo.miguez.muino@udc.es\npablo.portas@udc.es\n");
    }
    else if (NumTrozos == 1 && strcmp(trozos[1], "-n\0") == 0) {
        // Si el segundo argumento es "-n", imprime solo los nombres
        printf("Pablo Míguez Muiño\nPablo Portas López\n");
    }
    else {
        // Si el argumento no es reconocido, imprime el mensaje de error
        printf(ANSI_COLOR_RED "Error: Opción no reconocida.\n" ANSI_COLOR_RESET);
        printf("Usa el comando 'authors -l' para obtener solamente los logins.\n");
        printf("Usa el comando 'authors -n' para obtener solamente los nombres.\n");
        printf("Usa el comando 'authors' para obtener tanto los logins como los nombres.\n");
    }
}

void pid(){
    pid_t process_id = getpid();
    printf("El identificador del proceso es %d\n", process_id);
}

void ppid(){
    pid_t pprocess_id = getppid();
    printf("El identificador del proceso padre es %d\n", pprocess_id);
}
void Cmd_cd(int NumTrozos, char *trozos[]) {
    // Si no se pasa argumento (NumTrozos == 1), cambiamos al directorio HOME del usuario
    if (NumTrozos == 0) {
        char *home = getenv("HOME");  // Obtener el directorio home del usuario
        if (home == NULL) {
            printf(ANSI_COLOR_RED "Error: No se pudo obtener el directorio HOME.\n" ANSI_COLOR_RESET);
        } else {
            if (chdir(home) != 0) {
                printf(ANSI_COLOR_RED "Error: No se pudo cambiar al directorio HOME.\n" ANSI_COLOR_RESET);
            }
        }
    } else if (NumTrozos == 1) {
        // Intentamos cambiar al directorio especificado en trozos[1]
        if (chdir(trozos[1]) != 0) {
            printf(ANSI_COLOR_RED "Error: No se pudo cambiar al directorio '%s'. Verifica que exista.\n" ANSI_COLOR_RESET, trozos[1]);
        }
    } else {
        // Si hay más de un argumento, mostramos un mensaje de error
        printf(ANSI_COLOR_RED "Error: Demasiados argumentos. Usa 'cd <directorio>' o 'cd' para cambiar al directorio HOME.\n" ANSI_COLOR_RESET);
    }
}//ACABAR nº error, cambiar de directorio

void Cmd_date(int NumTrozos, char *trozos[]){
    time_t t;
    struct tm *tm_info;
    char buffer[80];

    //Obtengo el timempo actual
    time(&t);
    tm_info = localtime(&t);

    if(NumTrozos==0){
        strftime(buffer, 80,"%d/%m/%Y %H:%M:%S\n", tm_info );
        printf("Fecha y hora actuales: %s\n", buffer);
    }
    else if (NumTrozos==1 && strcmp(trozos[1], "-t\0")==0){
        strftime(buffer, 80, "%H:%M:%S\n",tm_info);
        printf("Hora actual: %s\n", buffer);
    }
    else if (NumTrozos==1 && strcmp(trozos[1], "-d\0")==0){
        strftime(buffer, 80, "%d/%m/%Y\n",tm_info);
        printf("Fecha actual: %s\n", buffer);
    }
    else{
        printf(ANSI_COLOR_RED "Error: Opción no reconocida.\n" ANSI_COLOR_RESET);
        printf("Usa el comando 'date' para obtener la fecha y la hora.\n");
        printf("Usa el comando 'date -t' para obtener solo la hora.\n");
        printf("Usa el comando 'date -d' para obtener solo la fecha.\n");
    }



















}




