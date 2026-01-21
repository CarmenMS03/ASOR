#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

//CLIENTE TCP: getaddrinfo->socket->connect->getnameinfo->send->recv->close
int main(int argc, char*argv[]){

    struct addrinfo hints;
    struct addrinfo *result;

    memset(&hints,0,sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    int e = getaddrinfo(argv[1],argv[2],&hints,&result);
    if(e!=0) fprintf(stderr, "Error en gai:%s",gai_strerror(e));

    int sd = socket(result->ai_family,result->ai_socktype,0);
    //**
    connect(sd, result->ai_addr, result->ai_addrlen);
    
    while(1){
        char buf[256];
        int m = read(STDIN_FILENO, &buf, sizeof(buf));
        if(strncmp(buf,"Q\n",2) == 0) break;

        ssize_t n = send(sd,buf,m,0);
        char msg[256];
        recv(sd, msg, n, 0);
        msg[n] = '\0';
        printf("%s",msg);
    }

    freeaddrinfo(result);
    close(sd);

    return 0;

}