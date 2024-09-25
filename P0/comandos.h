// Pablo Portas López
// Pablo Míguez Mouiño

#ifndef COMANDOS_H
#define COMANDOS_H

void authors(int NumTrozos, char *trozos[]);

void pid();

void ppid();

void Cmd_cd(int NumTrozos, char *trozos[]);

void Cmd_date(int NumTrozos, char *trozos[]);

void Cmd_open(int NumTrozos, char *trozos[]);

void Cmd_close(int NumTrozos, char *trozos[]);

void Cmd_dup(int NumTrozos, char *trozos[]);

void Cmd_infosys(int NumTrozos, char *trozos);

void Cmd_help(int NumTrozos, char *trozos[]);

#endif //COMANDOS_H
