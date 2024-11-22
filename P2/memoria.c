// Pablo Portas López           pablo.portas
// Pablo Míguez Mouiño          pablo.miguez.moino

#include "memoria.h"
#include "help.h"

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

size_t escribir_bytes(FILE *file, const void *addr, size_t count) {
    if (file == NULL || addr == NULL) {
        fprintf(stderr, "Error: Archivo o dirección de memoria no válidos.\n");
        return 0;
    }
    size_t bytes_escritos = fwrite(addr, 1, count, file);
    if (bytes_escritos < count) {
        perror("Error al escribir en el archivo");
    }
    return bytes_escritos;
}

ssize_t leer_desde_descriptor(int fd, void *addr, size_t count) {
    if (fd < 0 || addr == NULL) {
        fprintf(stderr, "Error: Descriptor de archivo o dirección de memoria no válidos.\n");
        return -1;
    }

    ssize_t bytes_leidos = read(fd, addr, count);
    if (bytes_leidos < 0) {
        perror("Error al leer desde el descriptor de archivo");
    }

    return bytes_leidos;
}

ssize_t escribir_en_descriptor(int fd, const void *addr, size_t count) {
    if (fd < 0 || addr == NULL) {
        fprintf(stderr, "Error: Descriptor de archivo o dirección de memoria no válidos.\n");
        return -1;
    }

    ssize_t bytes_escritos = write(fd, addr, count);
    if (bytes_escritos < 0) {
        perror("Error al escribir en el descriptor de archivo");
    }

    return bytes_escritos;
}

static char static_array[2048];

void recursive_function(int n, int *param_address) {
    char automatic_array[2048];

    printf("parametro:  %d(%p) array %p, arr estatico %p\n",
           n, (void *)param_address, (void *)automatic_array, (void *)static_array);

    if (n > 0) {
        recursive_function(n - 1, &n);
    }
}


////////////////////////////////////////////COMANDOS////////////////////////////////////////////////////////////////////
void Cmd_memfill(int NumTrozos, char *trozos[]) {
    if (NumTrozos >= 1 && !strcmp(trozos[1], "-?")) {
        Help_memfill();
        return;
    }

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
    if (NumTrozos == 0 || (NumTrozos >= 1 && !strcmp(trozos[1], "-?"))) {
        Help_memdump();
        return;
    }

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

void Cmd_memory(int NumTrozos, char *trozos[]) {
    if (NumTrozos == 0 || (NumTrozos >= 1 && !strcmp(trozos[1], "-?"))) {
        Help_memory();
        return;
    }

    if (NumTrozos == 1 || (NumTrozos == 2 && strcmp(trozos[1], "-all") == 0)) {
        memory_all();
        return;
    }
    for (int i = 1; i < NumTrozos; ++i) {
        if (strcmp(trozos[i], "-funcs") == 0) {
            memory_funcs();
        } else if (strcmp(trozos[i], "-vars") == 0) {
            memory_vars();
        } else if (strcmp(trozos[i], "-blocks") == 0) {
            memory_blocks();
        }else if (strcmp(trozos[i], "-pmap") == 0) {
            Do_MemPmap();
        }else {
            printf("Comando desconocido: %s\n", trozos[i]);
        }
    }
}

void Cmd_readfile(int NumTrozos, char *trozos[]) {
    if (NumTrozos >= 1 && !strcmp(trozos[1], "-?")) {
        Help_readfile();
        return;
    }

    if (NumTrozos!=4) {
        printf("Faltan parametros\n");
        return;
    }
    const char *filename = trozos[1];
    const char *add_str = trozos[2];
    size_t tamano = (size_t)strtoul(trozos[3], NULL, 10);

    void *addr = convertir_direccion(add_str);
    if (addr == NULL) {
        printf("Dirección inválida");
        return;
    }

    FILE *file = abrirArchivo(filename);
    if (file == NULL) {
        return;
    }
    const size_t bytes_leidos = leer_bytes(file, addr, tamano);
    if (bytes_leidos > 0) {
        printf("Bytes leídos: %zu\n", bytes_leidos);
    }
    cerrar_archivo(file);
}

void Cmd_writefile(int NumTrozos, char *trozos[]) {
    if (NumTrozos >= 1 && !strcmp(trozos[1], "-?")) {
        Help_writefile();
        return;
    }

    if (NumTrozos != 4) {
        printf("Parametros incorrectos\n");
        return;
    }
    const char *filename = trozos[1];
    const char *direccion_str = trozos[2];
    const size_t count = (size_t)strtoull(trozos[3], NULL, 10);

    const void *addr = convertir_direccion(direccion_str);
    if (addr == NULL) {
        printf("Error: dirección de memoria inválida.\n");
        return;
    }

    FILE *file = abrirArchivo(filename);
    if (file == NULL) {
        return;
    }
    const size_t bytes_escritos = escribir_bytes(file, addr, count);
    if (bytes_escritos > 0) {
        printf("Bytes escritos: %zu\n", bytes_escritos);
    }
    fclose(file);
}

void Cmd_read(int NumTrozos, char *trozos[]) {
    if (NumTrozos >= 1 && !strcmp(trozos[1], "-?")) {
        Help_read();
        return;
    }

    if (NumTrozos != 4) {
        printf("Parametros incorrectos\n");
        return;
    }
    int fd = atoi(trozos[1]);
    const char *direccion_str = trozos[2];
    size_t count = (size_t)strtoull(trozos[3], NULL, 10);

    void *direccion = convertir_direccion(direccion_str);
    if (direccion == NULL) {
        return;
    }
    ssize_t bytes_leidos = leer_desde_descriptor(fd, direccion, count);
    if (bytes_leidos >= 0) {
        printf("Bytes leídos: %zd\n", bytes_leidos);
    }
}

void Cmd_write(int NumTrozos, char *trozos[]) {
    if (NumTrozos >= 1 && !strcmp(trozos[1], "-?")) {
        Help_write();
        return;
    }

    if (NumTrozos != 4) {
        printf("Uso: write <descriptor> <direccion> <bytes>\n");
        return;
    }
    int fd = atoi(trozos[1]);
    const char *direccion_str = trozos[2];
    size_t count = (size_t)strtoull(trozos[3], NULL, 10);
    void *direccion = convertir_direccion(direccion_str);
    if (direccion == NULL) {
        return;
    }

    ssize_t bytes_escritos = escribir_en_descriptor(fd, direccion, count);
    if (bytes_escritos >= 0) {
        printf("Bytes escritos: %zd\n", bytes_escritos);
    }
}

void Cmd_recurse(int NumTrozos, char *trozos[]) {
    if (NumTrozos >= 1 && !strcmp(trozos[1], "-?")) {
        Help_recurse();
        return;
    }

    if (NumTrozos != 2) {
        printf("Uso: recurse <n>\n");
        return;
    }

    int n = atoi(trozos[1]);
    if (n < 0) {
        printf("Error: El número de recursiones debe ser mayor o igual a 0.\n");
        return;
    }

    recursive_function(n, &n);
}









