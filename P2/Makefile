# Pablo Portas López           pablo.portas
# Pablo Míguez Mouiño          pablo.miguez.moino

# Usar el compilador gcc con las cflags
CC = gcc
CFLAGS = -Wall

# Con "make" OBJ es la ejecución por defecto (lo compila y luego ejecuta)
all: p2.o

# Con "make run" para compilar y ejecutar
run: p2.o
	./p2.o

# Con "make flechas" para compilar y ejecutar con rlwrap
flechas: p2.o
	rlwrap ./p2.o

# Con "make leaks" se compila y se procede a comprobar leaks de memoria con valgrind
leaks: main.c list.c help.c comandos.c
	$(CC) $(CFLAGS) -g -O0 -c -o list.o list.c
	$(CC) $(CFLAGS) -g -O0 -c -o help.o help.c
	$(CC) $(CFLAGS) -g -O0 -c -o comandos.o comandos.c
	$(CC) $(CFLAGS) -g -O0 -o p2.o main.c list.o help.o comandos.o color.h
	valgrind --leak-check=full --show-reachable=yes ./p2.o

# Con "make clean" borrar el archivo
clean:
	rm -f *.o

# Compilación
help.o: help.c
	$(CC) $(CFLAGS) -c -o help.o help.c

list.o: list.c
	$(CC) $(CFLAGS) -c -o list.o list.c

comandos.o: comandos.c
	$(CC) $(CFLAGS) -c -o comandos.o comandos.c

p2.o: main.c help.o list.o comandos.o
	$(CC) $(CFLAGS) -o p2.o main.c help.o list.o comandos.o color.h

# Se declara que las ejecuciones no son archivos
.PHONY: all run flechas leaks clean

