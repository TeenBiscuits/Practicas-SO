// Pablo Portas López           pablo.portas
// Pablo Míguez Mouiño          pablo.miguez.moino

#ifndef PROCESOS_H
#define PROCESOS_H


// COMANDOS DE PROCESOS P3

void Cmd_getuid(int NumTrozos, char *trozos[]);

void Cmd_setuid(int NumTrozos, char *trozos[]);

void Cmd_showvar(int NumTrozos, char *trozos[]);

void Cmd_changevar(int NumTrozos, char *trozos[]);

void Cmd_subsvar(int NumTrozos, char *trozos[]);

void Cmd_environ(int NumTrozos, char *trozos[]);

void Cmd_fork(int NumTrozos, char *trozos[]);

void Cmd_search(int NumTrozos, char *trozos[]);

void Cmd_exec(int NumTrozos, char *trozos[]);

void Cmd_execpri(int NumTrozos, char *trozos[]);

void Cmd_fg(int NumTrozos, char *trozos[]);

void Cmd_fgpri(int NumTrozos, char *trozos[]);

void Cmd_back(int NumTrozos, char *trozos[]);

void Cmd_backpri(int NumTrozos, char *trozos[]);

void Cmd_listjobs(int NumTrozos, char *trozos[]);

void Cmd_deljobs(int NumTrozos, char *trozos[]);


// Auxiliares


#endif //PROCESOS_H
