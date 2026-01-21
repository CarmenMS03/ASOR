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
#include <signal.h>

// int CNT1 = 0, CNT2 = 0;

// void sa_handler1(int a){
//     CNT1++;
// }
// void sa_handler2(int b){
//     CNT2++;
// }

void sa_handler1(int a){
    printf("borra el fichero\n");
}
void sa_handler2(int b){
    printf("detiene borrado\n");
}

int main(int argc, char* argv[]){
    
    //Ejercicio 2
    // pkill sleep en otra terminal y el proceso de sleep termina

    //Ejercicio 3
    /*
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGTSTP);
    
    setenv("SLEEP_SECS","5",0);

    sigprocmask(SIG_SETMASK, &set, NULL);
    int val = atoi(getenv("SLEEP_SECS"));
    
    
    sleep(val);
    sigset_t set1;
    sigemptyset(&set1);
    sigpending(&set1);

    if(sigismember(&set1, SIGINT)){
        printf("recibe sigint\n");
    }
    if(sigismember(&set1, SIGTSTP)){
        printf("recibe sigtstp\n");

        if(sigismember(&set1, SIGINT)) sigdelset(&set1, SIGINT);
        sigprocmask(SIG_UNBLOCK,&set1,NULL);//desbloquea la señal de tstp y esta para el proceso
        printf("terminado\n");
    }*/

    //Ejercicio 4
    // struct sigaction sa;
    // sa.sa_handler = sa_handler1;

    // sigaction(SIGINT,&sa,NULL);

    // struct sigaction sa1;
    // sa1.sa_handler = sa_handler2;
    // sigaction(SIGTSTP,&sa1,NULL);

    // while((CNT1+CNT2)<10){}

    // printf("%d de SIGINT y %d de SIGTSTP\n", CNT1, CNT2);

    //Ejercicio 5
    // sigset_t set;
    // sigfillset(&set);
    // sigdelset(&set, SIGALRM);
    // sigdelset(&set, SIGUSR1);

    // struct sigaction sa;
    // sa.sa_handler = sa_handler1;

    // sigaction(SIGALRM,&sa,NULL);

    // struct sigaction sa1;
    // sa1.sa_handler = sa_handler2;
    // sigaction(SIGUSR1,&sa1,NULL);

    // alarm(atoi(argv[1]));
    // sigsuspend(&set);

    //Ejercicio 6
    
    // int a[2];
    // pipe(a);

    // int pid = fork();

    // if(pid==0){
    //     close(a[1]);
    //     dup2(a[0],0);
    //     close(a[0]);
    //     execlp(argv[3],argv[3],argv[4],NULL);

    // }
    // else{
    //     close(a[0]);
    //     dup2(a[1],1);
    //     close(a[1]);
    //     execlp(argv[1],argv[1],argv[2],NULL);
    // }

    //Ejercicio 7

    // int p_h[2];
    // pipe(p_h);

    // int h_p[2];
    // pipe(h_p);

    // int pid = fork();

    // if(pid==0){
    //     close(p_h[1]);
        
    //     close(h_p[0]);

    //     char buffer[100];
    //     read(p_h[0], buffer, 100);
    //     write(1, buffer,100);
    //     sleep(1);
    //     write(h_p[1],"1",2);

    // }
    // else{
    //     close(p_h[0]);

    //     close(h_p[1]);

    //     char buffer[100];
    //     read(0,buffer,100);
    //     write(p_h[1],buffer,100);
    //     read(h_p[0],buffer,100);
    //     printf("%s\n",buffer);

    // }

    //Ejercicio 8
    // mkfifo miTuberia             //OTRO TERMINAL: echo h > miTuberia
    // cat miTuberia

    //Ejercicio 9
    // int fd = open("miTuberia",O_WRONLY); //la que se haya creado antes

    // char buffer [200];
    // snprintf(buffer, sizeof(buffer), "%s\n", argv[1]); //esto es para poner el salto de linea
    // write(fd, buffer, strlen(buffer));
    // close(fd);

    //Ejercicio 10
    int fd1 = open("t1", O_RDONLY | O_NONBLOCK);
    int fd2 = open("t2", O_RDONLY | O_NONBLOCK);
    char buffer[256];

    while (1) {
        
        fd_set set;
        FD_ZERO(&set);
        FD_SET(fd1, &set);
        FD_SET(fd2, &set);

        int nfds;
        if(fd1>fd2) nfds = fd1+1;
        else nfds = fd2+1;

        select(nfds, &set, NULL, NULL, NULL);

        if (FD_ISSET(fd1, &set)) { //leer de la primera
            ssize_t n = read(fd1, buffer, 255);
            if (n > 0) {
                buffer[n] = '\0';
                printf("lectura de t1: %s", buffer);
            } 
            else if (n == 0) {//reabrir tuberia
                close(fd1);
                fd1 = open("t1", O_RDONLY | O_NONBLOCK);
            }
        }

        if (FD_ISSET(fd2, &set)) { //leer de la segunda
            ssize_t n = read(fd2, buffer, 255);
            if (n > 0) {
                buffer[n] = '\0';
                printf("lectura de t2: %s",buffer);
            } 
            else if (n == 0) {//reabrir tuberia
                close(fd2);
                fd2 = open("t2", O_RDONLY | O_NONBLOCK);
            } 
        }
    }

    close(fd1);
    close(fd2);

    return 0;

}

