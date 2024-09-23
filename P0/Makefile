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

# Con "make" OBJ es la ejecución por defecto (lo compila y luego ejecuta)
all: $(OBJ)
	./$(OBJ)

# Con "make compilar" solo se compila
compile: $(OBJ)

# Con "make leaks" se compila y se procede a comprobar leaks de memoria con valgrind
leaks: $(SRC)
	$(CC) $(CFLAGS) -g -O0 -o $(OBJ) $(SRC)
	valgrind --leak-check=full --show-reachable=yes ./$(OBJ)

# Con "make debug" se compula y se procede a debuguear con gdb
debug: $(SRC)
	$(CC) $(CFLAGS) -g -o $(OBJ) $(SRC)
	gdb $(OBJ)

# Con "make clean" borrar el archivo
clean:
	rm -f *.out

# Compilación
$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -o $(OBJ) $(SRC)

# Se declara que clean y compile no son archivos
.PHONY: clean compilar

