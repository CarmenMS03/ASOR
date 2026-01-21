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
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

// CLIENTE ECHO PARA EJERCICIO 7 y 8

int main(int argc, char* argv[]) {

    struct addrinfo hints;
    struct addrinfo *result;

    memset(&hints, 0, sizeof(struct addrinfo));
    
    hints.ai_flags    = 0;
    hints.ai_family   = AF_UNSPEC;   // IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM;

    int rc = getaddrinfo(argv[1], argv[2], &hints, &result);

    int sd = socket(result->ai_family, result->ai_socktype, 0);

    if (connect(sd, result->ai_addr, result->ai_addrlen) == -1) perror("connect");
    freeaddrinfo(result);

    struct sockaddr_storage peer_addr;
    socklen_t peer_addrlen = sizeof(struct sockaddr_storage);

    char buf[256];

    read(0, buf, 256);

    while(strcmp(buf, "Q\n\0") != 0) { // El read mete un \0 por defecto
        send(sd, buf, strlen(buf), 0);
        
        ssize_t leidos = recv(sd, buf, 255, 0);
        buf[leidos] = '\0';

        printf("%s\n", buf);
        memset(buf, 0, sizeof(buf));
        read(0, buf, 256);
    }

    close(sd);

    return 0;
}