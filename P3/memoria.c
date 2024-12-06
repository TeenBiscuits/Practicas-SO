// Pablo Portas López           pablo.portas
// Pablo Míguez Mouiño          pablo.miguez.moino

#include "memoria.h"
#include "memlist.h"
#include "help.h"
#include "auxiliar.h"
#include "color.h"

#include <string.h>
#include <sys/mman.h>
#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>


// COMANDOS DE MEMORIA P2

void Cmd_allocate(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]) {
    if (NumTrozos >= 1 && strcmp(trozos[1], "-?") == 0) {
        Help_allocate();
        return;
    }

    if (NumTrozos == 0) {
        MList_print(-1);
        return;
    }

    if (strcmp(trozos[1], "-malloc") == 0) Aux_allocate_malloc(NumTrozos, trozos);
    if (strcmp(trozos[1], "-mmap") == 0) Aux_allocate_mmap(NumTrozos, trozos);
    if (strcmp(trozos[1], "-createshared") == 0) Aux_allocate_createshared(NumTrozos, trozos);
    if (strcmp(trozos[1], "-shared") == 0) Aux_allocate_shared(NumTrozos, trozos);
}

void Cmd_deallocate(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]) {
    if (NumTrozos >= 1 && strcmp(trozos[1], "-?") == 0) {
        Help_deallocate();
        return;
    }

    if (NumTrozos == 0) {
        MList_print(-1);
        return;
    }

    if (!strcmp(trozos[1], "-malloc")) {
        if (NumTrozos >= 2) Aux_deallocate_malloc(NumTrozos, trozos);
        else MList_print(MALLOC);
    } else if (!strcmp(trozos[1], "-mmap")) {
        if (NumTrozos >= 2) Aux_deallocate_mmap(NumTrozos, trozos);
        else MList_print(MAPPED);
    } else if (!strcmp(trozos[1], "-shared")) {
        if (NumTrozos >= 2) Aux_deallocate_shared(NumTrozos, trozos);
        else MList_print(SHARED);
    } else if (!strcmp(trozos[1], "-delkey")) {
        if (NumTrozos >= 2) Aux_deallocate_delkey(NumTrozos, trozos);
        else MList_print(SHARED);
    } else {
        tAddressL address = (void *) strtol(trozos[1], NULL, 16);
        MList_remove_addr(address);
    }
}

void Cmd_memfill(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]) {
    if (NumTrozos < 3) {
        Help_memfill();
        return;
    }
    void *address = (void *) strtol(trozos[1], NULL, 16);
    Aux_memfill_LlenarMemoria(address, atoi(trozos[3]), trozos[2][0]);
}

void Cmd_memdump(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]) {
    if (NumTrozos < 2) {
        Help_memdump();
        return;
    }

    unsigned char *address = (unsigned char *) strtol(trozos[1], NULL, 16);
    int i = 0, j = 0;
    while (i <= atoi(trozos[2])) {
        for (int k = 0; k < 16 && i <= atoi(trozos[2]); i++, k++) {
            unsigned char c = address[i];
            switch (c) {
                // Este precioso switch me los escribió ChatGPT porque para
                // una tarea tan mecánica, pues la IA util un rato es.
                case '\n': printf(" \\n");
                    break; // Escapar salto de línea
                case '\t': printf(" \\t");
                    break; // Escapar tabulación
                case '\r': printf(" \\r");
                    break; // Escapar retorno de carro
                case '\\': printf(" \\\\");
                    break; // Escapar barra invertida
                case '\'': printf(" \\\'");
                    break; // Escapar comilla simple
                case '\"': printf(" \\\"");
                    break; // Escapar comilla doble
                case 0: printf("   ");
                    break; // Espacios en blanco
                default:
                    if (c >= 32 && c <= 126) printf("%3c", c);
                    else printf("  .");
            }
        }
        printf("\n");
        for (int k = 0; k < 16 && j <= atoi(trozos[2]); j++, k++) printf(" %02x", address[j]);
        printf("\n");
    }
}

void Cmd_memory(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]) {
    if (NumTrozos < 1 || !strcmp(trozos[1], "-all")) {
        Aux_memory_vars();
        Aux_memory_funcs();
        MList_print(-1);
        return;
    }
    if (!strcmp(trozos[1], "-?")) Help_memory();
    if (!strcmp(trozos[1], "-blocks")) MList_print(-1);
    if (!strcmp(trozos[1], "-funcs")) Aux_memory_funcs();
    if (!strcmp(trozos[1], "-vars")) Aux_memory_vars();
    if (!strcmp(trozos[1], "-pmap")) Aux_memory_dopmap();
}

void Cmd_readfile(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]) {
    if (NumTrozos >= 1 && !strcmp(trozos[1], "-?")) {
        Help_readfile();
        return;
    }

    void *p;
    size_t cont = -1; /*si no pasamos tamano se lee entero */
    ssize_t n;
    if (trozos[1] == NULL || trozos[2] == NULL) {
        Aux_general_Imprimir_Error("faltan parámetros");
        return;
    }
    p = (void *) strtol(trozos[2], NULL, 16); /*convertimos de cadena a puntero*/
    if (trozos[3] != NULL)
        cont = (size_t) atoll(trozos[3]);

    if ((n = Aux_readfile_LeerFichero(trozos[1], p, cont)) == -1)
        Aux_general_Imprimir_Error("Imposible leer fichero");
    else
        printf(ANSI_COLOR_GREEN "leidos %lld bytes de %s en %p\n" ANSI_COLOR_RESET, (long long) n, trozos[1], p);
}

void Cmd_writefile(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]) {
    if (NumTrozos >= 1 && !strcmp(trozos[1], "-?")) {
        Help_writefile();
        return;
    }
    void *p; //puntero que almacena una dirección de memoria pasada por el usuario
    size_t cont; //número de bytes que se escribirán desde la memoria
    ssize_t n; //resiltado de la función auxiliar escribir fichero

    if (trozos[0] == NULL || trozos[1] == NULL || trozos[2] == NULL) {
        Aux_general_Imprimir_Error("Faltan parámetros");
        return;
    }
    p = (void *) strtol(trozos[2], NULL, 16);
    cont = (size_t) atoll(trozos[3]); //convierte los bytes a un valor de tipo size_t

    if ((n = Aux_readfile_LeerFichero(trozos[1], p, cont)) == -1) {
        Aux_general_Imprimir_Error("Imposible escribir en el fichero");
    } else {
        printf(ANSI_COLOR_GREEN "Escritos %lld bytes desde %p en %s\n" ANSI_COLOR_RESET, (long long) n, p, trozos[1]);
    }
}

void Cmd_read(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]) {
}

void Cmd_write(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]) {
}

void Cmd_recurse(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]) {
    if (NumTrozos >= 1) {
        if (!strcmp(trozos[1], "-?")) {
            Help_recurse();
            return;
        }
        Aux_recurse_Recursiva(atoi(trozos[1]));
    }
}

// Auxiliares

void Aux_allocate_malloc(int NumTrozos, char *trozos[]) {
    void *paux;
    if (NumTrozos >= 2) {
        if (atoi(trozos[2]) == 0)
            Aux_general_Imprimir_Error("No se asignan bloques de 0 bytes");
        else if ((paux = MList_add_malloc(atoi(trozos[2]))) == NULL) Aux_general_Imprimir_Error("");
        else printf(ANSI_COLOR_GREEN "Asignados %d bytes en %p" ANSI_COLOR_RESET "\n", atoi(trozos[2]), paux);
    } else MList_print(MALLOC);
}

void Aux_deallocate_malloc(int NumTrozos, char *trozos[]) {
    MList_remove_malloc(atoi(trozos[2]));
}

void Aux_allocate_mmap(int NumTrozos, char *trozos[]) {
    void *paux;
    char *perm;
    int protection = 0;

    if (NumTrozos >= 2) {
        if ((perm = trozos[3]) != NULL && strlen(perm) < 4) {
            if (strchr(perm, 'r') != NULL) protection |= PROT_READ;
            if (strchr(perm, 'w') != NULL) protection |= PROT_WRITE;
            if (strchr(perm, 'x') != NULL) protection |= PROT_EXEC;
        }
        if ((paux = MList_add_mmap(trozos[2], protection)) == NULL) Aux_general_Imprimir_Error("");
        else printf(ANSI_COLOR_GREEN "Fichero %s mapeado en %p" ANSI_COLOR_RESET "\n", trozos[2], paux);
    } else MList_print(MAPPED);
}

void Aux_deallocate_mmap(int NumTrozos, char *trozos[]) {
    MList_remove_mmap(trozos[2]);
}

void Aux_allocate_createshared(int NumTrozos, char *trozos[]) {
    key_t cl;
    size_t tam;
    void *p;

    if (trozos[2] == NULL || trozos[3] == NULL) {
        MList_print(SHARED);
        return;
    }

    cl = (key_t) strtoul(trozos[2],NULL, 10);
    tam = (size_t) strtoul(trozos[3],NULL, 10);
    if (tam == 0) {
        Aux_general_Imprimir_Error("No se asignan bloques de 0 bytes");
        return;
    }
    if ((p = MList_add_shared(cl, tam)) != NULL)
        printf(ANSI_COLOR_GREEN "Asignados %lu bytes en %p\n" ANSI_COLOR_RESET, (unsigned long) tam, p);
    else
        fprintf(stderr,ANSI_COLOR_RED "Imposible asignar memoria compartida clave %lu: %s\n" ANSI_COLOR_RESET,
                (unsigned long) cl, strerror(errno));
}

void Aux_deallocate_delkey(int NumTrozos, char *trozos[]) {
    key_t clave;
    int id;
    char *key = trozos[2];

    if (key == NULL || (clave = (key_t) strtoul(key,NULL, 10)) == IPC_PRIVATE) {
        Aux_general_Imprimir_Error("delkey necesita clave válida");
        return;
    }
    if ((id = shmget(clave, 0, 0666)) == -1) {
        Aux_general_Imprimir_Error("shmget: imposible obtener memoria compartida");
        return;
    }
    if (shmctl(id,IPC_RMID,NULL) == -1)
        Aux_general_Imprimir_Error("shmctl: imposible eliminar memoria compartida");
}

void Aux_allocate_shared(int NumTrozos, char *trozos[]) {
    key_t cl;
    void *p;

    if (trozos[2] == NULL) {
        MList_print(SHARED);
        return;
    }

    cl = (key_t) strtoul(trozos[2],NULL, 10);

    if ((p = MList_add_shared(cl, 0)) != NULL)
        printf(ANSI_COLOR_GREEN "Asignada memoria compartida de clave %lu en %p\n" ANSI_COLOR_RESET,
               (unsigned long) cl, p);
    else
        fprintf(stderr,ANSI_COLOR_RED "Imposible asignar memoria compartida clave %lu: %s\n" ANSI_COLOR_RESET,
                (unsigned long) cl, strerror(errno));
}

void Aux_deallocate_shared(int NumTrozos, char *trozos[]) {
    key_t cl = (key_t) strtoul(trozos[2],NULL, 10);
    MList_remove_shared(cl);
}

void Aux_recurse_Recursiva(int n) {
    char automatico[TAMANO];
    static char estatico[TAMANO];

    printf("parametro:%3d(%p) array %p, arr estatico %p\n", n, &n, automatico, estatico);

    if (n > 0)
        Aux_recurse_Recursiva(n - 1);
}

void Aux_memfill_LlenarMemoria(void *p, size_t cont, unsigned char ch) {
    unsigned char *arr = (unsigned char *) p;
    size_t i;

    printf("Llenando %ld bytes de memoria con el byte %c(%x) a partir de la dirección %p\n", cont, ch, ch, p);
    for (i = 0; i < cont; i++)
        arr[i] = ch;
}

void Aux_memory_dopmap(void) {
    pid_t pid; /*hace el pmap (o equivalente) del proceso actual*/
    char elpid[32];
    char *argv[4] = {"pmap", elpid,NULL};

    sprintf(elpid, "%d", (int) getpid());
    if ((pid = fork()) == -1) {
        Aux_general_Imprimir_Error("Imposible crear proceso");
        return;
    }
    if (pid == 0) {
        if (execvp(argv[0], argv) == -1)
            Aux_general_Imprimir_Error("cannot execute pmap (linux, solaris)");

        argv[0] = "procstat";
        argv[1] = "vm";
        argv[2] = elpid;
        argv[3] = NULL;
        if (execvp(argv[0], argv) == -1) /*No hay pmap, probamos procstat FreeBSD */
            Aux_general_Imprimir_Error("cannot execute procstat (FreeBSD)");

        argv[0] = "procmap", argv[1] = elpid;
        argv[2] = NULL;
        if (execvp(argv[0], argv) == -1) /*probamos procmap OpenBSD*/
            Aux_general_Imprimir_Error("cannot execute procmap (OpenBSD)");

        argv[0] = "vmmap";
        argv[1] = "-interleave";
        argv[2] = elpid;
        argv[3] = NULL;
        if (execvp(argv[0], argv) == -1) /*probamos vmmap Mac-OS*/
            Aux_general_Imprimir_Error("cannot execute vmmap (Mac-OS)");
        exit(1);
    }
    waitpid(pid,NULL, 0);
}

void Aux_memory_funcs() {
    printf("Funciones programa\t\t%p,\t%p,\t%p\n", Aux_general_Imprimir_Error, MList_print, Cmd_allocate);
    printf("Funciones libreria\t\t%p,\t%p,\t%p\n", printf, getpid, wait);
}


int externia = 1, externia2 = 2, externia3 = 3;
int externa, externb, externc;

void Aux_memory_vars() {
    extern int externia, externia2, externia3;
    extern int externa, externb, externc;
    static int statica = 1, staticb = 2, staticc = 3;
    static int staticia, staticib, staticicc;
    auto int autoa = 1, autob = 2, autoc = 3;
    printf("Variables externas\t\t%p,\t%p,\t%p\n", &externia, &externia2, &externia3);
    printf("Variables (N.I.) externas\t%p,\t%p,\t%p\n", &externa, &externb, &externc);
    printf("Variables estáticas\t\t%p,\t%p,\t%p\n", &staticia, &staticib, &staticicc);
    printf("Variables (N.I.) estáticas\t%p,\t%p,\t%p\n", &statica, &staticb, &staticc);
    printf("Variables automáticas\t\t%p,\t%p,\t%p\n", &autoa, &autob, &autoc);
}

ssize_t Aux_readfile_LeerFichero(char *f, void *p, size_t cont) {
    struct stat s;
    ssize_t n;
    int df, aux;

    if (stat(f, &s) == -1 || (df = open(f, O_RDONLY)) == -1)
        return -1;
    if (cont == -1) /* si pasamos -1 como bytes a leer lo leemos entero*/
        cont = s.st_size;
    if ((n = read(df, p, cont)) == -1) {
        aux = errno;
        close(df);
        errno = aux;
        return -1;
    }
    close(df);
    return n;
}

ssize_t Aux_writefile_EscribirFichero(char *f, void *p, ssize_t cont) {
    ssize_t n;
    int df, aux;

    if ((df = open(f, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1) {
        return -1;
    }
    if ((n = write(df, p, cont)) == -1) {
        aux = errno;
        close(df);
        errno = aux;
        return -1;
    }
    close(df);
    return n;
}
