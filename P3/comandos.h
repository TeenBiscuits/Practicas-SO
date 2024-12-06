// Pablo Portas López           pablo.portas
// Pablo Míguez Mouiño          pablo.miguez.moino

#ifndef COMANDOS_H
#define COMANDOS_H

#include <stdbool.h>
#include <sys/types.h>

// COMANDOS BÁSICOS P0 + P1

#define MAX_FILES 100   // Máximos archivos posibles de abrir

// Struct para almacenar los archivos abiertos
typedef struct {
    int desc;
    char filename[PATH_MAX];
    char mode[3];
} OpenFile;

// Struct para almacenar las equivalencias entre "comando" y función
struct CMD {
    char *comando;

    void (*funcion)(int, char **, int, char **, char **);
};

// Estructura de una función de comandos
// void comando(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]);

// P0

// Imprime por pantalla los autores del proyecto. Acepta dos parámetros:
// [-l|-n] Solo logins y solo nombres respectivamente
void Cmd_authors(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]);

// Imprime por pantalla el pid del shell
void Cmd_pid(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]);

// Imprime por pantalla el ppid del shell
void Cmd_ppid(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]);

// Cambia el cwd del shell al path específicado [dir]
void Cmd_cd(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]);

// Imprime por pantalla la fecha actual. Acepta dos parámetros:
// [-t|-d] Solo hora y solo fecha respectivamente
void Cmd_date(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]);

// Lista los archivos abiertos o abre el archivo especificado
// dado un path y un modo. Los modos aceptados son:
// cr, ap, ex, ro, rw, wo, tr.
void Cmd_open(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]);

// Cierra el archivo especificado dado un file descriptor
void Cmd_close(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]);

// Duplica el file descriptor especificado
void Cmd_dup(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]);

// Imprime por pantalla la información del equipo
void Cmd_infosys(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]);

// Imprime por pantalla el historial de todos los inputs del usuario
// Acepta dos parámetros: [N|-N] Imprimir el comando N o imprimir los
// últimos N comandos
void Cmd_historic(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]);

// Termina con el shell y borra el historial
void Cmd_exit();

// P1

// Crea un archivo
void Cmd_makefile(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]);

// Crea un directorio
void Cmd_makedir(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]);

// Da la información de un archivo o un directorio
void Cmd_listfile(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]);

// Imprime el directorio de trabajo actual
void Cmd_cwd(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]);

// Imprime los contenidos de una carpeta
void Cmd_listdir(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]);

// Imprime los contenidos de un directorio de forma recursiva
// (subdirectorios después)
void Cmd_reclist(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]);

// Imprime los contenidos de un directorio de forma recursiva
// (subdirectorios antes)
void Cmd_revlist(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]);

// Elimina archivos o directorios vacios
void Cmd_erase(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]);

// Elimina archivos y/o directorios no vacíos recursivamente
void Cmd_delrec(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]);

// FUNCIONES AUXILIARES

// Devuelve el valor numérico de las diferentes "flags" de apertura
int Aux_open_get_flag(const char *mode);

// Imprime por pantalla los archivos abiertos y sus descriptores
// De no haberlos imprime un aviso
void Aux_open_lofiles();

void Aux_reclist(char *dir_name, bool show_hidden, bool show_long, bool show_acc, bool show_link);

void Aux_revlist(char *dir_name, bool show_long, bool show_acc, bool show_link, bool show_hid, char *parent_dir);

// Devuelve la letra del tipo de archivo
char Aux_comando_LetraTF(mode_t m);

// Dado un mode_t devuelve un string con formato
// Ej: -rwxrwxrwx
char *Aux_comando_mode_to_string(mode_t m, char *permisos);

// Imprime la información de un archivo dados su nombre y ruta.
// Dependiendo de los valores booleanos long, acc y link
void Aux_comando_pfinfo(char *path, char *name, bool show_long, bool show_acc, bool show_link);

void Aux_delrec(char *dir_name);

#endif
