//Práctica 2: Sistema de ficheros
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/utsname.h>
#include <pwd.h>
#include <time.h>
#include <dirent.h>
#include <sys/time.h>
#include <sys/sysmacros.h>

int main(){

//CREACIÓN Y ATRIBUTOS DE FICHEROS

    //Ejercicio 1 : ls [OPTION] [FILE]-> Por defecto el directorio actual
    //[OPTION]: 
    /*
        -a: no ignora las entradas que empiecen con . (el propio directorio y el padre)
        -l: indica los permisos, fechas etc de cada fichero
        -d: lista directorios no su contenido.
        -i: muestra el inodo de cada fichero
        -R: muestra lo que hay en el directorio y por cada directorio que haya también su contenido.
        -1: un archivo por linea
        -F: indica el tipo de archivo con * o /
        --color[=WHEN]: colorea o no la salida  (always, never, auto)
    
    */

    //Ejercicio 3
    //chmod 645 fichero
    //chmod u=rw, g=r, o=rx fichero

    //Ejercicio 4
    //mkdir dir
    //chmod 666 dir
    //cd dir/
    //bash: cd: dir/: Permission denied

    //Ejercicio 5
    // int fd = open("/home/ubuntu/Documents/Practicas/P1/f1.txt",O_CREAT,0645);

    // if(fd==-1){
    //     perror("Error en open");
    //     return 1;
    // }
    // close(fd);
    
    //-rw-r--r-x 1 ubuntu ubuntu     0 Sep 22 09:17 f1.txt

    //Ejercicio 6
    //umask 0027
    //mkdir dir1
    //ls -l: drwxr-x--- 2 ubuntu ubuntu  4096 Sep 22 09:21 dir1

    //Ejercicio 7

    // umask(0027);
    // int fd = open("/home/ubuntu/Documents/Practicas/P1/f1.txt",O_CREAT,0666); -> Por defecto un fichero se crea con permisos 0666 y los directorios 0777

    // if(fd==-1){
    //     perror("Error en open");
    //     return 1;
    // }
    // close(fd);

    //con umask muestra la mascara del shell

    //Ejercicio 8
    /*
        >stat f1.txt

        File: f1.txt
        Size: 0               Blocks: 0          IO Block: 4096   regular empty file
        Device: 801h/2049d      Inode: 768076      Links: 1
        Access: (0664/-rw-rw-r--)  Uid: ( 1001/  ubuntu)   Gid: ( 1001/  ubuntu)
        Access: 2025-09-24 17:25:44.990325177 +0000
        Modify: 2025-09-24 17:06:48.766528334 +0000
        Change: 2025-09-24 17:25:44.814237180 +0000
        Birth: 2025-09-24 17:06:48.766528334 +0000
    */

    //Ejercicio 9

    // struct stat s;
    // int e = stat("/home/ubuntu/Documents/Practicas/P1/f1.txt", &s);
    // if(e==-1){
    //     perror("Error en stat");
    //     return 1;
    // }

    // char tipo[20]; 
    // if(S_ISREG(s.st_mode)) tipo = "regular";
    // else if(S_ISDIR(s.st_mode)) tipo = "directorio";

    // printf("major: %d, minor: %d, inodo: %ld, tipo: %s , hora: %ld \n", major(s.st_dev),  minor(s.st_dev), s.st_ino, tipo, s.st_atime );

    //st_mtime : la última vez que se ha modificado el fichero y st_ctime: último cambio en el inodo

    //Ejercicio 10
    //ln -s f1.txt enlace 
    //ln -s dir enlacedir

    //link f1.txt  enlaceduro
    //link dir enlacedirduro --> NO se pueden hacer enlaces duros a directorios.

    //No pasa nada al borrar un enlace duro simplemente decrementa el numero de referencias en la tabla global. Borrar un enlace simbólico no hace nada, borrar el original deja los simbólicos nulos.
    
    //Ejercicio 11
    // struct stat s;
    // char* fichero = "/home/ubuntu/Documents/Practicas/P1/f1.txt";
    // int e = stat("/home/ubuntu/Documents/Practicas/P1/f1.txt", &s);
    // if(e==-1){
    //     perror("Error en stat");
    //     return 1;
    // }

    //char name[500];

    // if(S_ISREG(s.st_mode)){
        //sprintf(name, "%s.hard", argv[1]); // Argumento a pasar a link y symlink para crear el nuevo nombre
    //     link(fichero, "/home/ubuntu/Documents/Practicas/P1/f1.hard");
    //     symlink (fichero, "/home/ubuntu/Documents/Practicas/P1/f1.sym");
    // }


//REDIRECCIONES Y DUPLICACIÓN DE DESCRIPTORES

    //Ejercicio 12
    
    // int ant= dup(1);
    // int fd = open("/home/ubuntu/Documents/Practicas/P1/f1.txt",O_WRONLY);
    // dup2(fd,1);
    // printf("aaa\n");
    // fflush(stdout);//no estan sincronizadas con write puede arreglarse¿?

    // dup2(ant, 1);
    // printf("Estamos de vuelta\n");
    // close(fd);

    //Ejercicio 13
    
    // int fd = open("/home/ubuntu/Documents/Practicas/P1/f1.txt",O_WRONLY);
    // dup2(fd,1);
    // dup2(fd, 2);
    
    // printf("estandar\n");
    // fflush(stdout); //no estan sincronizadas con write puede arreglarse¿?
    // perror("error\n");
    // close(fd);

//DIRECTORIOS

    //Ejercicio 17

    DIR *d = opendir("."); //  "/home/ubuntu/Documents/Practicas/P1" con el . abre el directorio actual
    struct dirent *sd;
    long tam = 0; //para calcular lo que ocupan los ficheros reg

    while((sd=readdir(d)) !=NULL){
        
        struct stat s;
        int e = lstat(sd->d_name, &s); //usar lstat porque no sigue los enlaces simbólicos, los lee como enlaces simbólicos y no como a lo que apuntan

        if(S_ISLNK(s.st_mode)){
            char buf [20];
            ssize_t lon = readlink(sd->d_name, buf,sizeof(buf)-1);
            buf[lon] = '\0'; //el readlink  no pone el caracter de terminacion hay que ponerlo a mano
            printf("%s->%s \n", sd->d_name, buf);
        }
        else if(S_ISDIR(s.st_mode)){
            printf("%s/ \n", sd->d_name);
        }
        else if(S_ISREG(s.st_mode)){
            printf("%s", sd->d_name);
            if (s.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH)) printf("*");
            printf("\n");
            tam += s.st_size;
        }
        else{
            printf("%s\n", sd->d_name);
        }
    }

    closedir(d);
    printf("Tam ficheros regulares: %ld KB\n", tam/1024);

    return 0;
}