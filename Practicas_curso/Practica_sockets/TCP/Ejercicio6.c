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

//SERVIDOR ECHO PARA EJERCICIOS 6 Y 7

int main(int argc, char* argv[]) {

    struct addrinfo hints;
    struct addrinfo *result;

    memset(&hints, 0, sizeof(struct addrinfo));
    
    hints.ai_flags    = 0;
    hints.ai_family   = AF_UNSPEC;   // IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM;

    int rc = getaddrinfo(argv[1], argv[2], &hints, &result);

    int sd = socket(result->ai_family, result->ai_socktype, 0);

    bind(sd, (struct sockaddr *) result->ai_addr, result->ai_addrlen);

    listen(sd, 6);

    while (1) {

        char buf[256];
        char msg[256];

        struct sockaddr_storage peer_addr;
        socklen_t peer_addrlen = sizeof(struct sockaddr_storage);

        char host[NI_MAXHOST];
        char serv[NI_MAXSERV];

        int clisd = accept(sd, (struct sockaddr *) &peer_addr, &peer_addrlen);
        
        getnameinfo((struct sockaddr *) &peer_addr, peer_addrlen, host, NI_MAXHOST,
            serv, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV);
        
        ssize_t c;

        while(c = recv(clisd, buf, 256, 0)) {
            send(clisd, buf, c, 0);
        }

        close(clisd);
    }

    close(sd);
    freeaddrinfo(result);

    return 0;
}