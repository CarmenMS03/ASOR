#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/utsname.h>
#include <pwd.h>
#include <time.h>
#include <sys/time.h>

int main(){
    //GESTION DE ERRORES

        //EJ1 , EJ2
    // int er = setuid(0);

    // if(er ==-1){
    //     perror("Error en setuid");
    //     printf("El codigo de error es: %d y la descripcion: %s\n",errno,strerror(errno));
    // }
    //return 1

        //EJ3
    // for(int i =0; i<=255; i++){
    //     printf("El codigo de error es: %d y la descripcion: %s\n",i,strerror(i));
    // }
    //return 1;

    //INFORMACION DEL SISTEMA

    //EJ5
    // struct utsname buf;
    // int er = uname (&buf);
    // if(er==-1){
    //     perror("Error en uname");
    //     return -1;
    // }
    // printf("Sistema: %s, nombre: %s, lanzamiento: %s, version: %s, maquina: %s, dominio: %s\n",buf.sysname,buf.nodename,buf.release,buf.version,buf.machine,buf.__domainname);

    // return 0;

    //EJ6
    // printf("Long max argumentos: %ld, Num max de hijos: %ld, Num max ficheros: %ld\n", sysconf(_SC_ARG_MAX),sysconf(_SC_CHILD_MAX),sysconf(_SC_OPEN_MAX));
    // return 0;

    //EJ7
    // char* path = "/home/ubuntu/Documents/Practica_examen/P1/P1_1.c"; // char path[] = "/home/ubuntu/Documents/Practica_examen/P1/P1_1.c";
    // printf("Num max de enlaces: %ld, Tam max de ruta: %ld, Tam max de nombre: %ld\n", pathconf(path,_PC_LINK_MAX),pathconf(path,_PC_PATH_MAX),pathconf(path,_PC_NAME_MAX));
    // return 0;

    //INFORMACION DEL USUARIO

    //EJ9, EJ10
    // uid_t uid = getuid();
    // struct passwd* buf = getpwuid(uid);

    // printf("UID real: %d, UID efectivo: %d, Nombre: %s, Home: %s, Descripcion: %s \n",uid,geteuid(), buf->pw_name, buf->pw_dir, buf->pw_gecos);
    // return 0;

    //INFORMACION HORARIA DEL SISTEMA

    //EJ12
    // printf("Segundos desde el epoch: %ld\n", time(NULL));
    // return 0;

    //EJ14
    // time_t sec;
    // time(&sec);
    // struct tm *buf = localtime (&sec);
    // printf("El anio es: %d\n",buf->tm_year + 1900);
    // return 0;

    //EJ15
    time_t sec;
    time(&sec);
    struct tm *buf = localtime (&sec);
    char cadena [100];
    strftime(cadena, 100, "%a %b %d %H:%M:%S %Y", buf);
    printf("Fecha: %s\n",cadena);
    return 0;

}