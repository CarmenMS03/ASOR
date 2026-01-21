//Práctica 1 :Introducción a la programación de sistemas Unix
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
//GESTIÓN DE ERRORES

    // Ejercicio 1

    // int ret = setuid(0); //Error por intenta elevar permisos
    // if(ret == -1){
    //     perror("Error en setuid");
    //     return 1;
    // }

    //Ejercicio 2

    // int ret = setuid(0); //Error por intenta elevar permisos
    // if(ret == -1){
    //     char* msg = strerror(errno);
    //     printf("Codigo de error: %d , Mensaje de error: %s\n", errno, msg);
    //     return 1;   
    // }

    //Ejercicio 3
    
    // for(int i = 0; i < 255; i++) {
    //   char* msg = strerror(i);
    //   printf("Error %d: %s\n", i, msg);
    // }

//INFORMACIÓN DEL SISTEMA

    //Ejercicio 4

    // uname -a en la terminal para obtener toda la información del sistema

    //Ejercicio 5

    // struct utsname st;
    // uname(&st); //Funcion reentrante: se pasa por parametro el struct creado reservando espacio
    // printf("Name: %s, nodename: %s, release: %s, version: %s, machine: %s\n", st.sysname, st.nodename, st.release, st.version, st.machine);

    //Ejercicio 6

    // long max_ficheros = sysconf(_SC_OPEN_MAX);
    // long max_child = sysconf(_SC_CHILD_MAX);

    // printf("Maximo ficheros: %ld, Maximo hijos: %ld\n", max_ficheros, max_child);

    //Ejercicio 7

    // long max_enlaces = pathconf("/home/ubuntu/Documents/Practicas/Practica_1.c", _PC_LINK_MAX);
    // printf("Maximo enlaces: %ld\n", max_enlaces);

//INFORMACIÓN DEL USUARIO

    //Ejercicio 8
    // id por el terminal printea los identificadores de usuario/grupo real/efectivo de un usuario o del actual si no se pone nada.

    //Ejercicio 9: Al hacer ls -l sobre el fichero que se quiere consultar en los permisos tiene que aparecer una s que indica que el bit setuid está activado

    // uid_t id = getuid();
    // uid_t eid = geteuid();
    // printf("uid: %d, euid: %d\n", id, eid);

    //Ejercicio 10

    // uid_t id = getuid();
    // uid_t eid = geteuid();

    // struct passwd* ps = getpwnam("ubuntu"); //Funcion no reentrante: el struct es propiedad del kernel y puede modificarlo. Se devuelve el puntero para consultarlo.

    // printf("id: %d, euid: %d, name: %s, home: %s, desc: %s\n", id, eid, ps->pw_name, ps->pw_dir, ps->pw_gecos); 

//Información horaria del sistema

    //Ejercicio 12

    // time_t tiempo= time(NULL);
    // printf("Hora en segundos desde Epoch: %ld\n", tiempo);

    //Ejercicio 13

    // struct timeval tv_i;  
    // int t_ini = gettimeofday(&tv_i, NULL);

    // long ini = tv_i.tv_sec * 1000000 + tv_i.tv_usec;

    // int i=0; //el bucle no puede ser vacío porque si lo es, el SO optimiza pasando de su ejecución.
    // while (i < 100000) {
    //     i++;
    // }

    // struct timeval tv_f;
    // int t_fin = gettimeofday(&tv_f, NULL);

    // long fin = tv_f.tv_sec * 1000000 + tv_f.tv_usec;

    // long dif = fin - ini;

    // printf("Microsegundos que tarda: %ld\n", dif);

    //Ejercicio 14

    // time_t tiempo = time(NULL);
    // struct tm* t = localtime(&tiempo);
    // printf("Anyo: %d\n", 1900 + t->tm_year); //devuelve el numero de años desde 1900

    //Ejercicio 15
    time_t tiempo = time(NULL);

    struct tm* t = localtime(&tiempo);

    char msg[100];
    strftime(msg, 100, "%a %b %d %H:%M:%S", t);

    printf("Fecha: %s %d\n", msg, 1900 + t->tm_year);


    return 0; 
}