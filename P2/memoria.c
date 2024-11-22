#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

// Variables globales inicializadas
int global1 = 1, global2 = 2, global3 = 3;

// Variables globales no inicializadas
int global_ni1, global_ni2, global_ni3;

// Funciones del programa
void funcion1() {}
void funcion2() {}
void funcion3() {}

// Estructura para rastrear bloques de memoria asignados
typedef struct Bloque {
    void *direccion;
    size_t tamano;
    struct Bloque *siguiente;
} Bloque;

static Bloque *lista_bloques = NULL;
////////////////////////////////////MEMORY FUNCS////////////////////////////////////////////////////////////////////////
void imprimir_funciones() {
    printf("Funciones programa      %p,    %p,    %p\n",
           (void *)funcion1, (void *)funcion2, (void *)funcion3);

    printf("Funciones libreria      %p,    %p,    %p\n",
           (void *)printf, (void *)malloc, (void *)free);
}

void memory_funcs() {
    imprimir_funciones();
}
////////////////////////////////////MEMORY BLOCKS///////////////////////////////////////////////////////////////////////
void registrar_bloque(void *direccion, size_t tamano) {
    Bloque *nuevo_bloque = (Bloque *)malloc(sizeof(Bloque));
    if (nuevo_bloque == NULL) {
        perror("Error al registrar bloque");
        return;
    }
    nuevo_bloque->direccion = direccion;
    nuevo_bloque->tamano = tamano;
    nuevo_bloque->siguiente = lista_bloques;
    lista_bloques = nuevo_bloque;
}

void liberar_bloque(void *direccion) {
    Bloque *actual = lista_bloques, *anterior = NULL;
    while (actual != NULL) {
        if (actual->direccion == direccion) {
            if (anterior == NULL) {
                lista_bloques = actual->siguiente;
            } else {
                anterior->siguiente = actual->siguiente;
            }
            free(actual);
            return;
        }
        anterior = actual;
        actual = actual->siguiente;
    }
}

void imprimir_bloques_asignados() {
    printf("******Lista de bloques asignados para el proceso %d\n", getpid());
    Bloque *actual = lista_bloques;
    while (actual != NULL) {
        printf("Bloque en %p, tamaño %zu bytes\n", actual->direccion, actual->tamano);
        actual = actual->siguiente;
    }
}

void *asignar_memoria(size_t tamano) {
    void *direccion = malloc(tamano);
    if (direccion == NULL) {
        perror("Error al asignar memoria");
        return NULL;
    }
    registrar_bloque(direccion, tamano);
    return direccion;
}

void liberar_memoria(void *direccion) {
    liberar_bloque(direccion);
    free(direccion);
}

void memory_blocks() {
    imprimir_bloques_asignados();
}
////////////////////////////////////MEMORY VARS/////////////////////////////////////////////////////////////////////////
void imprimir_variables() {
    int local1, local2, local3; // Variables locales

    // Variables estáticas inicializadas
    static int static1 = 10, static2 = 20, static3 = 30;

    // Variables estáticas no inicializadas
    static int static_ni1, static_ni2, static_ni3;

    printf("Variables locales       %p,    %p,    %p\n",
           (void *)&local1, (void *)&local2, (void *)&local3);

    printf("Variables globales      %p,    %p,    %p\n",
           (void *)&global1, (void *)&global2, (void *)&global3);

    printf("Var (N.I.)globales      %p,    %p,    %p\n",
           (void *)&global_ni1, (void *)&global_ni2, (void *)&global_ni3);

    printf("Variables staticas      %p,    %p,    %p\n",
           (void *)&static1, (void *)&static2, (void *)&static3);

    printf("Var (N.I.)staticas      %p,    %p,    %p\n",
           (void *)&static_ni1, (void *)&static_ni2, (void *)&static_ni3);
}

void memory_vars() {
    imprimir_variables();
}
//////////////////////////////////PMAP//////////////////////////////////////////////////////////////////////////////////
void Do_MemPmap() {
    pid_t pid = getpid(); // Obtener el PID del proceso actual
    char comando[256];
    snprintf(comando, sizeof(comando), "pmap %d", pid);

    // Encabezado del comando
    printf("\nmemory -pmap\n");
    int resultado = system(comando); // Ejecutar el comando pmap

    if (resultado == -1) {
        perror("Error al ejecutar pmap");
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void memory_all() {
    imprimir_variables();
    imprimir_funciones();
    imprimir_bloques_asignados();
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void *direccion_inicio(const char *arg) {
    return (void *)strtoull(arg, NULL, 16);
}

size_t cantidad_bytes(const char *arg) {
    return (size_t)strtoull(arg, NULL, 10);
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

void *convertir_direccion(const char *direccion_str) {
    void *direccion = (void *)strtoull(direccion_str, NULL, 16);
    if (direccion == NULL) {
        printf("Error: dirección de memoria inválida.\n");
    }
    return direccion;
}

FILE *abrirArchivo(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error al abrir archivo");
    }
    return file;
}

size_t leer_bytes(FILE *file, void *addr, size_t tamano) {
    size_t bytes_leidos = fread(addr, 1, tamano, file);

    if (bytes_leidos < tamano) {
        if (feof(file)) {
            printf("Fin del archivo alcanzado. Bytes leídos: %zu\n", bytes_leidos);
        } else if (ferror(file)) {
            perror("Error al leer el archivo");
        }
    }

    return bytes_leidos;
}

void cerrar_archivo(FILE *file) {
    if (file !=NULL) {
        fclose(file);
    }
}


////////////////////////////////////////////COMANDOS////////////////////////////////////////////////////////////////////
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
    memset(direccion, caracter, cantidad);

    printf("llenando %zu bytes de memoria con el byte %c(%02X) a partir de la dirección %p\n",
           cantidad, caracter, caracter, direccion);
}

void Cmd_memdump(int NumTrozos, char *trozos[]) {
    void *direccion_inicio = convertir_direccion(trozos[1]);
    if (direccion_inicio == NULL) {
        printf("Error al obtener la dirección inicial.\n");
        return;
    }

    if (trozos[2] == NULL) {
        printf("Error: el argumento de cantidad de bytes no es válido.\n");
        return;
    }

    size_t cantidad_bytes = strtoul(trozos[2], NULL, 10);
    if (cantidad_bytes == 0) {
        printf("Error al obtener la cantidad de bytes.\n");
        return;
    }

    printf("Volcando memoria desde 0x%p, %zu bytes:\n", direccion_inicio, cantidad_bytes);
    volcar_memoria((const uint8_t *)direccion_inicio, cantidad_bytes); // Función para volcar memoria
}

void Cmd_memory(int numTrozos, char *args[]) {
    if (numTrozos == 1 || (numTrozos == 2 && strcmp(args[1], "-all") == 0)) {
        memory_all();
        return;
    }
    for (int i = 1; i < numTrozos; ++i) {
        if (strcmp(args[i], "-funcs") == 0) {
            memory_funcs();
        } else if (strcmp(args[i], "-vars") == 0) {
            memory_vars();
        } else if (strcmp(args[i], "-blocks") == 0) {
            memory_blocks();
        }else if (strcmp(args[i], "-pmap") == 0) {
            Do_MemPmap();
        }else {
            printf("Comando desconocido: %s\n", args[i]);
        }
    }
}

void Cmd_readfile(int NumTrozos, char *args[]) {
    if (NumTrozos!=4) {
        printf("Faltan parametros\n");
        return;
    }
    const char *filename = args[1];
    const char *add_str = args[2];
    size_t tamano = (size_t)strtoul(args[3], NULL, 10);

    void *addr = convertir_direccion(add_str);
    if (addr == NULL) {
        printf("Dirección inválida");
        return;
    }

    FILE *file = abrirArchivo(filename);
    if (file == NULL) {
        return;
    }
    size_t bytes_leidos = leer_bytes(file, addr, tamano);
    if (bytes_leidos > 0) {
        printf("Bytes leídos: %zu\n", bytes_leidos);
    }
    cerrar_archivo(file);
}












