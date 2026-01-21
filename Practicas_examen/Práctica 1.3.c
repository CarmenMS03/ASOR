#include <sched.h>
#include <string.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[]){

    //EJ2
    // int p = sched_getscheduler(0); //coge la politica de planificacion
    // if(p == SCHED_FIFO) printf("Politica fifo ");
    // else if(p == SCHED_OTHER) printf("Politica estandar ");
    // else if (p == SCHED_RR) printf("Politica round robin ");

    // struct sched_param sp;
    // sched_getparam(0,&sp);
    // printf("Prioridad %d ", sp.sched_priority);

    // printf("Max: %d, Min: %d\n", sched_get_priority_max(p),sched_get_priority_min(p)); //devuelve el valor de la prioridad edel proceso
    // printf("Usando getpriority: %d\n", getpriority(PRIO_PROCESS,0)); //devuelve el valor del nice

    //EJ3
    //Se heredan los atributos de planificación al cambiar en la shell el proceso hijo que ejecuta el programa tiene los mismos atributos.
    
    //EJ4
    // ps -l
    // ps -o pid,pgid,sid,state,args
    // Los procesos creados por una shell pertenecen a la misma sesión que esta, comparten SID. Cuando se ejecuta un nuevo comando, 
    // se crea un nuevo grupo de procesos cuyo identificador coincide con el PID del proceso creado (es el líder de este nuevo grupo).
    
    //EJ5
    // printf("PID: %d PPID: %d PGID: %d SID: %d\n", getpid(), getppid(),getpgid(0),getsid(0));

    // struct rlimit rl;
    // getrlimit(RLIMIT_NOFILE,&rl);
    // int m = rl.rlim_max;
    // printf("Max de ficheros: %d\n",m);

    // char path [100];
    // getcwd(path, sizeof(path));
    // printf("Directorio: %s\n",path);

    //EJ6
    // pid_t p = fork(); //crear nuevo proceso

    // if(p == -1) perror("Error en fork");
    // else if(p == 0){//hijo
        
    //     setsid();
    //     sleep(15);
    //     printf("PID: %d PPID: %d PGID: %d SID: %d\n", getpid(), getppid(),getpgid(0),getsid(0));
        
    //     chdir("/tmp");
    //     char path [100];
    //     getcwd(path, sizeof(path));
    //     printf("Directorio: %s\n",path);
    // }
    // else{//padre
    //     sleep(15);
    //     printf("PID: %d PPID: %d PGID: %d SID: %d\n", getpid(), getppid(),getpgid(0),getsid(0));
        
    // }
    //si el padre termina primero, el hijo queda huerfano y su ppid pasa a ser 1
    //si el hijo termina primero, queda en estado zombie para que el padre recoja su salida ocupando una entrada en la tabla de procesos
    // si el sleep del demonio es antes del setsid: padre,hijo y terminal en la misma sesion por lo que ctrl c los mata
    // si el sleep del demonio es después del setsid: padre y terminal en la misma sesion (ctrl c mata al padre) pero el hijo esta en otra sesion sin terminal asociado (tty ?)
    
    //EJ7
    // pid_t p = fork();
    // if(p==0){//hijo
    //     execvp(argv[1], &argv[1]);
    //     printf("El comando terminó de ejecutarse");
    // }
    // else{
    //     wait(NULL);
    // }
    // system(argv[1]); //hace el comando mandado por teclado: interiormente usa execl ejecutado por otro proceso tras un fork, para despues hacer un wait y volver al programa ppal
    // printf("El comando terminó de ejecutarse\n");
    //solo se imprime la cadena con system ya que en el caso anterior el proceso hijo sale de este programa y no vuelve para hacer el printf
    /*En la versión que utiliza system(3), la cadena se imprime porque system() crea un proceso hijo para ejecutar el comando y el proceso padre espera su finalización, retomando posteriormente la ejecución del programa.
    En cambio, en la versión que utiliza execvp(3), la cadena no se imprime ya que execvp() reemplaza la imagen del proceso actual y no retorna si la ejecución tiene éxito.*/
    
    //EJ8
    
    pid_t pid = fork();

    if(pid == 0){
        setsid();
        chdir("/tmp");

        int fd = open("/tmp/daemon.out",O_CREAT|O_WRONLY|O_TRUNC);
        dup2(fd,1);
        close(fd);
        int fd2 = open("/tmp/daemon.err",O_CREAT|O_WRONLY|O_TRUNC);
        dup2(fd2, 2);
        close(fd2);
        int fd3 = open("/dev/null",O_RDONLY);
        dup2(fd3, 0);
        close(fd3);

        execvp(argv[1], &argv[1]);
        
    } 
    else{
        _exit(0);
    }
    
    return 0;
}