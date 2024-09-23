// Pablo Portas López
// Pablo Míguez Mouiño
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include <stdbool.h>
#include <limits.h>
#include "comandos.h"
#include "color.h"

//COMANDOS_BÁSICOS

void authors(int NumTrozos, char *trozos[]){
    if(NumTrozos==1){
        printf("Pablo Míguez Muiño .................................. \n Pablo Portas López ..................................\n");
        printf("pablo.miguez.muino@udc.es\npablo.portas@udc.es\n");
    }else if ((NumTrozos==2 && strcmp(trozos[1], "-l")==0)){
        printf("pablo.miguez.muino@udc.es\npablo.portas@udc.es\n");
    }else if (NumTrozos==2 && strcmp(trozos[1],"-n")==0){
        printf("Pablo Míguez Muiño .................................. \n Pablo Portas López ..................................\n");
    }else
        printf(ANSI_COLOR_RED "Error: Opción no reconocida.\n Usa el comando 'authors -l' para obtener solamente los logins.\n Usa el comando 'authors -n' para obtener solamente los nombres\n Usa el comando 'authors' para obtener tanto los logins como los nombres\n"  ANSI_COLOR_RESET);

}

void pid(){
    pid_t process_id = getpid();
    printf("El identificador del proceso es %d\n", process_id);
}

void ppid(){
    pid_t pprocess_id = getppid();
    printf("El identificador del proceso padre es %d\n", pprocess_id);
}

void cd (int NumTrozos, char *args[]){

}