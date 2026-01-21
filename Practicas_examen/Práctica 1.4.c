#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>

// int contINT = 0;
// int contTSTP = 0;
// int cancelar = 0;

// void handlerINT(int a){
//     contINT++;
// }

// void handlerTSTP(int b){
//     contTSTP++;
// }

// void handlerALRM(int c){
// }

// void handlerUSR1(int d){
//     cancelar = 1;
// }

int main(int argc, char* argv[]){

    //EJ3
    // sigset_t set;
    // sigemptyset(&set);
    // sigaddset(&set,SIGINT);
    // sigaddset(&set,SIGTSTP);

    // sigprocmask(SIG_SETMASK,&set, NULL);
    
    // setenv("SLEEP_SECS","30",0);
    // int v = atoi(getenv("SLEEP_SECS"));
    // sleep(v);

    // sigset_t setpen;
    // sigemptyset(&setpen);
    // sigpending(&setpen);

    // if(sigismember(&setpen,SIGINT)){
    //     printf("Recibida SIGINT\n");
    // }
    // if(sigismember(&setpen,SIGTSTP)){
    //     printf("Recibida SIGTSTP\n");
    //     printf("Desbloqueando SIGTSTP\n");
    //     sigset_t unblock;
    //     sigemptyset(&unblock);
    //     sigaddset(&unblock, SIGTSTP);

    //     sigprocmask(SIG_UNBLOCK, &unblock, NULL);
        
    // }
    // printf("Programa finalizado\n");

    //EJ4
    // struct sigaction actINT;
    // actINT.sa_flags = 0;
    // sigemptyset(&actINT.sa_mask);
    // actINT.sa_handler = handlerINT;
    // sigaction(SIGINT,&actINT,NULL);

    // struct sigaction actTSTP;
    // actTSTP.sa_flags = 0;
    // sigemptyset(&actTSTP.sa_mask);
    // actTSTP.sa_handler = handlerTSTP;
    // sigaction(SIGTSTP,&actTSTP,NULL);

    // while((contTSTP + contINT) < 5){
    // }

    // printf("\nNum de SIGINT: %d\n", contINT);
    // printf("Num de SIGTSTP: %d\n", contTSTP);

    //EJ5
    // struct sigaction actALRM;
    // actALRM.sa_flags = 0;
    // sigemptyset(&actALRM.sa_mask);
    // actALRM.sa_handler = handlerALRM;
    // sigaction(SIGALRM,&actALRM,NULL);

    // struct sigaction actUSR1;
    // actUSR1.sa_flags = 0;
    // sigemptyset(&actUSR1.sa_mask);
    // actUSR1.sa_handler = handlerUSR1;
    // sigaction(SIGUSR1,&actUSR1,NULL);

    // //bloquear SIGALRM Y SIGUSR1 antes para evitar carrera
    // alarm(atoi(argv[1]));
    // //desbloquear SIGALRM Y SIGUSR1 para qeu lleguen al suspend

    // sigset_t set;
    // sigfillset(&set);
    // sigdelset(&set, SIGALRM);
    // sigdelset(&set, SIGUSR1);

    // sigsuspend(&set);//se suspende hasta que una señal que no este en el set se produzca

    // if (cancelar) {
    //     printf("Borrado cancelado\n");
    // } else {
    //     printf("Borrando ejecutable\n");
    //     unlink(argv[0]);   
    // }

    //EJ6
    // int fd[2]; //escritura 1 y lectura 0
    // pipe(fd);
    // pid_t p = fork();

    // if(p==0){//hijo
    //     close(fd[1]);
    //     dup2(fd[0],0);
    //     close(fd[0]);
    //     execlp(argv[3],argv[3],argv[4],NULL);
    // }
    // else{//padre
    //     close(fd[0]);
    //     dup2(fd[1],1);
    //     close(fd[1]);
    //     execlp(argv[1],argv[1],argv[2],NULL);
    // }

    //EJ7
    // int p_h[2];
    // pipe(p_h);

    // int h_p[2];
    // pipe(h_p);

    // pid_t p = fork();

    // if(p==0){//hijo
    //     close(p_h[1]);//cierra escritura de p a h
    //     close(h_p[0]);//cierra lectura de h a p
    //     char buf[100];
    //     int m = 0; //num de mensajes recibidos
    //     while(m<10){
    //         int n = read(p_h[0],buf, sizeof(buf)-1);//lee de la tuberia, cuidado usar sizeof en read
    //         buf[n] = '\0';
    //         printf("Hijo recibe:%s",buf);
    //         fflush(stdout);

    //         sleep(1);//espera un segundo
    //         m++;
    //         if(m == 10) {
    //             write(h_p[1],"q",1);
    //         }
    //         else write(h_p[1],"l",1);
    //     }

    //     close(p_h[0]);
    //     close(h_p[1]);
    //     exit(0);
    // }
    // else{//padre
    //     close(p_h[0]);//cierra lectura de p a h
    //     close(h_p[1]);//cierra escritura de h a p
    //     char buf[100];
    //     char ack;
    //     int termina = 0;
    //     while (!termina) {
    //         printf("Padre: ");
    //         fgets(buf, 100, stdin); //lee de la entrada estandar

    //         write(p_h[1], buf, strlen(buf));
            
    //         read(h_p[0], &ack, 1);

    //         if (ack == 'q') {
    //             printf("Padre: hijo finalizó, terminando.\n");
    //             termina = 1;
    //         }
    //     }

    //     close(p_h[1]);
    //     close(h_p[0]);
    //     wait(NULL);
    // }

    //EJ8
    //mkfifo miT
    //cat miT
    //en otra terminal: echo hola > miT

    //EJ9
    // int fd = open("miT",O_TRUNC|O_WRONLY);
    // char buf[100];
    // snprintf(buf,sizeof(buf),"%s %s\n",argv[1],argv[2]);
    // write(fd,buf,strlen(buf));
    // close(fd);

    //EJ10

    int fd1 = open("t1", O_RDONLY | O_NONBLOCK);
    int fd2 = open("t2", O_RDONLY | O_NONBLOCK);
    char buffer[256];

    while(1){
        fd_set set;
        FD_ZERO(&set);
        FD_SET(fd1,&set);
        FD_SET(fd2,&set);

        int nfds;
        if(fd1>fd2) nfds = fd1+1;
        else nfds = fd2+1;

        select(nfds,&set,NULL,NULL,NULL);

        if(FD_ISSET(fd1,&set)){//primera lista
            int n = read(fd1,buffer,sizeof(buffer)-1);
            if(n>0){//lee
                buffer[n] = '\0';//terminacion
                printf("lectura de t1: %s", buffer);
            }
            else if(n==0){//cuando se cierra la tuberia, reabrir
                close(fd1);
                fd1 = open("t1", O_RDONLY | O_NONBLOCK);
            }

        }
        if(FD_ISSET(fd2,&set)){//segunda lista
            int n = read(fd2,buffer,sizeof(buffer)-1);
            if(n>0){//lee
                buffer[n] = '\0';//terminacion
                printf("lectura de t2: %s", buffer);
            }
            else if(n==0){//cuando se cierra la tuberia, reabrir
                close(fd2);
                fd2 = open("t2", O_RDONLY | O_NONBLOCK);
            }
        }
    }

    close(fd1);
    close(fd2);

    return 0;
}