#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

//SERVIDOR TCP: getaddrinfo->socket->bind->listen->accept->getnameinfo->recv->send->close

void sigchld_handler(int signo) {
    int status;
    pid_t pid;
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        printf("Hijo %d finalizado\n", pid);
    }
}

int main(int argc, char*argv[]){

    struct addrinfo hints;
    struct addrinfo *result;

    memset(&hints,0,sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    int e = getaddrinfo(argv[1],argv[2],&hints,&result);
    if(e!=0) fprintf(stderr, "Error en gai:%s",gai_strerror(e));

    int sd = socket(result->ai_family,result->ai_socktype,0);

    if (bind(sd, result->ai_addr, result->ai_addrlen) != 0){
        perror("Error en bind");
        return 1;
    }

    struct sigaction sa;
    sa.sa_handler = sigchld_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;  
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    //*****
    listen(sd,5);

    while(1){
        struct sockaddr_storage peer_addr;
        socklen_t peer_addrlen = sizeof(struct sockaddr_storage);
        int clifd = accept(sd, (struct sockaddr *)&peer_addr,&peer_addrlen);

        int f = fork();
        if(f==0){
            char host[NI_MAXHOST], serv[NI_MAXSERV];
            getnameinfo((struct sockaddr*)&peer_addr,peer_addrlen,host,NI_MAXHOST,serv,NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV);
            printf("Desde host(%s) con serv(%s)\n",host,serv);

            char buf[256];
            ssize_t n;

            while ((n = recv(clifd, buf, sizeof(buf), 0)) > 0) {
                send(clifd, buf, n, 0);
            }
            

            printf("Conexion terminada con host %s y serv %s\n",host,serv);
            close(clifd);
            _exit(0);
        }
        else{
            close(clifd);
        }
    }

    freeaddrinfo(result);
    close(sd);
    return 0;
}