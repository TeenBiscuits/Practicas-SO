# Pablo Portas López           pablo.portas
# Pablo Míguez Mouiño          pablo.miguez.moino

PROGAMITA = p3

# Usar el compilador gcc con las cflags
CC = gcc
CFLAGS = -Wall
DEBUGFLAGS = -g -O0
VALGRINDFLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes --show-reachable=yes

# Con "make" OBJ es la ejecución por defecto (lo compila y luego ejecuta)
all: $(PROGAMITA)

# Con "make run" para compilar y ejecutar
run: $(PROGAMITA)
	./$(PROGAMITA)

# Con "make test" para comprobar los comandos
test: debug
	valgrind $(VALGRINDFLAGS) ./$(PROGAMITA) < tests.txt
# Con "make flechas" para compilar y ejecutar con rlwrap
# Existe un bug en rlwrap que elimna el promt luego de escribir algo se soluciona así:
# $ sudo nano /etc/inputrc
# |		# for rlwrap
# |		set enable-bracketed-paste off
flechas: $(PROGAMITA)
	rlwrap ./$(PROGAMITA)

# Con "make leaks" se compila y se procede a comprobar leaks de memoria con valgrind
leaks: debug
	valgrind $(VALGRINDFLAGS) ./$(PROGAMITA)

# Con "make clean" borrar el archivo
clean:
	rm -f *.o

# Compilación con símbolos de debug y optimización
debug: help.c hislist.c memlist.c searchlist.c proclist.c auxiliar.c comandos.c memoria.c procesos.c main.c
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -c -o help.o help.c
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -c -o hislist.o hislist.c
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -c -o memlist.o memlist.c
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -c -o searchlist.o searchlist.c
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -c -o proclist.o proclist.c
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -c -o auxiliar.o auxiliar.c
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -c -o comandos.o comandos.c
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -c -o memoria.o memoria.c
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -c -o procesos.o procesos.c
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -o $(PROGAMITA) main.c help.o hislist.o memlist.o searchlist.o proclist.o auxiliar.o comandos.o memoria.o procesos.o color.h

# Compilación normal
help.o: help.c
	$(CC) $(CFLAGS) -c -o help.o help.c

hislist.o: hislist.c
	$(CC) $(CFLAGS) -c -o hislist.o hislist.c

memlist.o: memlist.c
	$(CC) $(CFLAGS) -c -o memlist.o memlist.c

searchlist.o: searchlist.c
	$(CC) $(CFLAGS) -c -o searchlist.o searchlist.c

proclist.o: proclist.c
	$(CC) $(CFLAGS) -c -o proclist.o proclist.c

auxiliar.o: auxiliar.c
	$(CC) $(CFLAGS) -c -o auxiliar.o auxiliar.c

comandos.o: comandos.c
	$(CC) $(CFLAGS) -c -o comandos.o comandos.c

memoria.o: memoria.c
	$(CC) $(CFLAGS) -c -o memoria.o memoria.c

procesos.o: procesos.c
	$(CC) $(CFLAGS) -c -o procesos.o procesos.c

$(PROGAMITA): main.c help.o hislist.o memlist.o searchlist.o proclist.o auxiliar.o comandos.o procesos.o memoria.o
	$(CC) $(CFLAGS) -o $@ main.c help.o hislist.o memlist.o searchlist.o proclist.o auxiliar.o comandos.o memoria.o procesos.o color.h

# Se declara que las ejecuciones no son archivos
.PHONY: all run flechas leaks debug clean

