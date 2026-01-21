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
#include <sched.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){

    //Ejercicio 1
    // consultar pid: ps -l
    // cambiar nice: sudo renice -20 1534

    //cambiar politica de privacidad: sudo chrt -f -p 12 1534
    //consultar: chrt -p 1534

    //Ejercicio 2
    // char* pol [20];
    // int pr;
    // struct sched_param param;

    // sched_getparam (0, &param);
    // pr = param.sched_priority;
    // int pl = sched_getscheduler(0);

    // if(pl == SCHED_FIFO) *pol ="fifo";
    // else if(pl == SCHED_OTHER) *pol ="estandar";
    // else *pol ="rr";

    // printf("Politica: %s, prioridad: %d, rango: %d-%d \n", *pol, pr, sched_get_priority_min(pl), sched_get_priority_max(pl));

    // char* pol [20];
    // int pr;

    // pr = getpriority(PRIO_PROCESS,0);
    // int pl = sched_getscheduler(0);

    // if(pl == SCHED_FIFO) *pol ="fifo";
    // else if(pl == SCHED_OTHER) *pol ="estandar";
    // else *pol ="rr";

    // printf("Politica: %s, prioridad: %d, rango: %d-%d \n", *pol, pr, sched_get_priority_min(pl), sched_get_priority_max(pl));

    // getpriority devuelve el valor del nice mientras que sched_getparam devuelve la prioridad del proceso

    // Ejercicio 3: prioridad 12, se hereda

    //Ejercicio 4
    // ps -l
    // ps -ejH
    // Los procesos que comparten la shell tienen el mismo identificador de sesión. 
    // El identificador de grupo al crear un proceso nuevo es el del líder del grupo del proceso que ha creado el nuevo.

    // Ejercicio 5
    // int pid = getpid();
    // int pgid = getpgid(0);
    // int sid = getsid(0);
    // char buffer[100];
    // getcwd(buffer, 100);
    // struct rlimit rlim;
    // getrlimit(RLIMIT_NOFILE, &rlim);
    // int max = rlim.rlim_max;

    // printf("pid: %d, pgid: %d, sid: %d, ruta: %s, ficherosmax: %d\n", pid, pgid, sid, buffer, max);

    // Ejercicio 6
    // pid_t pid = fork();

    // if(pid == 0){//hijo

    //     chdir("/tmp/");
    //     pid_t se = setsid();

    //     int pid = getpid();
    //     int pgid = getpgid(0);
    //     int sid = getsid(0);
    //     char buffer[100];
    //     getcwd(buffer, 100);
    //     struct rlimit rlim;
    //     getrlimit(RLIMIT_NOFILE, &rlim);
    //     int max = rlim.rlim_max;

    //     sleep(5);
    //     int ppid = getppid();
    //     printf("pid: %d, ppid: %d, pgid: %d, sid: %d, ruta: %s, ficherosmax: %d\n", pid, ppid, pgid, sid, buffer, max);
        

    // }
    // else{//padre
    //     printf("fin padre\n");
    // }
    
    // Si el proceso padre termina antes, en el ppid muestra 1, si es el hijo el que termina primero, el ppid es el pid del padre.

    // Al hacer control C, si el padre es el que está durmiendo, sí que muere. Si es el hijo el que está durmiendo, no muere porque está en otra sesión.

    // Ejercicio 7
    // pid_t pid = fork();

    // if(pid==0){//hijo
    //     // char* comnds = {argv[1], argv[2], NULL};
    //     //              argv+1
    //     execvp(argv[1], &argv[1]); // Lee de la segunda posición de argv hacia delante
    //     printf("El comando terminó de ejecutarse");
    // }
    // else{//padre
    //     printf("Terminó el padre");
    // }

    // system(argv[1]);
    // printf("El comando terminó de ejecutarse");

    // Ejercicio 8

    int fd = open("/tmp/daemon.out",O_CREAT|O_WRONLY);
    dup2(fd,1);
    int fd2 = open("/tmp/daemon.err",O_CREAT|O_WRONLY);
    dup2(fd2, 2);
    int fd3 = open("/dev/null",O_CREAT|O_WRONLY);
    dup2(fd3, 0);

    pid_t pid = fork();

    if(pid == 0){
        setsid();
        sleep(5);
        execvp(argv[1], &argv[1]);
    } 
    else{
        int st;
        int opts;
        waitpid(pid, &st, opts);
        printf("El comando terminó de ejecutarse\n");
        printf("Terminó el padre\n");
    }

    return 0;
}