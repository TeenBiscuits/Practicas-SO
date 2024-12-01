# Pablo Portas López           pablo.portas
# Pablo Míguez Mouiño          pablo.miguez.moino

PROGRAMITA = p3

# Usar el compilador gcc con las cflags
CC = gcc
CFLAGS = -Wall
DEBUGFLAGS = -g -O0
VALGRINDFLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes --show-reachable=yes

# Archivos fuente y objetos
SRC = help.c hislist.c memlist.c searchlist.c proclist.c auxiliar.c comandos.c memoria.c procesos.c main.c
OBJ = $(SRC:.c=.o)

# Con "make" all es la ejecución por defecto (lo compila y luego ejecuta)
all: $(PROGRAMITA)

# Existe un bug en rlwrap que elimna el promt luego de escribir algo se soluciona así:
# $ sudo nano /etc/inputrc
# |		# for rlwrap
# |		set enable-bracketed-paste off

# Con "make run" para compilar y ejecutar
run: $(PROGRAMITA)
	@if command -v rlwrap >/dev/null 2>&1; then \
		rlwrap ./$(PROGRAMITA); \
	else \
		echo "rlwrap no está instalado, ejecutando sin rlwrap..."; \
		./$(PRORGAMITA); \
	fi

# Con "make test" para comprobar los comandos
test: debug
	valgrind $(VALGRINDFLAGS) ./$(PROGRAMITA) < tests.txt

# Con "make leaks" se compila y se procede a comprobar leaks de memoria con valgrind
leaks: debug
	@if command -v rlwrap >/dev/null 2>&1; then \
		rlwrap valgrind $(VALGRINDFLAGS) ./$(PROGRAMITA); \
	else \
		echo "rlwrap no está instalado, ejecutando sin rlwrap..."; \
		valgrind $(VALGRINDFLAGS) ./$(PROGRAMITA); \
	fi

# Para la compilación debug, añadimos a las CFLAGS las DEBUGFLAGS
debug: CFLAGS += $(DEBUGFLAGS)
debug: $(PROGRAMITA)

# Compilación
$(PROGRAMITA): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) color.h

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Con "make clean" borrar los archivos intermedios y ejecutables
clean:
	rm $(OBJ) $(PROGRAMITA)

# Se declara que las ejecuciones no son archivos
.PHONY: all run test leaks debug clean
