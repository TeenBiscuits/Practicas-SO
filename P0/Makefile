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

# Fuente y Salida del makefile
SRC = p0.c
OBJ = p0.out

# Comandos
COMA = comandos.c
COMP = comandos.out

# Librería y archivo dependencia
LIB = list.c
DEPE = list.out

# Literalmente variables colores
COLORES = color.h

# Con "make" OBJ es la ejecución por defecto (lo compila y luego ejecuta)
all: $(OBJ)
	./$(OBJ)

# Con "make flechas" para compilar y ejecutar con rlwrap
flechas: $(OBJ)
	rlwrap ./$(OBJ)

# Con "make compilar" solo se compila
compile: $(OBJ)

# Con "make lib" se compila la librería
lib: $(LIB)
	$(CC) $(CFLAGS) -c -o $(DEPE) $(LIB)

# Con "make comandos" se compilan los comandos
comandos: $(COMA)
	$(CC) $(CFLAGS) -c -o $(COMP) $(COMA)

# Con "make leaks" se compila y se procede a comprobar leaks de memoria con valgrind
leaks: $(SRC) $(LIB) $(COMA)
	$(CC) $(CFLAGS) -g -O0 -c -o $(DEPE) $(LIB)
	$(CC) $(CFLAGS) -g -O0 -c -o $(COMP) $(COMA)
	$(CC) $(CFLAGS) -g -O0 -o $(OBJ) $(SRC) $(DEPE) $(COMP) $(COLORES)
	valgrind --leak-check=full --show-reachable=yes ./$(OBJ)

# Con "make debug" se compula y se procede a debuguear con gdb
debug: $(SRC) $(DEPE) $(COMP)
	$(CC) $(CFLAGS) -g -o $(OBJ) $(SRC) $(DEPE) $(COMP) $(COLORES)
	gdb $(OBJ)

# Con "make clean" borrar el archivo
clean:
	rm -f *.out

# Compilación
$(DEPE): $(LIB)
	$(CC) $(CFLAGS) -c -o $(DEPE) $(LIB)

$(COMP): $(COMA)
	$(CC) $(CFLAGS) -c -o $(COMP) $(COMA)

$(OBJ): $(SRC) $(DEPE) $(COMP)
	$(CC) $(CFLAGS) -o $(OBJ) $(SRC) $(DEPE) $(COMP) $(COLORES)

# Se declara que las ejecuciones no son archivos
.PHONY: all flechas compile lib comandos leaks debug clean

