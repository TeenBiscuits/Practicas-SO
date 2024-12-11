// Pablo Portas López           pablo.portas
// Pablo Míguez Mouiño          pablo.miguez.moino

#include "proclist.h"
#include "color.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/wait.h>

// Variable global del procedural
tProcList procedural = {-1,NULL};


void PList_add(pid_t pid, enum tStatusL status, char *trozos[]) {
    tCommandLine command = "";
    for (int i = 0; trozos[i] != NULL; i++) {
        strcat(command, trozos[i]);
        strcat(command, " ");
    }
    PList_aux_insertItem(pid, time(NULL), status, command,NULL, &procedural);
}

void PList_update() {
    tPosProcL aux = PList_aux_first(procedural);
    while (aux != NULL) {
        if (waitpid(aux->pid, aux->wstatus, WNOHANG|WUNTRACED) == aux->pid) {
            if (WIFEXITED(*(aux->wstatus))) aux->status = FINISHED;
            if (WIFSIGNALED(*(aux->wstatus))) aux->status = SIGNALED;
            if (WIFSTOPPED(*(aux->wstatus))) aux->status = STOPPED;
        } else aux->status = ACTIVE;
        aux = PList_aux_next(aux, procedural);
    }
}

void PList_print_all() {
    if (PList_aux_isEmptyList(procedural)) return;
    printf(ANSI_COLOR_YELLOW "*** Lista de procesos en segundo plano para la shell %d\n" ANSI_COLOR_RESET,
           getpid());
    PList_update();
    for (tPosProcL aux = PList_aux_first(procedural); aux != NULL; aux = PList_aux_next(aux, procedural)) {
        PList_aux_printNode(aux);
    }
}

void PList_delete(enum tStatusL status) {
    if (PList_aux_isEmptyList(procedural)) return;

    tPosProcL aux = PList_aux_first(procedural);
    tPosProcL aux2;
    while (aux != NULL) {
        aux2 = PList_aux_next(aux, procedural);
        if (aux->status == status) PList_aux_deleteAtPosition(aux, &procedural);
        aux = aux2;
    }
}

void PList_delete_all() {
    if (PList_aux_isEmptyList(procedural)) return;

    tPosProcL posaux;
    while (!PList_aux_isEmptyList(procedural)) {
        posaux = PList_aux_first(procedural);
        PList_aux_deleteAtPosition(posaux, &procedural);
    }
}

// AUXILIARES / INTERNAS

void PList_aux_createEmptyList(tProcList *lista) {
    lista->contador = -1;
    lista->start = PNULL;
}

bool PList_aux_isEmptyList(tProcList lista) {
    if (lista.contador == -1) return true;
    return false;
}

tPosProcL PList_aux_first(tProcList lista) {
    return lista.start;
}

tPosProcL PList_aux_last(tProcList lista) {
    tPosProcL puntero;
    for (puntero = lista.start; puntero->siguiente != PNULL; puntero = puntero->siguiente);
    return puntero;
}

tPosProcL PList_aux_next(tPosProcL posicion, tProcList lista) {
    return posicion->siguiente;
}

tPosProcL PList_aux_previous(tPosProcL posicion, tProcList lista) {
    if (posicion == lista.start) return PNULL;
    tPosProcL aux;
    for (aux = lista.start; aux->siguiente != posicion; aux = aux->siguiente);
    return aux;
}

bool PList_aux_insertItem(pid_t pid, time_t time, enum tStatusL status, tCommandLine command, tPosProcL posicion,
                          tProcList *lista) {
    if (!PList_aux_isEmptyList(*lista) && lista->contador == MAX_PLIST_SIZE) return false;

    tPosProcL aux1 = malloc(sizeof(struct tNodeProc));

    if (aux1 == NULL) return false;

    // Creación del nodo
    aux1->pid = pid;
    aux1->time = time;
    aux1->status = status;
    aux1->wstatus = malloc(sizeof(int));
    strcpy(aux1->command, command);
    aux1->siguiente = PNULL;

    if (lista->start == PNULL)
        lista->start = aux1;
    else if (posicion == PNULL) {
        tPosProcL aux2 = PList_aux_last(*lista);
        aux2->siguiente = aux1;
    } else if (posicion == PList_aux_first(*lista)) {
        aux1->siguiente = posicion;
        lista->start = aux1;
    } else {
        tPosProcL aux2 = PList_aux_previous(posicion, *lista);
        aux2->siguiente = aux1;
        aux1->siguiente = posicion;
    }

    lista->contador += 1;
    return true;
}

void PList_aux_deleteAtPosition(tPosProcL posicion, tProcList *lista) {
    tPosProcL aux, anterior;

    if (PList_aux_next(posicion, *lista) == PNULL) {
        if (posicion == lista->start) {
            lista->start = PNULL;
        } else {
            aux = PList_aux_previous(posicion, *lista);
            aux->siguiente = PNULL;
        }
    } else {
        if (posicion == lista->start) {
            lista->start = PList_aux_next(posicion, *lista);
        } else {
            anterior = PList_aux_previous(posicion, *lista);
            anterior->siguiente = PList_aux_next(posicion, *lista);
        }
    }
    lista->contador -= 1;
    free(posicion->wstatus);
    free(posicion);
}

// Este tremendo struct será muy util para traducir señales
static struct SEN sigstrnum[] = {
    {"HUP", SIGHUP},
    {"INT", SIGINT},
    {"QUIT", SIGQUIT},
    {"ILL", SIGILL},
    {"TRAP", SIGTRAP},
    {"ABRT", SIGABRT},
    {"IOT", SIGIOT},
    {"BUS", SIGBUS},
    {"FPE", SIGFPE},
    {"KILL", SIGKILL},
    {"USR1", SIGUSR1},
    {"SEGV", SIGSEGV},
    {"USR2", SIGUSR2},
    {"PIPE", SIGPIPE},
    {"ALRM", SIGALRM},
    {"TERM", SIGTERM},
    {"CHLD", SIGCHLD},
    {"CONT", SIGCONT},
    {"STOP", SIGSTOP},
    {"TSTP", SIGTSTP},
    {"TTIN", SIGTTIN},
    {"TTOU", SIGTTOU},
    {"URG", SIGURG},
    {"XCPU", SIGXCPU},
    {"XFSZ", SIGXFSZ},
    {"VTALRM", SIGVTALRM},
    {"PROF", SIGPROF},
    {"WINCH", SIGWINCH},
    {"IO", SIGIO},
    {"SYS", SIGSYS},
    /*senales que no hay en todas partes*/
#ifdef SIGPOLL
    {"POLL", SIGPOLL},
#endif
#ifdef SIGPWR
    {"PWR", SIGPWR},
#endif
#ifdef SIGEMT
    {"EMT", SIGEMT},
#endif
#ifdef SIGINFO
    {"INFO", SIGINFO},
#endif
#ifdef SIGSTKFLT
    {"STKFLT", SIGSTKFLT},
#endif
#ifdef SIGCLD
    {"CLD", SIGCLD},
#endif
#ifdef SIGLOST
    {"LOST", SIGLOST},
#endif
#ifdef SIGCANCEL
    {"CANCEL", SIGCANCEL},
#endif
#ifdef SIGTHAW
    {"THAW", SIGTHAW},
#endif
#ifdef SIGFREEZE
    {"FREEZE", SIGFREEZE},
#endif
#ifdef SIGLWP
    {"LWP", SIGLWP},
#endif
#ifdef SIGWAITING
    {"WAITING", SIGWAITING},
#endif
    {NULL, -1},
}; /*fin array sigstrnum */

char *String_of_Signal(int sen) /*devuelve el nombre senal a partir de la senal*/
{
    /* para sitios donde no hay sig2str*/
    int i;
    for (i = 0; sigstrnum[i].nombre != NULL; i++)
        if (sen == sigstrnum[i].senal)
            return sigstrnum[i].nombre;
    return ("SIGUNKNOWN");
}

char *String_of_Staus(enum tStatusL status) {
    switch (status) {
        case FINISHED:
            return "TERMINADO";
        case STOPPED:
            return "PARADO";
        case SIGNALED:
            return "SEÑALADO";
        case ACTIVE:
            return "ACTIVO";
        default:
            return "DESCONOCIDO";
    }
}

void PList_aux_printNode(tPosProcL posicion) {
    char datebuffer[80];
    struct tm *tm_info = localtime(&posicion->time);
    int prio = getpriority(PRIO_PROCESS, posicion->pid);
    strftime(datebuffer, sizeof(datebuffer), "%y/%m/%d %H:%M:%S", tm_info);
    if (posicion->status == FINISHED) {
        printf("%d\tusuario p=%d %s %s (%03d) %s\n",
               posicion->pid, prio, datebuffer, String_of_Staus(posicion->status), WEXITSTATUS(*(posicion->wstatus)),
               posicion->command);
    }
    if (posicion->status == SIGNALED) {
        printf("%d\tusuario p=%d %s %s (%s) %s\n",
               posicion->pid, prio, datebuffer, String_of_Staus(posicion->status),
               String_of_Signal(WTERMSIG(*(posicion->wstatus))),
               posicion->command);
    }
    if (posicion->status == STOPPED) {
        printf("%d\tusuario p=%d %s %s (%03d) %s\n",
               posicion->pid, prio, datebuffer, String_of_Staus(posicion->status), WSTOPSIG(*(posicion->wstatus)),
               posicion->command);
    }
    if (posicion->status == ACTIVE) {
        printf("%d\tusuario p=%d %s %s (000) %s\n",
               posicion->pid, prio, datebuffer, String_of_Staus(posicion->status), posicion->command);
    }
}
