#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

//CLIENTE UDP: getaddrinfo->socket->sendto->recvfrom->close

int main(int argc, char* argv[]){
    struct addrinfo hints;
    struct addrinfo *result;

    memset(&hints,0,sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;

    int e = getaddrinfo(argv[1],argv[2],&hints,&result);
    if(e!=0) fprintf(stderr, "Error en gai:%s",gai_strerror(e));

    int sd = socket(result->ai_family,result->ai_socktype,0);

    sendto(sd,argv[3],strlen(argv[3]),0,result->ai_addr,result->ai_addrlen);
    if(strcmp(argv[3],"q")!=0) {
        char buf[256];
        ssize_t nread = recvfrom(sd,&buf,sizeof(buf),0,NULL,0);
        buf[nread] = '\0';
        printf("%s", buf);
    }
    printf("Saliendo...\n");
    freeaddrinfo(result);
    close(sd);

    return 0;
}