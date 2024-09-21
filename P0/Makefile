# ELIMINAR ESTE COMENTARIO EN EL FUTURO
# He creado este archivo make, para que sirve te preguntarás.
# Yo tampoco lo sabía.
# Pues por lo visto vale para que al ejecutar simplemente "make" este archivo
# indique una serie de pasos para compilar y ejecutar un programa.
# Super util para no tener que escribir comandos super largos como
# gcc p0.c -o p0.out -Wall && ./p0.out
# que no es muy largo pero oye tampoco nos sobra el tiempo

# Usar el compilador gcc
CC = gcc
CFLAGS = -Wall

# Salida del makefile
TARGET = p0.out

# Compilación
$(TARGET): p0.c
	$(CC) $(CFLAGS) -o $(TARGET) p0.c

# Con "make" Target es la ejecución por defecto (lo compila y luego ejecuta)
all: $(TARGET)
	./$(TARGET)

# Con "make compilar" solo se compila
compile: $(TARGET)

# Con "make clean" borrar el archivo
clean:
	rm -f $(TARGET)

# Se declara que clean y compile no son archivos
.PHONY: clean compilar

