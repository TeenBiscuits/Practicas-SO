# Prácticas SO

> To get acquainted with the C programming language we’ll start to code a
> shell

Un _shell_ con un set de comandos para interactuar con tu sistema operativo. Última versión (entrega) de la práctica
para la asignatura de Sistemas Operativos.

## Compilación y Ejecución

> [!IMPORTANT]  
> Este shell fue desarrollado para sistemas unix. Recomendamos encarecidamente compilarlo y ejecutarlo en **Linux**.
>
> Es posible compilarlo para Mac, pero debe cambiar las librerías debido a las diferencias entre ambos sistemas.

1. Primero clona este repositorio
    ```shell
    git clone https://github.com/TeenBiscuits/Practicas-SO.git
    ```
2. Entra a la carpeta
    ```shell
    cd Practicas-SO  
    ```
3. Compila el programa usando las _flags_ requeridas (es la opción por defecto del Makefile)
    ```shell
    make
    ```
   <details>

   <summary>Todas las opciones del Makefile</summary>

    - ``make all`` o ``make`` (por defecto): Compila el programa con las _flags_ requeridas (`-Wall`)
    - ``make debug``: Compila el programa añadiendo las _flags_ de _debug_ y optimización (`-g -O0`)
    - ``make run``: Compila el programa (como en la opción por defecto) y lo ejecuta acto seguido. Tratará de ejecutarlo
      usando `rlwrap`(1), de no estar instalado lo ejecutará de forma normal.
    - ``make leaks``: Compila el programa (con las _flags_ de `debug`) y trata de ejecutarlo con **Valgrind**.
    - ``make tests``: Compila y ejecuta el programa como en `leaks` e introduce automáticamente por la entrada estandar
      los contenidos del archivo `tests.txt`.

   (1) Al ejecutarlo con `rlwrap` podrás usar las flechas `←`/`→` para moverte por el texto escrito o las otras flechas
   `↑`/`↓` para volver a escribir el texto anteriormente introducido.

   </details>
4. Ejecuta el programa
    ```shell
    ./shell 
    ```
5. Tras esto el prompt de tu terminal debería haber cambiado a uno con el mismo formato que Ubuntu pero con usuario y el
   hostname de la máquina en morado. Ejemplo:
   ```
   user@hostname:~/Practicas-SO$
   ```
6. Para salir ejecuta el comando `exit` o mata el proceso con **Ctrl + C**

## Comandos

> [!NOTE]  
> Esta breve lista fue usada para llevar un registro de los comandos que fueron implementados durante el desarrollo y
> sus diferentes parámetros.
>
> Para ver en detalle que hace cada comando y las notas sobre ellos consulta
> la [Wiki](https://github.com/TeenBiscuits/Practicas-SO/wiki).

### P0 - Comandos básicos

<details>

<summary>Mostrar lista de comandos</summary>

- [x] authors [-l|-n]
- [x] pid
- [x] ppid
- [x] cd [dir]
- [x] date [-t|-d]
- [x] historic [N|-N] **(1)**
- [x] open [file] mode (cr,ap,ex,ro,rw,wo,tr)
- [x] close [df]
- [x] dup [df]
- [x] infosys
- [x] help [cmd]
- [x] quit, exit, bye

(1) _Hypothetically, there’s a scenario where trying to repeat a historic command could yield an infinite loop or a
stack overflow (depending on how it is coded), so students may choose to not store calls to historic N itself in the
historic list if they want so (See the NOTES ON LIST IMPLEMENTATIONS at the end of this document)_

</details>

### P1 - Sistema de Ficheros

<details>

<summary>Mostrar lista de comandos</summary>

- [x] makefile [name]
- [x] makedir [name]
- [x] listfile [-long][-link][-acc] name1 name2 n3 ... lista ficheros; **(2)**
- [x] cwd
- [x] listdir [-hid][-long][-link][-acc] n1 n2 ... lista contenidos de directorios **(3)**
- [x] reclist [-hid][-long][-link][-acc] n1 n2 ... lista recursivamente contenidos de directorios (subdirs después) **(
  3)**
- [x] revlist [-hid][-long][-link][-acc] n1 n2 ... lista recursivamente contenidos de directorios (subdirs antes)
- [x] erase [name1 name2 ..]
- [x] delrec [name1 name2 ..]

(2) -long: listado largo | -acc: acesstime | -link: si es enlace simbolico, el path contenido

(3) -long: listado largo | -hid: incluye los ficheros ocultos | -acc: acesstime | -link: si es enlace simbolico, el path
contenido

</details>

### P2 - Gestión de Memoria

<details>

<summary>Mostrar lista de comandos</summary>

- [x] allocate [-malloc|-mmap|-createshared|-shared]
- [x] deallocate [-malloc|-mmap|-shared|-delkey]
- [x] memfill [addr] [ch cont|cont]
- [x] memdump [addr] [cont]
- [x] memory [-funcs|-vars|-blocks|-all|-pmap]
- [x] readfile [file] [addr] [cont]
- [x] writefile [file] [addr] [cont]
- [x] read [df] [addr] [cont]
- [x] write [df] [addr] [cont]
- [x] recurse [n]

</details>

### P3 - Gestión de Procesos

<details>

<summary>Mostrar lista de comandos</summary>

- [x] getuid
- [x] setuid [-l] id
- [x] showvar v1 v2 ..
- [x] changevar [-a|-e|-p] var val
- [x] subsvar [-a|-e] v1 v2 val
- [x] environ [-environ|-addr]
- [x] fork
- [x] search [-add dir|-del dir|-clear|-path]
- [x] exec [VAR1 VAR2 VAR3 ...] executablefile [arg1 arg2 ...]
- [x] execpri prio [VAR1 VAR2 VAR3 ...] executablefile [arg1 arg2 ...]
- [x] fg [VAR1 VAR2 VAR3 ...] executablefile [arg1 arg2 ...]
- [x] fgpri prio [VAR1 VAR2 VAR3 ...] executablefile [arg1 arg2 ...]
- [x] back [VAR1 VAR2 VAR3 ...] executablefile [arg1 arg2 ...]
- [x] backpri prio [VAR1 VAR2 VAR3 ...] executablefile [arg1 arg2 ...]
- [x] listjobs
- [x] deljobs -term|-sig
- [x] \*****

</details>

## Documentación

En la carpeta de [documentación](/docs) puedes consultar los PDFs y los archivos auxiliares que seguimos para realizar
las 4 entregas de la prácitca.

En la [Wiki de este repositorio](https://github.com/TeenBiscuits/Practicas-SO/wiki) puedes leer más sobre como funciona
el código de este shell. Esperamos que esto te ayude a entender como implementar la práctica.

## Créditos

Licenciado bajo [Apache License 2.0](/LICENSE) por Pablo Portas López y Pablo Míguez Muiño.