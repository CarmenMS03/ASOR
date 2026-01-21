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

    bind(sd, (struct sockaddr *) result->ai_addr, result->ai_addrlen);

    for (int i = 0; i < 10; i++) {
        pid_t pid = fork();

        if (pid == 0) { // Hijo

            // while (1) {

                char buf[256];
                char msg[256];

                struct sockaddr_storage peer_addr;
                socklen_t peer_addrlen = sizeof(struct sockaddr_storage);

                char host[NI_MAXHOST];
                char serv[NI_MAXSERV];
                
                ssize_t read = recvfrom(sd, buf, 255, 0, (struct sockaddr *) &peer_addr, &peer_addrlen);
                buf[read] = '\0';

                getnameinfo((struct sockaddr *) &peer_addr, peer_addrlen, host, NI_MAXHOST,
                    serv, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV);

                pid_t pid = getpid();
                printf("PID: %d. Received %ld bytes from %s:%s\n", pid, (long)read, host, serv);
                printf("Msg: %s\n", buf);

                if (strcmp(buf, "t") == 0) { // Para nc hay que poner t\n porque lo manda solo y para el ejercicio 3 no porque no lo mandas
                    // Hora
                    time_t now = time(NULL);
                    struct tm *t = localtime(&now);
                    strftime(msg, sizeof(msg), "%H:%M:%S\n", t);
                    sendto(sd, msg, strlen(msg), 0,
                            (struct sockaddr *)&peer_addr, peer_addrlen);
                }

                else if (strcmp(buf, "d") == 0) {
                    // Fecha
                    time_t now = time(NULL);
                    struct tm *t = localtime(&now);
                    strftime(msg, sizeof(msg), "%Y-%m-%d\n", t);
                    sendto(sd, msg, strlen(msg), 0,
                            (struct sockaddr *)&peer_addr, peer_addrlen);
                }

                else if (strcmp(buf, "q") == 0) {
                    printf("Servidor finalizado.\n");
                    break;
                }

            // }
        }
    }

    printf("Padre ha terminado. GID: %d", getpgid(getpid()));
    // Guardar en una lista los pids de los hijos y en el handler los matas a todos

    freeaddrinfo(result);
    // close(sd);
    return 0;
}