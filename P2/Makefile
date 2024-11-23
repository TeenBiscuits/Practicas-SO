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

# Con "make test" para comprobar los comandos
test: debug
	valgrind --leak-check=full --show-reachable=yes ./p2.o < tests.txt
# Con "make flechas" para compilar y ejecutar con rlwrap
# Existe un bug en rlwrap que elimna el promt luego de escribir algo se soluciona así:
# $ sudo nano /etc/inputrc
# |		# for rlwrap
# |		set enable-bracketed-paste off
flechas: p2.o
	rlwrap ./p2.o

# Con "make leaks" se compila y se procede a comprobar leaks de memoria con valgrind
leaks: debug
	valgrind --leak-check=full --show-reachable=yes ./p2.o

# Con "make clean" borrar el archivo
clean:
	rm -f *.o

# Compilación con símbolos de debug y optimización
debug: main.c help.o hislist.o auxiliar.o comandos.o memoria.o
	$(CC) $(CFLAGS) -g -O0 -c -o help.o help.c
	$(CC) $(CFLAGS) -g -O0 -c -o hislist.o hislist.c
	$(CC) $(CFLAGS) -g -O0 -c -o auxiliar.o auxiliar.c
	$(CC) $(CFLAGS) -g -O0 -c -o comandos.o comandos.c
	$(CC) $(CFLAGS) -g -O0 -c -o memoria.o memoria.c
	$(CC) $(CFLAGS) -g -O0 -o p2.o main.c help.o hislist.o auxiliar.o comandos.o memoria.o color.h

# Compilación normal
help.o: help.c
	$(CC) $(CFLAGS) -c -o help.o help.c

hislist.o: hislist.c
	$(CC) $(CFLAGS) -c -o hislist.o hislist.c

auxiliar.o: auxiliar.c
	$(CC) $(CFLAGS) -c -o auxiliar.o auxiliar.c

comandos.o: comandos.c
	$(CC) $(CFLAGS) -c -o comandos.o comandos.c

memoria.o: memoria.c
	$(CC) $(CFLAGS) -c -o memoria.o memoria.c

p2.o: main.c help.o hislist.o auxiliar.o comandos.o memoria.o
	$(CC) $(CFLAGS) -o p2.o main.c help.o hislist.o auxiliar.o comandos.o memoria.o color.h

# Se declara que las ejecuciones no son archivos
.PHONY: all run flechas leaks debug clean

