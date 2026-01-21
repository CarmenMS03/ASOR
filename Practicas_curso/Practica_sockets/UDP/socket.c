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

    // Ejercicio 1

    // struct addrinfo hints;
    // struct addrinfo *res, *ptr;

    // char host[NI_MAXHOST];

    // memset(&hints, 0, sizeof(struct addrinfo));

    // hints.ai_flags     = 0;
    // hints.ai_family   = AF_UNSPEC;   // IPv4 or IPv6

    // int rc = getaddrinfo(argv[1], NULL, &hints, &res);

    // if (rc != 0) fprintf(stderr, "Error en gai: %s\n", gai_strerror(rc));

    // for (ptr = res; ptr != NULL; ptr = ptr->ai_next) {
    //     getnameinfo(ptr->ai_addr, ptr->ai_addrlen, host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
    //     printf("%s\t %d\t %d\n", host, ptr->ai_family, ptr->ai_socktype);
    // }

    // freeaddrinfo(res);

    // Ejercicio 2

    struct addrinfo hints;
    struct addrinfo *result;

    memset(&hints, 0, sizeof(struct addrinfo));
    
    hints.ai_flags    = 0;
    hints.ai_family   = AF_UNSPEC;   // IPv4 or IPv6
    hints.ai_socktype = SOCK_DGRAM;

    int rc = getaddrinfo(argv[1], argv[2], &hints, &result);

    int sd = socket(result->ai_family, result->ai_socktype, 0);

    bind(sd, (struct sockaddr *) result->ai_addr, result->ai_addrlen);

    while (1) {

        fd_set set;

        char buf[256];
        char msg[256];
        FD_ZERO(&set);
        FD_SET(sd, &set);
        FD_SET(0, &set);

        int nfds = 0;
        if(sd > 0) nfds = sd;
        else nfds = 0;

        int changes = select(nfds + 1, &set, NULL, NULL, NULL); 

        // Los conjuntos de descriptores se modifican en select para indicar cuáles están listos para cada op
        if(FD_ISSET(sd, &set)) { // La primera tubería tiene algo para leer

            struct sockaddr_storage peer_addr;
            socklen_t peer_addrlen = sizeof(struct sockaddr_storage);

            char host[NI_MAXHOST];
            char serv[NI_MAXSERV];
            
            ssize_t read = recvfrom(sd, buf, 255, 0, (struct sockaddr *) &peer_addr, &peer_addrlen);
            buf[read] = '\0';

            getnameinfo((struct sockaddr *) &peer_addr, peer_addrlen, host, NI_MAXHOST,
                serv, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV);

            printf("Received %ld bytes from %s:%s\n", (long)read, host, serv);
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
        }
        else if (FD_ISSET(0, &set)) {

            ssize_t bytes = read(0, buf, sizeof(buf) - 1);
            printf("Buffer: %s", buf);

            if(bytes != 0) { // El escritor no ha cerrado la tubería
                if (strcmp(buf, "t\n") == 0) { // Para nc hay que poner t\n porque lo manda solo y para el ejercicio 3 no porque no lo mandas
                    // Hora
                    time_t now = time(NULL);
                    struct tm *t = localtime(&now);
                    strftime(msg, sizeof(msg), "%H:%M:%S\n", t);
                    write(STDOUT_FILENO, msg, strlen(msg));
                }

                else if (strcmp(buf, "d\n") == 0) { // IMPORTANTE \N SINO NO FUNCIONA, NO ENTRA AL IF
                    // Fecha
                    time_t now = time(NULL);
                    struct tm *t = localtime(&now);
                    strftime(msg, sizeof(msg), "%Y-%m-%d\n", t);
                    write(STDOUT_FILENO, msg, strlen(msg));
                }

                else if (strcmp(buf, "q\n") == 0) {
                    printf("Servidor finalizado.\n");
                    break;
                }
            }
        }

    }

    freeaddrinfo(result);
    close(sd);

    return 0;
}