// Pablo Portas López           pablo.portas
// Pablo Míguez Mouiño          pablo.miguez.moino

#include "help.h"

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
    printf("authors, pid, ppid, cd, date, historic, open, close, dup, infosys, help, quit, exit, bye, makefile, listfile, cwd, listdir, reclist, revlist, erase, delrec.\n");
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
    printf("allocate [-malloc|-shared|-createshared|-mmap]... Asigna un bloque de memoria\n"
    "-malloc tam: asigna un bloque malloc de tamano tam\n"
    "-createshared cl tam: asigna (creando) el bloque de memoria compartida de clave cl y tamano tam\n"
    "-shared cl: asigna el bloque de memoria compartida (ya existente) de clave cl\n"
    "-mmap fich perm: mapea el fichero fich, perm son los permisos\n");
}

void Help_deallocate() {
    printf("deallocate [-malloc|-shared|-delkey|-mmap|addr]..	Desasigna un bloque de memoria\n"
    "-malloc tam: desasigna el bloque malloc de tamano tam\n"
    "-shared cl: desasigna (desmapea) el bloque de memoria compartida de clave cl\n"
    "-delkey cl: elimina del sistema (sin desmapear) la clave de memoria cl\n"
    "-mmap fich: desmapea el fichero mapeado fich\n"
    "addr: desasigna el bloque de memoria en la direccion addr\n");
}

void Help_memfill() {
    printf("memfill addr cont byte 	Llena la memoria a partir de addr con byte\n");
}

void Help_memdump(){
    printf("memdump addr cont 	Vuelca en pantallas los contenidos (cont bytes) de la posicion de memoria addr\n");
}

void Help_memory() {
    printf("memory [-blocks|-funcs|-vars|-all|-pmap] ..	Muestra muestra detalles de la memoria del proceso\n"
        "-blocks: los bloques de memoria asignados\n"
        "-funcs: las direcciones de las funciones\n"
        "-vars: las direcciones de las variables\n"
        ":-all: todo\n"
        "-pmap: muestra la salida del comando pmap(o similar)\n");
}

void Help_readfile() {
    printf("readfile fiche addr cont 	Lee cont bytes desde fich a la direccion addr\n");
}

void Help_writefile() {
    printf("writefile [-o] fiche addr cont 	Escribe cont bytes desde la direccion addr a fich (-o sobreescribe)\n");
}

void Help_read() {
    printf("read df addr cont	Transfiere cont bytes del fichero descrito por df a la dirección addr\n");
}

void Help_write() {
    printf("write df addr cont	Transfiere cont bytes desde la dirección addr al fichero descrito por df\n");
}

void Help_recurse() {
    printf("recurse [n]	Invoca a la funcion recursiva n veces\n");
}