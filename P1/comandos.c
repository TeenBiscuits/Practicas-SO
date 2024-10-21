// Pablo Portas López           pablo.portas
// Pablo Míguez Mouiño          pablo.miguez.moino

#include "comandos.h"
#include "list.h"

//COMANDOS_BÁSICOS

void Cmd_authors(int NumTrozos, char *trozos[]) {
    printf("%d\n", NumTrozos);
    if (NumTrozos == 0) {
        // Si solo se introduce "authors", imprime ambos nombres y correos
        printf("Pablo Míguez Muiño\nPablo Portas López\n");
        printf("pablo.miguez.muino@udc.es\npablo.portas@udc.es\n");
    } else if (NumTrozos == 1 && strcmp(trozos[1], "-l\0") == 0) {
        // Si el segundo argumento es "-l", imprime solo los correos
        printf("pablo.miguez.muino@udc.es\npablo.portas@udc.es\n");
    } else if (NumTrozos == 1 && strcmp(trozos[1], "-n\0") == 0) {
        // Si el segundo argumento es "-n", imprime solo los nombres
        printf("Pablo Míguez Muiño\nPablo Portas López\n");
    } else {
        // Si el argumento no es reconocido, imprime el mensaje de error
        printf(ANSI_COLOR_RED "Error: Opción no reconocida.\n" ANSI_COLOR_RESET);
        printf("Usa el comando 'authors -l' para obtener solamente los logins.\n");
        printf("Usa el comando 'authors -n' para obtener solamente los nombres.\n");
        printf("Usa el comando 'authors' para obtener tanto los logins como los nombres.\n");
    }
}

void Cmd_pid(int NumTrozos, char *trozos[]) {
    pid_t process_id = getpid();
    printf("El identificador del proceso es %d\n", process_id);
}

void Cmd_ppid(int NumTrozos, char *trozos[]) {
    pid_t pprocess_id = getppid();
    printf("El identificador del proceso padre es %d\n", pprocess_id);
}

void Cmd_cd(int NumTrozos, char *trozos[]) {
    // Si no se pasa argumento (NumTrozos == 1), cambiamos al directorio HOME del usuario
    if (NumTrozos == 0) {
        char *home = getenv("HOME"); // Obtener el directorio home del usuario
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
            printf(
                ANSI_COLOR_RED "Error: No se pudo cambiar al directorio '%s'. Verifica que exista.\n" ANSI_COLOR_RESET,
                trozos[1]);
        }
    } else {
        // Si hay más de un argumento, mostramos un mensaje de error
        printf(
            ANSI_COLOR_RED
            "Error: Demasiados argumentos. Usa 'cd <directorio>' o 'cd' para cambiar al directorio HOME.\n"
            ANSI_COLOR_RESET);
    }
} //ACABAR nº error, cambiar de directorio

void Cmd_date(int NumTrozos, char *trozos[]) {
    time_t t;
    struct tm *tm_info;
    char buffer[80];

    //Obtengo el timempo actual
    time(&t);
    tm_info = localtime(&t);

    if (NumTrozos == 0) {
        strftime(buffer, 80, "%d/%m/%Y %H:%M:%S\n", tm_info);
        printf("Fecha y hora actuales: %s\n", buffer);
    } else if (NumTrozos == 1 && strcmp(trozos[1], "-t\0") == 0) {
        strftime(buffer, 80, "%H:%M:%S\n", tm_info);
        printf("Hora actual: %s\n", buffer);
    } else if (NumTrozos == 1 && strcmp(trozos[1], "-d\0") == 0) {
        strftime(buffer, 80, "%d/%m/%Y\n", tm_info);
        printf("Fecha actual: %s\n", buffer);
    } else {
        printf(ANSI_COLOR_RED "Error: Opción no reconocida.\n" ANSI_COLOR_RESET);
        printf("Usa el comando 'date' para obtener la fecha y la hora.\n");
        printf("Usa el comando 'date -t' para obtener solo la hora.\n");
        printf("Usa el comando 'date -d' para obtener solo la fecha.\n");
    }
}

//Lista archivos abiertos
OpenFile open_files[MAX_FILES];
int open_file_count = 0; //Esto es el contador de archivos abiertos

int get_open_flags(const char *mode) {
    if (strcmp(mode, "cr\0") == 0)
        return O_CREAT | O_WRONLY;
    if (strcmp(mode, "ap\0") == 0)
        return O_APPEND | O_WRONLY;
    if (strcmp(mode, "ex\0") == 0)
        return O_CREAT | O_EXCL | O_WRONLY;
    if (strcmp(mode, "ro\0") == 0)
        return O_RDONLY;
    if (strcmp(mode, "rw\0") == 0)
        return O_RDWR;
    if (strcmp(mode, "wo\0") == 0)
        return O_WRONLY;
    if (strcmp(mode, "tr\0") == 0)
        return O_TRUNC | O_WRONLY;

    return -1;
}

void list_open_files() {
    if (open_file_count == 0) {
        printf("No hay archivos abiertos.\n");
        return;
    }

    printf("Archivos abiertos:\n");
    printf("Descriptor\tNombre\tModo\n");
    for (int i = 0; i < open_file_count; i++) {
        printf("%d\t\t%s\t%s\n", open_files[i].desc, open_files[i].filename, open_files[i].mode);
    }
}

void Cmd_open(int NumTrozos, char *trozos[]) {
    if (NumTrozos == 0) { list_open_files(); return; }
    if (NumTrozos != 2) {
        printf(ANSI_COLOR_RED "Error: Usa 'open [archivo] [modo]'.\n" ANSI_COLOR_RESET); return;
    }

    int flags = get_open_flags(trozos[2]), desc;
    if (flags == -1) {
        printf(ANSI_COLOR_RED "Error: Modo no reconocido.\n" ANSI_COLOR_RESET); return;
    }

    if ((desc = open(trozos[1], flags, 0644)) == -1) {
        perror("Error al abrir el archivo"); return;
    }

    if (open_file_count < MAX_FILES) {
        open_files[open_file_count].desc = desc;
        strncpy(open_files[open_file_count].filename, trozos[1], PATH_MAX);
        strncpy(open_files[open_file_count].mode, trozos[2], 3);
        open_file_count++;
        printf("Archivo '%s' abierto con descriptor %d en modo '%s'.\n", trozos[1], desc, trozos[2]);
    } else {
        printf(ANSI_COLOR_RED "Error: No se pueden abrir más archivos.\n" ANSI_COLOR_RESET);
        close(desc);
    }
}

void Cmd_close(int NumTrozos, char *trozos[]) {
    if (NumTrozos != 1 || atoi(trozos[1]) < 0) {
        printf(ANSI_COLOR_RED "Error: Proporciona un descriptor válido. Usa 'close [df]'.\n" ANSI_COLOR_RESET);
        return;
    }

    int desc = atoi(trozos[1]), i, j;
    for (i = 0; i < open_file_count; i++) {
        if (open_files[i].desc == desc) {
            if (close(desc) == -1) { perror("Error al cerrar el archivo"); return; }

            for (j = i; j < open_file_count - 1; j++) open_files[j] = open_files[j + 1];
            open_file_count--;
            printf("El archivo con descriptor %d ha sido cerrado.\n", desc);
            return;
        }
    }
    printf(ANSI_COLOR_RED "Error: Descriptor %d no encontrado.\n" ANSI_COLOR_RESET, desc);
}


void Cmd_dup(int NumTrozos, char *trozos[]) {
    if (NumTrozos == 0 || atoi(trozos[1]) < 0) {
        printf(ANSI_COLOR_RED "Error: Proporciona un descriptor válido. Usa 'dup [df]'.\n" ANSI_COLOR_RESET);
        return;
    }
    int old_desc = atoi(trozos[1]), new_desc, i;
    for (i = 0; i < open_file_count; i++) {
        if (open_files[i].desc == old_desc) {
            if ((new_desc = dup(old_desc)) == -1) {
                perror("Error al duplicar el descriptor"); return;
            }
            if (open_file_count < MAX_FILES) {
                open_files[open_file_count].desc = new_desc;
                strncpy(open_files[open_file_count].filename, open_files[i].filename, PATH_MAX);
                strncpy(open_files[open_file_count].mode, open_files[i].mode, 3);
                open_file_count++;
                printf("Descriptor %d duplicado. Nuevo descriptor: %d\n", old_desc, new_desc);
            } else {
                printf(ANSI_COLOR_RED "Error: Límite de archivos alcanzado.\n" ANSI_COLOR_RESET);
                close(new_desc);
            }
            return;
        }
    }
    printf(ANSI_COLOR_RED "Error: Descriptor %d no encontrado.\n" ANSI_COLOR_RESET, old_desc);
}


void Cmd_infosys(int NumTrozos, char *trozos[]) {
    struct utsname sys_info;

    //Llamada al sistema uname para obtener info del sistema
    if (uname(&sys_info) == -1) {
        perror(ANSI_COLOR_RED "Error al obtener la información del sistema" ANSI_COLOR_RESET);
        return;
    }
    printf(ANSI_COLOR_GREEN "Información del sistema:\n" ANSI_COLOR_RESET);
    printf("Sistema Operativo: %s\n", sys_info.sysname);
    printf("Nombre del Nodo: %s\n", sys_info.nodename);
    printf("Versión del Sistema: %s\n", sys_info.version);
    printf("Release del Sistema: %s\n", sys_info.release);
    printf("Arquitectura de la Máquina: %s\n", sys_info.machine);
}

void Cmd_help(int NumTrozos, char *trozos[]) {
    if (NumTrozos == 0) {
        printf("Lista de comandos disponibles:\n");
        printf("  authors       Muestra los autores del programa.\n");
        printf("  cd [dir]      Cambia el directorio de trabajo actual.\n");
        printf("  close [df]    Cierra un archivo abierto con el descriptor [df].\n");
        printf("  date [-d|-t]  Muestra la fecha y/o la hora actual.\n");
        printf("  dup [df]      Duplica el descriptor de archivo [df].\n");
        printf("  infosys       Muestra información del sistema.\n");
        printf("  open [file] [mode]  Abre un archivo en el modo especificado.\n");
        printf("  pid           Muestra el PID del proceso actual.\n");
        printf("  ppid          Muestra el PID del proceso padre.\n");
        printf("  help [cmd]    Muestra esta lista o ayuda sobre un comando específico.\n");
    } else if (NumTrozos == 1) {
        if (strcmp(trozos[1], "authors") == 0) {
            printf("authors: Muestra los autores del programa.\n");
            printf("Uso: authors [-l|-n]\n");
            printf("  -l  Muestra los logins (correos electrónicos).\n");
            printf("  -n  Muestra los nombres completos.\n");
        } else if (strcmp(trozos[1], "cd") == 0) {
            printf("cd: Cambia el directorio de trabajo actual.\n");
            printf("Uso: cd [directorio]\n");
            printf("  Si no se proporciona un directorio, cambia al directorio HOME.\n");
        } else if (strcmp(trozos[1], "close") == 0) {
            printf("close: Cierra un archivo abierto con el descriptor proporcionado.\n");
            printf("Uso: close [df]\n");
        } else if (strcmp(trozos[1], "date") == 0) {
            printf("date: Muestra la fecha y la hora actual.\n");
            printf("Uso: date [-d|-t]\n");
            printf("  -d  Muestra solo la fecha.\n");
            printf("  -t  Muestra solo la hora.\n");
        } else if (strcmp(trozos[1], "dup") == 0) {
            printf("dup: Duplica el descriptor de archivo proporcionado.\n");
            printf("Uso: dup [df]\n");
        } else if (strcmp(trozos[1], "infosys") == 0) {
            printf("infosys: Muestra información sobre el sistema actual.\n");
            printf("Uso: infosys\n");
        } else if (strcmp(trozos[1], "open") == 0) {
            printf("open: Abre un archivo con el modo especificado.\n");
            printf("Uso: open [archivo] [modo]\n");
            printf(
                "  Modos: cr (crear), ap (append), ex (exclusivo), ro (solo lectura), rw (lectura/escritura), wo (solo escritura), tr (truncar).\n");
        } else if (strcmp(trozos[1], "pid") == 0) {
            printf("pid: Muestra el identificador del proceso actual (PID).\n");
            printf("Uso: pid\n");
        } else if (strcmp(trozos[1], "ppid") == 0) {
            printf("ppid: Muestra el identificador del proceso padre (PPID).\n");
            printf("Uso: ppid\n");
        } else if (strcmp(trozos[1], "help") == 0) {
            printf("help: Muestra información de ayuda sobre los comandos disponibles.\n");
            printf("Uso: help [cmd]\n");
        } else {
            // Comando no reconocido
            printf(ANSI_COLOR_RED "Error: Comando '%s' no reconocido.\n" ANSI_COLOR_RESET, trozos[0]);
        }
    } else {
        // Si se pasan más de 1 argumento, mostramos un mensaje de error
        printf(ANSI_COLOR_RED "Error: Demasiados argumentos. Usa 'help [cmd]'.\n" ANSI_COLOR_RESET);
    }
}

tList historial = {-1,NULL};

void Cmd_historic(int NumTrozos, char *trozos[]) {
    if (NumTrozos == 0) {
        tPosL posaux = first(historial);
        for (int i = 1; posaux != LNULL; i++) {
            printf("%d. %s\n", i, posaux->comando);
            posaux = next(posaux, historial);
        }
    }
    if (NumTrozos == 1) {
        int ncomando = atoi(trozos[1]);
        if (ncomando <= -1) {
            tPosL posaux = last(historial);
            for (int i = historial.contador; i > historial.contador + ncomando && posaux != LNULL; i--) {
                printf("%d. %s\n", i + 1, posaux->comando);
                posaux = previous(posaux, historial);
            }
            return;
        }
        if (ncomando >= 1 && ncomando <= historial.contador + 1) {
            tPosL posaux = first(historial);
            for (int i = ncomando; i > 0; i--) {
                if (i == 1) {
                    printf("%d. %s\n", ncomando, posaux->comando);
                }
                posaux = next(posaux, historial);
            }
            return;
        }
        printf(ANSI_COLOR_RED "Error: Argumento no válido. Usa 'help [cmd]'.\n" ANSI_COLOR_RESET);
    }
    // else printf(ANSI_COLOR_RED "Error: Comando '%s' no reconocido.\n" ANSI_COLOR_RESET, trozos[0]);
    if (NumTrozos >= 2) {
        printf(ANSI_COLOR_RED "Error: Demasiados argumentos. Usa 'help [cmd]'.\n" ANSI_COLOR_RESET);
    }
}

void add_to_historic(char comando[MAXITEM]) {
    insertItem(comando,LNULL, &historial);
}

void delete_historic(tList *historial) {
    if (historial->start == NULL) return;
    while (!isEmptyList(*historial)) {
        deleteAtPosition(first(*historial), historial);
    }
}

void Cmd_exit(int NumTrozos, char *trozos[]) {
    printf("Saliendo del shell...\n");
    delete_historic(&historial);
    exit(0);
}
