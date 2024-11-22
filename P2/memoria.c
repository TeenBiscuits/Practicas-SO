#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>



//Convierte cadena en puntero
void *direccion_inicio(const char *arg) {
    return (void *)strtoull(arg, NULL, 16);
}

size_t cantidad_bytes(const char *arg) {
    return (size_t)strtoull(arg, NULL, 10);
}

void memory_funcs() {
    // Funciones del programa
    printf("Dirección de funcion1: %p\n", (void *)&cantidad_bytes);

    // Funciones de biblioteca
    printf("Dirección de printf (biblioteca): %p\n", (void *)&printf);
    printf("Dirección de scanf (biblioteca): %p\n", (void *)&scanf);
    printf("Dirección de malloc (biblioteca): %p\n", (void *)&malloc);
}

void volcar_memoria(const uint8_t *ptr, size_t cantidad_bytes) {
    for (size_t i = 0; i < cantidad_bytes; i++) {
        printf("%02x ", *(ptr + i));
        if ((i + 1) % 16 == 0) {
            printf("\n");
        }
    }
    if (cantidad_bytes % 16 != 0) {
        printf("\n");
    }
}

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

// Vuelca el contenido de una cantidad específica de bytes de memoria (cont) comenzando desde una dirección determinada (addr) en la pantalla.
void Cmd_memdump(int NumTrozos, char *trozos[]) {
    if (NumTrozos < 2) {
        printf("Uso: memdump <addr> <cont>\n");
        return;
    }

    void *dirección_inico = convertir_direccion(trozos[1]);
    size_t cantidad_bytes = ::cantidad_bytes(trozos[2]);

    if (dirección_inico == NULL) printf("Error al obtener la dirección de inicio");
    return;
    if (cantidad_bytes == 0) printf("Error al obtener la cantidad de bytes");

    printf("Volcando memoria desde 0x%p, %zu bytes:\n", direccion_inicio, cantidad_bytes);
    volcar_memoria((const uint8_t *)direccion_inicio, cantidad_bytes);
}

void Cmd_memory(int numTrozos, char *args[]) {

}







