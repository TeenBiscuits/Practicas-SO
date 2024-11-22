//
// Created by paablomiiguez on 21/11/24.
//

#ifndef MEMORIA_H
#define MEMORIA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Cmd_memfill(int NumTrozos, char *trozos[]);

void Cmd_memdump(int NumTrozos, char *trozos[]);

void Cmd_memory(int numTrozos, char *args[]);

void Cmd_readfile(int NumTrozos, char *args[]);

void Cmd_writefile(int NumTrozos, char *args[]);

void Cmd_read(int NumTrozos, char *args[]);

void Cmd_write(int NumTrozos, char *args[]);


#endif //MEMORIA_H
