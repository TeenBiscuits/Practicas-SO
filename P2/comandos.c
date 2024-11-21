// Pablo Portas López           pablo.portas
// Pablo Míguez Mouiño          pablo.miguez.moino

#include "comandos.h"
#include "help.h"
#include "list.h"

// COMANDOS BÁSICOS P0 + P1

// VARIABLES GLOBALES AUXILIARES

// Lista de archivos abiertos
OpenFile open_files[MAX_FILES];
int open_file_count = 0; //Esto es el contador de archivos abiertos

// Struct Comandos Help o Carolina Herrera (ChatGPT nunca pondría esto)
struct CMDHELP CH[] = {
    {"-?", Help_help},
    {"authors", Help_authors},
    {"pid", Help_pid},
    {"ppid", Help_ppid},
    {"cd", Help_cd},
    {"date", Help_date},
    {"historic", Help_historic},
    {"open", Help_open},
    {"close", Help_close},
    {"dup", Help_dup},
    {"infosys", Help_infosys},
    {"help", Help_help},
    {"quit", Help_exit},
    {"exit", Help_exit},
    {"bye", Help_exit},
    {"makefile", Help_makefile},
    {"makedir", Help_makedir},
    {"listfile", Help_listfile},
    {"cwd", Help_cwd},
    {"listdir", Help_listdir},
    {"reclist", Help_reclist},
    {"revlist", Help_revlist},
    {"erase", Help_erase},
    {"delrec", Help_delrec},
};

// Variable global del historial
tList historial = {-1,NULL};

// COMANDOS

// P0

void Cmd_authors(int NumTrozos, char *trozos[]) {
    if (NumTrozos == 0) {
        // Si solo se introduce "authors", imprime ambos nombres y correos
        printf("Pablo Portas López: pablo.portas@udc.es\n");
        printf("Pablo Míguez Muiño: pablo.miguez.muino@udc.es\n");
    } else if (NumTrozos == 1 && strcmp(trozos[1], "-l\0") == 0) {
        // Si el segundo argumento es "-l", imprime solo los correos
        printf("pablo.portas@udc.es\npablo.miguez.muino@udc.es\n");
    } else if (NumTrozos == 1 && strcmp(trozos[1], "-n\0") == 0) {
        // Si el segundo argumento es "-n", imprime solo los nombres
        printf("Pablo Portas López\nPablo Míguez Muiño\n");
    } else if (NumTrozos == 1 && strcmp(trozos[1], "-?\0") == 0) {
        printf("Usa el comando 'authors -l' para obtener solamente los logins.\n");
        printf("Usa el comando 'authors -n' para obtener solamente los nombres.\n");
        printf("Usa el comando 'authors' para obtener tanto los logins como los nombres.\n");
    } else {
        // Si el argumento no es reconocido, imprime el mensaje de error
        printf(ANSI_COLOR_RED "Error: Opción no reconocida.\n" ANSI_COLOR_RESET);
        printf("Usa el comando 'authors -l' para obtener solamente los logins.\n");
        printf("Usa el comando 'authors -n' para obtener solamente los nombres.\n");
        printf("Usa el comando 'authors' para obtener tanto los logins como los nombres.\n");
    }
}

void Cmd_pid(int NumTrozos, char *trozos[]) {
    if (strcmp(trozos[1], "-?") == 0) {
        Help_pid();
        return;
    }
    printf("El identificador del proceso es %d\n", getpid());
}

void Cmd_ppid(int NumTrozos, char *trozos[]) {
    if (strcmp(trozos[1], "-?") == 0) {
        Help_ppid();
        return;
    }
    printf("El identificador del proceso padre es %d\n", getppid());
}

void Cmd_cd(int NumTrozos, char *trozos[]) {
    // Si no se pasa argumento (NumTrozos >= 1), cambiamos al directorio HOME del usuario
    if (NumTrozos == 0) {
        char *home = getenv("HOME"); // Obtener el directorio home del usuario
        if (home == NULL || chdir(home) != 0) Imprimir_Error();
    } else if (strcmp(trozos[1], "-?\0") == 0) Help_cd();
    else if (chdir(trozos[1]) != 0) Imprimir_Error();
}

void Cmd_date(int NumTrozos, char *trozos[]) {
    time_t t;
    char buffer[80];
    time(&t); // Inicializa t con el tiempo actual

    // Obtenemos la estructura tm con el tiempo local y la hacemos const
    const struct tm *tm_info = localtime(&t);

    if (tm_info == NULL) {
        Imprimir_Error();
        return;
    }
    if (NumTrozos == 0) {
        strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M:%S", tm_info);
        printf("Fecha y hora actuales: %s\n", buffer);
    } else if (strcmp(trozos[1], "-t") == 0) {
        strftime(buffer, sizeof(buffer), "%H:%M:%S", tm_info);
        printf("Hora actual: %s\n", buffer);
    } else if (strcmp(trozos[1], "-d") == 0) {
        strftime(buffer, sizeof(buffer), "%d/%m/%Y", tm_info);
        printf("Fecha actual: %s\n", buffer);
    } else if (strcmp(trozos[1], "-?") == 0) Help_date();
}

void Cmd_open(int NumTrozos, char *trozos[]) {
    if (NumTrozos == 0) {
        list_open_files();
        return;
    }
    if (strcmp(trozos[1], "-?") == 0) {
        Help_open();
        return;
    }
    if (NumTrozos < 2) return;

    int flags = get_open_flags(trozos[2]), desc;
    if (flags == -1) {
        printf(ANSI_COLOR_RED "Error: Modo no reconocido.\n" ANSI_COLOR_RESET);
        return;
    }

    if ((desc = open(trozos[1], flags, 0644)) == -1) {
        Imprimir_Error();
        return;
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
    if (NumTrozos >= 1 && strcmp(trozos[1], "-?") == 0) {
        Help_close();
        return;
    }
    if (NumTrozos != 1 || atoi(trozos[1]) < 0) {
        printf(ANSI_COLOR_RED "Error: Proporciona un descriptor válido. Usa 'close [df]'.\n" ANSI_COLOR_RESET);
        return;
    }

    int desc = atoi(trozos[1]);

    for (int i = 0; i < open_file_count; i++) {
        if (open_files[i].desc == desc) {
            if (close(desc) == -1) {
                perror("Error al cerrar el archivo");
                return;
            }

            for (int j = i; j < open_file_count - 1; j++) open_files[j] = open_files[j + 1];
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
    if (strcmp(trozos[1], "-?") == 0) {
        Help_dup();
        return;
    }
    int old_desc = atoi(trozos[1]), new_desc;
    for (int i = 0; i < open_file_count; i++) {
        if (open_files[i].desc == old_desc) {
            if ((new_desc = dup(old_desc)) == -1) {
                Imprimir_Error();
                return;
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
    if (NumTrozos >= 1 && strcmp(trozos[1], "-?") == 0) {
        Help_infosys();
        return;
    }

    struct utsname sys_info;

    //Llamada al sistema uname para obtener info del sistema
    if (uname(&sys_info) == -1) {
        Imprimir_Error();
        return;
    }
    // Imprimimos siguiendo el formato del shell de referencia
    printf("%s (%s), OS: %s-%s-%s\n", sys_info.nodename, sys_info.machine, sys_info.sysname, sys_info.release,
           sys_info.version);
}

void Cmd_help(int NumTrozos, char *trozos[]) {
    if (NumTrozos == 0) {
        Help_default();
    }
    if (NumTrozos >= 1) {
        for (int i = 0; i < sizeof(CH) / sizeof(CH[0]); i++) {
            if (strcmp(trozos[1], CH[i].comando) == 0) {
                CH[i].funcion();
                return;
            }
        }
        printf(ANSI_COLOR_RED"Comando '%s' no encontrado.\n"ANSI_COLOR_RESET, trozos[1]);
    }
}

void Cmd_historic(int NumTrozos, char *trozos[]) {
    if (NumTrozos == 0) {
        tPosL posaux = first(historial);
        for (int i = 1; posaux != LNULL; i++) {
            printf("%d. %s\n", i, posaux->comando);
            posaux = next(posaux, historial);
        }
        return;
    }

    if (strcmp(trozos[1], "-?") == 0) {
        Help_historic();
        return;
    }

    int ncomando = atoi(trozos[1]);
    if (ncomando <= -1) {
        tPosL posaux = last(historial);
        for (int i = historial.contador; i > historial.contador + ncomando && posaux != LNULL; i--) {
            printf("%d. %s\n", i + 1, posaux->comando);
            posaux = previous(posaux, historial);
        }
    }
    if (ncomando >= 1 && ncomando <= historial.contador + 1) {
        tPosL posaux = first(historial);
        for (int i = ncomando; i > 0; i--) {
            if (i == 1) {
                printf("%d. %s\n", ncomando, posaux->comando);
            }
            posaux = next(posaux, historial);
        }
    }
}

void Cmd_exit(int NumTrozos, char *trozos[]) {
    if (NumTrozos >= 1 && strcmp(trozos[1], "-?") == 0) {
        Help_exit();
        return;
    }
    printf("Saliendo del shell...\n");
    delete_historic(&historial);
    exit(0);
}

// P1

void Cmd_makefile(int NumTrozos, char *trozos[]) {
    if (NumTrozos < 1) return;

    if (strcmp(trozos[1], "-?") == 0) {
        Help_makefile();
        return;
    }

    int fd = open(trozos[1], O_CREAT | O_EXCL | O_WRONLY, 0644);
    if (fd == -1) {
        Imprimir_Error();
    } else {
        printf("Archivo '%s' creado exitosamente.\n", trozos[1]);
        close(fd);
    }
}

void Cmd_makedir(int NumTrozos, char *trozos[]) {
    if (NumTrozos < 1) return;

    if (strcmp(trozos[1], "-?") == 0) {
        Help_makedir();
        return;
    }

    if (mkdir(trozos[1], 0755) == -1) {
        Imprimir_Error();
    } else {
        printf("Directorio '%s' creado exitosamente.\n", trozos[1]);
    }
}

void Cmd_listfile(int NumTrozos, char *trozos[]) {
    if (NumTrozos < 1) return;

    if (strcmp(trozos[1], "-?") == 0) {
        Help_listfile();
        return;
    }

    bool show_long = false, show_acc = false, show_link = false;

    for (int i = 1; i <= NumTrozos; i++) {
        if (!strcmp(trozos[i], "-long")) show_long = true;
        else if (!strcmp(trozos[i], "-acc")) show_acc = true;
        else if (!strcmp(trozos[i], "-link")) show_link = true;
    }

    for (int i = 1; i <= NumTrozos; i++) {
        if (trozos[i][0] == '-') continue;
        Aux_fileinfo(trozos[i],trozos[i],show_long,show_acc,show_link);
    }
}
void Cmd_cwd(int NumTrozos, char *trozos[]) {
    if (NumTrozos >= 1 && strcmp(trozos[1], "-?") == 0) {
        Help_cwd();
        return;
    }

    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        printf(ANSI_COLOR_RED "Error: No se pudo obtener el directorio actual: %s\n" ANSI_COLOR_RESET, strerror(errno));
    } else {
        printf("Directorio actual: %s\n", cwd);
    }
}

void Cmd_listdir(int NumTrozos, char *trozos[]) {
    if (NumTrozos >= 1 && strcmp(trozos[1], "-?") == 0) {
        Help_listdir();
        return;
    }

    bool show_long = false, show_acc = false, show_link = false, show_hid = false;

    for (int i = 1; i <= NumTrozos; i++) {
        if (!strcmp(trozos[i], "-long")) show_long = true;
        else if (!strcmp(trozos[i], "-acc")) show_acc = true;
        else if (!strcmp(trozos[i], "-link")) show_link = true;
        else if (!strcmp(trozos[i], "-hid")) show_hid = true;
    }

    for (int i = 1; i <= NumTrozos; i++) {
        if (trozos[i][0] == '-') continue;

        DIR *dir = opendir(trozos[i]);
        if (!dir) {
            Imprimir_Error();
            return;
        }

        struct dirent *entry;
        struct stat fileStat;

        while ((entry = readdir(dir)) != NULL) {
            if (entry->d_name[0] == '.' && !show_hid) continue;

            char path[PATH_MAX];
            snprintf(path, sizeof(path), "%s/%s", trozos[i], entry->d_name);
            if (stat(path, &fileStat) == -1) continue;

            Aux_fileinfo(path, entry->d_name, show_long, show_acc, show_link);
        }
        closedir(dir);
    }
}

void Cmd_reclist(int NumTrozos, char *trozos[]) {
    if (NumTrozos >= 1 && strcmp(trozos[1], "-?") == 0) {
        Help_reclist();
        return;
    }

    bool show_long = false, show_acc = false, show_link = false, show_hid = false;

    for (int i = 1; i <= NumTrozos; i++) {
        if (!strcmp(trozos[i], "-long")) show_long = true;
        else if (!strcmp(trozos[i], "-acc")) show_acc = true;
        else if (!strcmp(trozos[i], "-link")) show_link = true;
        else if (!strcmp(trozos[i], "-hid")) show_hid = true;
    }

    for (int i = 1; i <= NumTrozos; i++) {
        if (trozos[i][0] == '-') continue;
        printf(ANSI_COLOR_GREEN "%s:" ANSI_COLOR_RESET "\n", trozos[i]);
        Aux_reclist(trozos[i], show_long, show_acc, show_link, show_hid);
    }
}

void Cmd_revlist(int NumTrozos, char *trozos[]) {
    if (NumTrozos >= 1 && strcmp(trozos[1], "-?") == 0) {
        Help_revlist();
        return;
    }

    bool show_long = false, show_acc = false, show_link = false, show_hid = false;

    for (int i = 1; i <= NumTrozos; i++) {
        if (!strcmp(trozos[i], "-long")) show_long = true;
        else if (!strcmp(trozos[i], "-acc")) show_acc = true;
        else if (!strcmp(trozos[i], "-link")) show_link = true;
        else if (!strcmp(trozos[i], "-hid")) show_hid = true;
    }

    for (int i = 1; i <= NumTrozos; i++) {
        if (trozos[i][0] == '-') continue;
        Aux_revlist(trozos[i], show_long, show_acc, show_link, show_hid,trozos[i]);
    }
}
void Cmd_erase(int NumTrozos, char *trozos[]) {
    if (NumTrozos < 2) return;
    if (!strcmp(trozos[1], "-?")) { Help_erase(); return; }

    for (int i = 1; i <= NumTrozos; i++) {
        struct stat info;
        if (stat(trozos[i], &info) == -1) {
            printf("Error al obtener info de '%s': %s\n", trozos[i], strerror(errno));
            continue;
        }
        if (S_ISREG(info.st_mode) && unlink(trozos[i]) == 0)
            printf("Archivo '%s' borrado.\n", trozos[i]);
        else if (S_ISDIR(info.st_mode) && rmdir(trozos[i]) == 0)
            printf("Directorio '%s' borrado.\n", trozos[i]);
        else
            printf("Error al borrar '%s': %s\n", trozos[i], strerror(errno));
    }
}

void Cmd_delrec(int NumTrozos, char *trozos[]) {
    if (NumTrozos < 1) return;

    if (strcmp(trozos[1], "-?") == 0) {
        Help_erase();
        return;
    }

    for (int i = 1; i <= NumTrozos; i++) {
        struct stat path_stat;
        if (stat(trozos[i], &path_stat) != 0) {
            perror("stat");
            continue;
        }

        if (S_ISREG(path_stat.st_mode)) {
            // Eliminar archivo
            if (unlink(trozos[i]) == 0) printf("Archivo '%s' eliminado.\n", trozos[i]);
            else perror("unlink");
        } else if (S_ISDIR(path_stat.st_mode)) {
            // Eliminar directorio
            DIR *dir = opendir(trozos[i]);
            if (!dir) {
                perror("opendir");
                continue;
            }

            struct dirent *entry;
            while ((entry = readdir(dir)) != NULL) {
                if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;

                // Mover la declaración de subpath dentro del ciclo
                char subpath[PATH_MAX];
                snprintf(subpath, sizeof(subpath), "%s/%s", trozos[i], entry->d_name);
                Cmd_delrec(1, (char *[]){subpath}); // Recursividad
            }
            closedir(dir);
            if (rmdir(trozos[i]) == 0) printf("Directorio '%s' eliminado.\n", trozos[i]);
            else perror("rmdir");
        }
    }
}

// FUNCIONES AUXILIARES

void Imprimir_Error() {
    printf(ANSI_COLOR_RED "Error %d: %s\n" ANSI_COLOR_RESET,errno, strerror(errno));
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

bool is_hidden(const char *name) {
    return name[0] == '.';
}


void Aux_reclist(char *dir_name, bool show_long, bool show_acc, bool show_link, bool show_hid) {
    DIR *dir = opendir(dir_name);
    if (!dir) {
        Imprimir_Error();
        return;
    }

    struct dirent *entry;
    struct stat fileStat;
    char path[1024];

    // Primer pase: Archivos
    while ((entry = readdir(dir)) != NULL) {
        if (!show_hid && entry->d_name[0] == '.') continue;
        snprintf(path, sizeof(path), "%s/%s", dir_name, entry->d_name);
        stat(path, &fileStat);

        Aux_fileinfo(path,entry->d_name,show_long,show_acc,show_link);
    }

    printf("\n");
    rewinddir(dir);  // Resetear el directorio para la segunda pasada (subdirectorios)

    // Segundo pase: Subdirectorios
    while ((entry = readdir(dir)) != NULL) {
        if (!show_hid && entry->d_name[0] == '.') continue;
        snprintf(path, sizeof(path), "%s/%s", dir_name, entry->d_name);
        stat(path, &fileStat);

        if (S_ISDIR(fileStat.st_mode) && strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..")) {
            printf(ANSI_COLOR_GREEN "%s:" ANSI_COLOR_RESET "\n", path);
            Aux_reclist(path, show_long, show_acc, show_link, show_acc);
        }
    }
    closedir(dir);
}


void Aux_revlist(char *dir_name, bool show_long, bool show_acc, bool show_link, bool show_hid, char *parent_dir) {
    DIR *dir = opendir(dir_name);
    if (!dir) {
        Imprimir_Error();
        return;
    }

    struct dirent *entry;
    struct stat fileStat;
    char path[1024];

    // Primer pase: Subdirectorios
    while ((entry = readdir(dir)) != NULL) {
        if (!show_hid && entry->d_name[0] == '.') continue;
        snprintf(path, sizeof(path), "%s/%s", dir_name, entry->d_name);
        stat(path, &fileStat);

        if (S_ISDIR(fileStat.st_mode) && strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..")) {
            Aux_revlist(path, show_long, show_acc, show_link, show_acc, path);
        }
    }

    rewinddir(dir);  // Resetear el directorio para el segundo pase (archivos)

    // Segundo pase: Archivos

    printf(ANSI_COLOR_GREEN "%s:" ANSI_COLOR_RESET "\n", parent_dir);

    while ((entry = readdir(dir)) != NULL) {
        if (!show_hid && entry->d_name[0] == '.') continue;
        snprintf(path, sizeof(path), "%s/%s", dir_name, entry->d_name);
        stat(path, &fileStat);

        Aux_fileinfo(path,entry->d_name,show_long,show_acc,show_link);
    }

    printf("\n");

    closedir(dir);
}

void print_permissions(mode_t mode) {
    printf((S_ISDIR(mode)) ? "d" : "-");
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");
}

char LetraTF (mode_t m){
    switch (m&S_IFMT) { /*and bit a bit con los bits de formato,0170000 */
        case S_IFSOCK: return 's'; /*socket */
        case S_IFLNK: return 'l'; /*symbolic link*/
        case S_IFREG: return '-'; /* fichero normal*/
        case S_IFBLK: return 'b'; /*block device*/
        case S_IFDIR: return 'd'; /*directorio */
        case S_IFCHR: return 'c'; /*char device*/
        case S_IFIFO: return 'p'; /*pipe*/
        default: return '?'; /*desconocido, no deberia aparecer*/
    }
}

char * ConvierteModo (mode_t m, char *permisos){
    strcpy(permisos,"---------- ");

    permisos[0]=LetraTF(m);
    if (m&S_IRUSR) permisos[1]='r';    /*propietario*/
    if (m&S_IWUSR) permisos[2]='w';
    if (m&S_IXUSR) permisos[3]='x';
    if (m&S_IRGRP) permisos[4]='r';    /*grupo*/
    if (m&S_IWGRP) permisos[5]='w';
    if (m&S_IXGRP) permisos[6]='x';
    if (m&S_IROTH) permisos[7]='r';    /*resto*/
    if (m&S_IWOTH) permisos[8]='w';
    if (m&S_IXOTH) permisos[9]='x';
    if (m&S_ISUID) permisos[3]='s';    /*setuid, setgid y stickybit*/
    if (m&S_ISGID) permisos[6]='s';
    if (m&S_ISVTX) permisos[9]='t';

    return permisos;
}

void Aux_fileinfo(char *path, char *name, bool show_long, bool show_acc, bool show_link) {
    struct stat fileStat;
    if (lstat(path, &fileStat) == -1) {
        Imprimir_Error();
        return;
    }

    char timebuf[20];
    // Si también se pasó el parametro -acc se sustituirá la fecha de creación por modificación
    strftime(timebuf, sizeof(timebuf), "%Y/%m/%d-%H:%M", localtime(show_acc ? &fileStat.st_atime : &fileStat.st_mtime));

    char perms[12];
    ConvierteModo(fileStat.st_mode, perms);

    if(show_long) {
        printf("%s   %ld (%ld)    %s    %s %s %8ld %s\n",
            timebuf, (long)fileStat.st_nlink, fileStat.st_ino,
            getpwuid(fileStat.st_uid)->pw_name, getgrgid(fileStat.st_gid)->gr_name, perms,
            (long)fileStat.st_size, name);
    }
    else if (show_acc) {
        printf("%8ld  %s %s\n", fileStat.st_size, timebuf, name);
    }
    else if (show_link && S_ISLNK(fileStat.st_mode)) {
        char link_target[1024];
        ssize_t len = readlink(path, link_target, sizeof(link_target) - 1);
        link_target[len] = '\0';
        printf("%8ld  %s -> %s\n", fileStat.st_size, name, link_target);
    }
    else {
        printf("%8ld  %s\n", fileStat.st_size, name);
    }
}