// Pablo Portas López           pablo.portas
// Pablo Míguez Mouiño          pablo.miguez.moino

#ifndef PROCESOS_H
#define PROCESOS_H


// COMANDOS DE PROCESOS P3

void Cmd_getuid(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]);

void Cmd_setuid(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]);

void Cmd_showvar(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]);

void Cmd_changevar(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]);

void Cmd_subsvar(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]);

void Cmd_environ(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]);

void Cmd_fork(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]);

void Cmd_search(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]);

void Cmd_exec(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]);

void Cmd_execpri(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]);

void Cmd_fg(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]);

void Cmd_fgpri(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]);

void Cmd_back(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]);

void Cmd_backpri(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]);

void Cmd_listjobs(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]);

void Cmd_deljobs(int NumTrozos, char *trozos[], int argc, char *argv[], char *env[]);


// Auxiliares

char *Aux_procesos_Ejecutable(char *s);

int Aux_procesos_Execpve(char *tr[], char **NewEnv, int *pprio);

void Aux_environ_show(char **env, char * nombre_entorno);

#endif //PROCESOS_H
