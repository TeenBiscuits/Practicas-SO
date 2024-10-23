# P1 - SO

> C mola porque no hay que saber mucho para usarlo, solo saber hacerlo bien.

## Comandos

### P0

- [ ] authors [-l|-n]
- [ ] pid
- [ ] ppid
- [ ] cd [dir]
- [ ] date [-t|-d]
- [ ] historic [N|-N] **(1)**
- [ ] open [file] mode (cr,ap,ex,ro,rw,wo,tr)
- [ ] close [df]
- [ ] dup [df]
- [ ] infosys
- [ ] help [cmd]
- [ ] quit, exit, bye

(1) _Hypothetically, there’s a scenario where trying to repeat a historic command could yield an infinite loop or a stack overflow (depending on how it is coded), so students may choose to not store calls to historic N itself in the historic list if they want so (See the NOTES ON LIST IMPLEMENTATIONS at the end of this document)_

### P1

- [ ] makefile [name]
- [ ] makedir [name]
- [ ] listfile [-long][-link][-acc] name1 name2 n3 ... lista ficheros; **(2)**
- [ ] cwd
- [ ] listdir [-hid][-long][-link][-acc] n1 n2 ... lista contenidos de directorios **(3)**
- [ ] reclist [-hid][-long][-link][-acc] n1 n2 ... lista recursivamente contenidos de directorios (subdirs después) **(3)**
- [ ] revlist [-hid][-long][-link][-acc] n1 n2 ... lista recursivamente contenidos de directorios (subdirs antes)
- [ ] erase [name1 name2 ..]
- [ ] delrec [name1 name2 ..]

(2) -long: listado largo | -acc: acesstime | -link: si es enlace simbolico, el path contenido

(3) -long: listado largo | -hid: incluye los ficheros ocultos | -acc: acesstime | -link: si es enlace simbolico, el path contenido

## Errores

> Los que encontré por ahora

- [ ] El comando "date" provoca un leak de memoria
- [ ] El comando help no ha sido actualizado a todos los comandos
- [ ] El comando help cuando emite un error imprime el comando help y no el comando mandado
- [ ] Cuando se manda un comando -? debemos imprimir la ayuda de ese comando
- [ ] Falta el comando "delrec"
- [ ] Authors no imprime correctamente
- [x] El comando listdir puede ser llamado con ls
- [ ] ...

