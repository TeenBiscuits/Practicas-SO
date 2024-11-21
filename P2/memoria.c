#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Función para convertir una dirección de memoria en formato string a void*
void *convertir_direccion(const char *direccion_str) {
    void *direccion = (void *)strtoull(direccion_str, NULL, 16);
    if (direccion == NULL) {
        printf("Error: dirección de memoria inválida.\n");
    }
    return direccion;
}

// Función principal del comando memfill
void Cmd_memfill(int NumTrozos, char *trozos[]) {
    if (NumTrozos < 4) {
        printf("Número de trozos incorrecto. Uso: memfill <addr> <ch> <cont>\n");
        return;
    }

    void *direccion = convertir_direccion(trozos[1]);
    if (direccion == NULL) return;

    unsigned char caracter = (unsigned char)trozos[2][0];

    size_t cantidad = strtoull(trozos[3], NULL, 10);
    if (cantidad == 0) {
        printf("Error: cantidad de bytes a llenar inválida.\n");
        return;
    }

    //Aquí rellenamos memoria
    memset(direccion, caracter, cantidad);

    printf("llenando %zu bytes de memoria con el byte %c(%02X) a partir de la dirección %p\n",
           cantidad, caracter, caracter, direccion);
}
