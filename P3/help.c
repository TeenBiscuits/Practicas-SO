// Pablo Portas López           pablo.portas
// Pablo Míguez Mouiño          pablo.miguez.moino

#include <stdio.h>
#include <string.h>

#include "help.h"
#include "color.h"

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
    {"allocate", Help_allocate},
    {"deallocate", Help_deallocate},
    {"memfill", Help_memfill},
    {"memdump", Help_memdump},
    {"memory", Help_memory},
    {"readfile", Help_readfile},
    {"writefile", Help_writefile},
    {"read", Help_read},
    {"write", Help_write},
    {"recurse", Help_recurse},
    {"getuid", Help_getuid},
    {"setuid", Help_setuid},
    {"showvar", Help_showvar},
    {"changevar", Help_changevar},
    {"subsvar", Help_subsvar},
    {"environ", Help_environ},
    {"fork", Help_fork},
    {"search", Help_search},
    {"exec", Help_exec},
    {"execpri", Help_execpri},
    {"fg", Help_fg},
    {"fgpri", Help_fgpri},
    {"back", Help_back},
    {"backpri", Help_backpri},
    {"listjobs", Help_listjobs},
    {"deljobs", Help_deljobs}
};

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
        fprintf(stderr, ANSI_COLOR_RED"Comando '%s' no encontrado.\n"ANSI_COLOR_RESET, trozos[1]);
    }
}

void Help_authors() {
    printf("authors [-n|-l]\tMuestra los nombres y/o logins de los autores\n");
    printf("\t-l: solamente los logins.\n\t-n: solamente los nombres.\n");
}

void Help_pid() {
    printf("pid [-p]\tMuestra el pid del shell o de su proceso padre\n");
}

void Help_ppid() {
    printf("ppid\tMuestra el pid del proceso padre del shell\n");
}

void Help_cd() {
    printf("cd [dir]\tCambia (o muestra) el directorio actual del shell\n");
}

void Help_date() {
    printf("date [-d|-t]\tMuestra la fecha y/o la hora actual\n");
}

void Help_open() {
    printf("open fich m1 m2...\tAbre el fichero fich\n");
    printf("\ty lo anade a la lista de ficheros abiertos del shell\n");
    printf("\tm1, m2..es el modo de apertura (or bit a bit de los siguientes)\n");
    printf("\tcr: O_CREAT\tap: O_APPEND\n\tex: O_EXCL\tro: O_RDONLY\n");
    printf("\trw: O_RDWR\two: O_WRONLY\n\ttr: O_TRUNC\n");
}

void Help_close() {
    printf("close df\tCierra el descriptor df y elimina el correspondiente fichero de la lista de ficheros abiertos\n");
}

void Help_dup() {
    printf("dup df\tDuplica el descriptor de fichero df y anade una nueva entrada a la lista ficheros abiertos\n");
}

void Help_infosys() {
    printf("infosys\tMuestra informacion de la maquina donde corre el shell\n");
}

void Help_help() {
    printf("help [cmd|-lt|-T|-all]\tMuestra ayuda sobre los comandos\n");
    printf("\t-lt: lista topics de ayuda\n\t-T topic: lista comandos sobre ese topic\n"
        "\tcmd: info sobre el comando cmd\n\t-all: lista todos los topics con sus comandos\n");
}

void Help_default() {
    printf("help [cmd|-lt|-T|-all]\tMuestra ayuda sobre los comandos\n");
    printf("Comandos disponibles:\n");
    for (int i = 1; i < sizeof(CH) / sizeof(CH[0]); i++) {
        printf("%s", CH[i].comando);
        if (i < (sizeof(CH) / sizeof(CH[0]) - 1)) printf(", ");
    }
    printf(".\n");
}

void Help_historic() {
    printf("historic [-c|-N|N]\tMuestra (o borra)el historico de comandos\n");
    printf("\t-N: muestra los N primeros\n\t-c: borra el historico\n\tN: repite el comando N\n");
}

void Help_exit() {
    printf("exit\tTermina la ejecucion del shell\n");
}

void Help_makedir() {
    printf("makedir [name]\tCrea un directorio de nombre name\n");
}

void Help_makefile() {
    printf("makefile [name]\tCrea un fichero de nombre name\n");
}

void Help_listfile() {
    printf("listfile [-long][-link][-acc] name1 name2 ... lista ficheros;\n");
    printf("\t-long: listado largo\n\t-acc: acesstime\n\t-link: si es enlace simbolico, el path contenido\n");
}

void Help_cwd() {
    printf("cwd\tMuestra el directorio actual del shell\n");
}

void Help_listdir() {
    printf("listdir [-hid][-long][-link][-acc] n1 n2 ... lista contenidos de directorios\n");
    printf("\t-long: listado largo\n\t-hid: incluye los ficheros ocultos\n\t-acc: acesstime\n"
        "\t-link: si es enlace simbolico, el path contenido\n");
}

void Help_reclist() {
    printf("reclist [-hid][-long][-link][-acc] n1 n2 ... "
        "lista recursivamente contenidos de directorios (subdirs despues)\n");
    printf("\t-hid: incluye los ficheros ocultos\n\t-long: listado largo\n"
        "\t-acc: acesstime\n\t-link: si es enlace simbolico, el path contenido\n");
}

void Help_revlist() {
    printf("revlist [-hid][-long][-link][-acc] n1 n2 ... "
        "lista recursivamente contenidos de directorios (subdirs antes)\n");
    printf("\t-hid: incluye los ficheros ocultos\n\t-long: listado largo\n"
        "\t-acc: acesstime\n\t-link: si es enlace simbolico, el path contenido\n");
}

void Help_erase() {
    printf("erase [name1 name2 ..]\tBorra ficheros o directorios vacios\n");
}

void Help_delrec() {
    printf("delrec [name1 name2 ..]\tBorra ficheros o directorios no vacios recursivamente\n");
}

void Help_allocate() {
    printf("allocate [-malloc|-shared|-createshared|-mmap]... \tAsigna un bloque de memoria\n"
        "\t-malloc tam: asigna un bloque malloc de tamano tam\n"
        "\t-createshared cl tam: asigna (creando) el bloque de memoria compartida de clave cl y tamano tam\n"
        "\t-shared cl: asigna el bloque de memoria compartida (ya existente) de clave cl\n"
        "\t-mmap fich perm: mapea el fichero fich, perm son los permisos\n");
}

void Help_deallocate() {
    printf("deallocate [-malloc|-shared|-delkey|-mmap|addr]..	\tDesasigna un bloque de memoria\n"
        "\t-malloc tam: desasigna el bloque malloc de tamano tam\n"
        "\t-shared cl: desasigna (desmapea) el bloque de memoria compartida de clave cl\n"
        "\t-delkey cl: elimina del sistema (sin desmapear) la clave de memoria cl\n"
        "\t-mmap fich: desmapea el fichero mapeado fich\n"
        "\taddr: desasigna el bloque de memoria en la direccion addr\n");
}

void Help_memfill() {
    printf("memfill addr ch cont \tLlena la memoria con el carácter ch, empezando en la dirección addr, "
        "durante cont bytes.\n");
}

void Help_memdump() {
    printf("memdump addr cont \tVuelca en pantallas los contenidos (cont bytes) de la posicion de memoria addr\n");
}

void Help_memory() {
    printf("memory [-blocks|-funcs|-vars|-all|-pmap] .. \tMuestra muestra detalles de la memoria del proceso\n"
        "\t-blocks: los bloques de memoria asignados\n"
        "\t-funcs: las direcciones de las funciones\n"
        "\t-vars: las direcciones de las variables\n"
        "\t-all: todo\n"
        "\t-pmap: muestra la salida del comando pmap(o similar)\n");
}

void Help_readfile() {
    printf("readfile fiche addr cont \tLee cont bytes desde fich a la direccion addr\n");
}

void Help_writefile() {
    printf("writefile [-o] fiche addr cont \tEscribe cont bytes desde la direccion addr a fich (-o sobreescribe)\n");
}

void Help_read() {
    printf("read df addr cont \tTransfiere cont bytes del fichero descrito por df a la dirección addr\n");
}

void Help_write() {
    printf("write df addr cont \tTransfiere cont bytes desde la dirección addr al fichero descrito por df\n");
}

void Help_recurse() {
    printf("recurse [n] \tInvoca a la funcion recursiva n veces\n");
}

void Help_getuid() {
    printf("getuid  Muestra las credenciales del proceso que ejecuta el shell\n");
}

void Help_setuid() {
    printf("setuid [-l] id  Cambia las credenciales del proceso que ejecuta el shell\n"
        "\tid: establece la credencial al valor numerico id\n"
        "\t-l id: establece la credencial a login id\n");
}

void Help_showvar() {
    printf("showvar var\tMuestra el valor y las direcciones de la variable de entorno var\n");
}

void Help_changevar() {
    printf("changevar [-a|-e|-p] var valor  Cambia el valor de una variable de entorno\n"
        "\t-a: accede por el tercer arg de main\n"
        "\t-e: accede mediante environ\n"
        "\t-p: accede mediante putenv\n");
}

void Help_subsvar() {
    printf("subsvar [-a|-e] var1 var2 valor Sustituye la variable de entorno var1\n"
        "\tcon var2=valor\n"
        "\t-a: accede por el tercer arg de main\n"
        "\t-e: accede mediante environ\n");
}

void Help_environ() {
    printf("environ [-environ|-addr]\tMuestra el entorno del proceso\n"
        "\t-environ: accede usando environ (en lugar del tercer arg de main)\n"
        "\t-addr: muestra el valor y donde se almacenan environ y el 3er arg main\n");
}

void Help_fork() {
    printf("fork\tEl shell hace fork y queda en espera a que su hijo termine\n");
}

void Help_search() {
    printf("search [-add|-del|-clear|-path]..\tManipula o muestra la ruta de busqueda del shell (path)\n"
        "\t-add dir: aniade dir a la ruta de busqueda(equiv +dir)\n"
        "\t-del dir: elimina dir de la ruta de busqueda (equiv -dir)\n"
        "\t-clear: vacia la ruta de busqueda\n"
        "\t-path: importa el PATH en la ruta de busqueda\n");
}

void Help_exec() {
    printf("exec VAR1 VAR2 ..prog args....[@pri]\tEjecuta, sin crear proceso,prog con argumentos\n"
        "\ten un entorno que contiene solo las variables VAR1, VAR2...\n");
}

void Help_execpri() {
    printf("execpri prio prog args....\tEjecuta, sin crear proceso, prog con argumentos con la "
        "prioridad cambiada a prio\n");
}

void Help_fg() {
    printf("fg prog args... Crea un proceso que ejecuta en primer plano prog con argumentos\n");
}

void Help_fgpri() {
    printf("fgpri prio prog args... Crea un proceso que ejecuta en primer plano prog con "
        "argumentos  con la prioridad cambiada a prio\n");
}

void Help_back() {
    printf("back prog args...\tCrea un proceso que ejecuta en segundo plano prog con argumentos\n");
}

void Help_backpri() {
    printf("backpri prio prog args...\tCrea un proceso que ejecuta en segundo plano prog con "
        "argumentos con la prioridad cambiada a prio\n");
}

void Help_listjobs() {
    printf("listjobs\tLista los procesos en segundo plano\n");
}

void Help_deljobs() {
    printf("deljobs [-term][-sig]   Elimina los procesos de la lista procesos en sp\n"
        "\t-term: los terminados\n"
        "\t-sig: los terminados por senal\n");
}
