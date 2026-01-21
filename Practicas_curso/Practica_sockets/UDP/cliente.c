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

int main(int argc, char* argv[]) {

    struct addrinfo hints;
    struct addrinfo *result;

    memset(&hints, 0, sizeof(struct addrinfo));
    
    hints.ai_flags    = 0;
    hints.ai_family   = AF_UNSPEC;   // IPv4 or IPv6
    hints.ai_socktype = SOCK_DGRAM;

    int rc = getaddrinfo(argv[1], argv[2], &hints, &result);

    int sd = socket(result->ai_family, result->ai_socktype, 0);

    struct sockaddr_storage peer_addr;
    socklen_t peer_addrlen = sizeof(struct sockaddr_storage);

    char buf[256];
    char msg[256];
    char host[NI_MAXHOST];
    char serv[NI_MAXSERV];

    sendto(sd, argv[3], strlen(argv[3]), 0, result->ai_addr, result->ai_addrlen);
        
    ssize_t read = recvfrom(sd, buf, 255, 0, (struct sockaddr *) &peer_addr, &peer_addrlen);
    buf[read] = '\0';

    printf("Hora: %s\n", buf);


    freeaddrinfo(result);
    close(sd);

    return 0;
}