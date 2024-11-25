// Pablo Portas López           pablo.portas
// Pablo Míguez Mouiño          pablo.miguez.moino

#ifndef MEMORIA_H
#define MEMORIA_H

// COMANDOS DE MEMORIA P2

void Cmd_allocate(int NumTrozos, char *trozos[]);

void Cmd_deallocate(int NumTrozos, char *trozos[]);

void Cmd_memfill(int NumTrozos, char *trozos[]);

void Cmd_memdump(int NumTrozos, char *trozos[]);

void Cmd_memory(int NumTrozos, char *trozos[]);

void Cmd_readfile(int NumTrozos, char *trozos[]);

void Cmd_writefile(int NumTrozos, char *trozos[]);

void Cmd_read(int NumTrozos, char *trozos[]);

void Cmd_write(int NumTrozos, char *trozos[]);

void Cmd_recurse(int NumTrozos, char *trozos[]);

#endif //MEMORIA_H
