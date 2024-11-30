# P2 - SO

> C mola porque no hay que saber mucho para usarlo, solo saber hacerlo bien.

## Comandos

### P0

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

### P1

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

### P2

- [x] allocate [-malloc|-mmap|-createshared|-shared]
- [x] deallocate [-malloc|-mmap|-shared|-delkey]
- [x] memfill [addr] [ch cont|cont]
- [x] memdump [addr] [cont]
- [x] memory [-funcs|-vars|-blocks|-all|-pmap]
- [x] readfile [file] [addr] [cont]
- [ ] writefile [file] [addr] [cont]
- [ ] read [df] [addr] [cont]
- [ ] write [df] [addr] [cont]
- [x] recurse [n]

### P3

- [ ] getuid
- [ ] setuid [-l] id
- [ ] showvar v1 v2 ..
- [ ] changevar [-a|-e|-p] var val
- [ ] subsvar [-a|-e] v1 v2 val
- [ ] environ [-environ|-addr]
- [ ] fork
- [ ] search [-add dir|-del dir|-clear|-path]
- [ ] exec progspec
- [ ] exec-pri prio progspec
- [ ] fg progspe
- [ ] fgpri prio progspec
- [ ] back progspec
- [ ] backpri prio progspec
- [ ] listjobs
- [ ] deljobs -term|-sig
- [ ] \*****
