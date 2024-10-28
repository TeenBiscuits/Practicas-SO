# Pablo Portas López           pablo.portas
# Pablo Míguez Mouiño          pablo.miguez.moino

# ELIMINAR ESTE COMENTARIO EN EL FUTURO
# He creado este archivo make, para que sirve te preguntarás.
# Yo tampoco lo sabía.
# Pues por lo visto vale para que al ejecutar simplemente "make" este archivo
# indique una serie de pasos para compilar y ejecutar un programa.
# Super util para no tener que escribir comandos super largos como
# gcc p0.c -o p0.out -Wall && ./p0.out
# que no es muy largo pero oye tampoco nos sobra el tiempo

# Usar el compilador gcc con las cflags
CC = gcc
CFLAGS = -Wall

# Con "make" OBJ es la ejecución por defecto (lo compila y luego ejecuta)
all: shell.out
	./shell.out

# Con "make flechas" para compilar y ejecutar con rlwrap
flechas: shell.out
	rlwrap ./shell.out

# Con "make compilar" solo se compila
compile: shell.out

# Con "make leaks" se compila y se procede a comprobar leaks de memoria con valgrind
leaks: main.c list.c help.c comandos.c
	$(CC) $(CFLAGS) -g -O0 -c -o list.out list.c
	$(CC) $(CFLAGS) -g -O0 -c -o help.out help.c
	$(CC) $(CFLAGS) -g -O0 -c -o comandos.out comandos.c
	$(CC) $(CFLAGS) -g -O0 -o shell.out main.c list.out help.out comandos.out color.h
	valgrind --leak-check=full --show-reachable=yes ./shell.out

# Con "make debug" se compula y se procede a debuguear con gdb
debug: main.c list.out help.out comandos.out help.out
	$(CC) $(CFLAGS) -g -o shell.out main.c list.out help.out comandos.out help.out color.h
	gdb shell.out

# Con "make clean" borrar el archivo
clean:
	rm -f *.out

# Compilación
help.out: help.c
	$(CC) $(CFLAGS) -c -o help.out help.c

list.out: list.c
	$(CC) $(CFLAGS) -c -o list.out list.c

comandos.out: comandos.c
	$(CC) $(CFLAGS) -c -o comandos.out comandos.c

shell.out: main.c help.out list.out comandos.out
	$(CC) $(CFLAGS) -o shell.out main.c help.out list.out comandos.out color.h

# Se declara que las ejecuciones no son archivos
.PHONY: all flechas compile lib comandos leaks debug clean

