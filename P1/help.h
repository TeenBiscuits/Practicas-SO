// Pablo Portas López           pablo.portas
// Pablo Míguez Mouiño          pablo.miguez.moino

#ifndef HELP_H
#define HELP_H

#include <stdio.h>

// Struct para almacenar comandos y sus funciones de ayuda correspondientes
struct CMDHELP {
    char *comando;

    void (*funcion)();
};

// Imprime por pantalla la ayuda de authors
void Help_authors();

// Imprime por pantalla la ayuda de pid
void Help_pid();

// Imprime por pantalla la ayuda de ppid
void Help_ppid();

// Imprime por pantalla la ayuda de cd
void Help_cd();

// Imprime por pantalla la ayuda de date
void Help_date();

// Imprime por pantalla la ayuda de open
void Help_open();

// Imprime por pantalla la ayuda de close
void Help_close();

// Imprime por pantalla la ayuda de dup
void Help_dup();

// Imprime por pantalla la ayuda de infosys
void Help_infosys();

// Imprime por pantalla la ayuda de help
void Help_help();

// Imprime por pantalla la ayuda básica de help y una lista de todos los comandos disponibles.
void Help_default();

// Imprime por pantalla la ayuda de historic
void Help_historic();

// Imprime por pantalla la ayuda de exit
void Help_exit();

// Imprime por pantalla la ayuda de makedir
void Help_makedir();

// Imprime por pantalla la ayuda de makefile
void Help_makefile();

// Imprime por pantalla la ayuda de listfile
void Help_listfile();

// Imprime por pantalla la ayuda de cwd
void Help_cwd();

// Imprime por pantalla la ayuda de listdir
void Help_listdir();

// Imprime por pantalla la ayuda de reclist
void Help_reclist();

// Imprime por pantalla la ayuda de revlist
void Help_revlist();

// Imprime por pantalla la ayuda de erase
void Help_erase();

// Imprime por pantalla la ayuda de delrec
void Help_delrec();

#endif //HELP_H
