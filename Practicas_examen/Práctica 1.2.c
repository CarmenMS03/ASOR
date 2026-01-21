#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/sysmacros.h>
#include <string.h>
#include <dirent.h>

int main(int argc, char* argv[]){

    //EJ5
    // int fd = open ("/home/ubuntu/Documents/Practica_examen/P2/f.txt",O_CREAT,0645);
    // close(fd);

    //EJ6: umask 0027

    //EJ7
    //umask(0027);
    // int fd = open ("/home/ubuntu/Documents/Practica_examen/P2/f.txt",O_CREAT,0645);
    // close(fd);

    //EJ9
    // struct stat buf;
    // int er = stat("/home/ubuntu/Documents/Practica_examen/P2/P1_2.c",&buf);
    // if(er==-1){
    //     perror("Error en stat");
    //     return 1;
    // }

    // if(S_ISREG(buf.st_mode)) printf("Fichero regular ");
    // else if(S_ISLNK(buf.st_mode)) printf("Enlace simbólico ");
    // else if(S_ISDIR(buf.st_mode)) printf("Directorio ");

    // printf("Major: %d, minor: %d, inodo: %ld, acceso: %ld \n", major(buf.st_dev), minor(buf.st_dev), buf.st_ino, buf.st_atime);

    //EJ11
    // struct stat buf;
    // stat (argv[1],&buf);
    // if(S_ISREG(buf.st_mode)){
    //     //simbolico
    //     char cadena1[20];
    //     sprintf(cadena1, "%s.sym",argv[1]);
    //     symlink(argv[1],cadena1);
    //     //rigido
    //     char cadena2[20];
    //     sprintf(cadena2, "%s.hard",argv[1]);
    //     link(argv[1],cadena2);
    // }

    //EJ12
    // int fd;
    // fd = open(argv[1],O_APPEND||O_WRONLY);
    // dup2(fd,1);
    // printf("Hola\n");

    //EJ13
    // int fd;
    // fd = open(argv[1],O_APPEND|O_WRONLY);
    // dup2(fd,1);
    // dup2(fd,2);
    // printf("Hola\n");
    // fflush(stdout);
    // perror("error");

    //EJ17
    DIR *d = opendir(argv[1]);
    struct dirent *dir;
    dir = readdir(d);
    double tam = 0;
    while(dir != NULL){
        struct stat buf;
        lstat(dir->d_name,&buf); //no sigue enlaces simbolicos
        if(S_ISREG(buf.st_mode)){
            printf("%s",dir->d_name);
            if(buf.st_mode &(S_IXUSR|S_IXGRP| S_IXOTH)){
                printf("*");
            }
            printf("\n");
            tam += buf.st_size;
        }
        else if(S_ISDIR(buf.st_mode)){
            printf("%s/ \n",dir->d_name);
        }
        else if(S_ISLNK(buf.st_mode)){
            char path[100];
            ssize_t lon = readlink(dir->d_name,path, 98);
            path[lon] ='\0';
            printf("%s -> %s\n",dir->d_name,path);
        }
        dir = readdir(d);
    }
    tam = tam/1024;
    printf("Tam: %f\n", tam);
    return 0;
}