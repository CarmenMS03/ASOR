#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
//SERVIDOR UDP: getaddrinfo->socket->bind->recvfrom->sendto

void sigterm_handler(int sig){
    printf("Proceso %d terminando...\n", getpid());
    exit(0);
}

int main(int argc, char* argv[]){
    struct addrinfo hints;
    struct addrinfo *result;

    memset(&hints,0,sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;

    int e = getaddrinfo(argv[1],argv[2],&hints,&result);
    if(e!=0) fprintf(stderr, "Error en gai:%s",gai_strerror(e));

    int sd = socket(result->ai_family,result->ai_socktype,0);

    if (bind(sd, result->ai_addr, result->ai_addrlen) != 0){
        perror("Error en bind");
        return 1;
    }
    signal(SIGTERM, sigterm_handler);

    for(int i =0; i<5; i++){
        int f = fork();

        if(f==0){//hijo
            while(1){
                struct sockaddr_storage peer_addr;
                socklen_t peer_addrlen = sizeof(struct sockaddr_storage);
                char buf;
                ssize_t nread = recvfrom(sd,&buf,1,0,(struct sockaddr*)&peer_addr,&peer_addrlen);
                char host[NI_MAXHOST], serv[NI_MAXSERV];
                getnameinfo((struct sockaddr*)&peer_addr,peer_addrlen,host,NI_MAXHOST,serv,NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV);
                printf("El servidor %d, desde host(%s) con serv(%s) se recibe %c\n",getpid(),host,serv,buf);
                if(buf=='t'){
                    time_t s;
                    s = time(NULL);
                    struct tm* t = localtime(&s);
                    char msg[256];
                    strftime(msg,sizeof(msg),"%X\n",t);
                    sendto(sd,&msg,strlen(msg),0,(struct sockaddr*)&peer_addr,peer_addrlen);
                }
                else if(buf=='d'){
                    time_t s;
                    s = time(NULL);
                    struct tm* t = localtime(&s);
                    char msg[256];
                    strftime(msg,sizeof(msg),"%d-%m-%Y\n",t);
                    sendto(sd,&msg,strlen(msg),0,(struct sockaddr*)&peer_addr,peer_addrlen);
                }
                else{
                    char msg[256];
                    snprintf(msg,sizeof(msg),"Comando %c no soportado\n",buf);
                    sendto(sd,&msg,strlen(msg),0,(struct sockaddr*)&peer_addr,peer_addrlen);
                }
            }
            _exit(0);//no es necesario porque en realidad nunca saldra del while
        }
    
    }
    printf("Servidor UDP prefork iniciado. PID padre=%d PGID padre = %d\n", getpid(), getpgid(0));
    while(1) pause();
    
    freeaddrinfo(result);
    close(sd);
    return 0;
}