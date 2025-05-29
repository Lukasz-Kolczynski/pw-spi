#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

int main(int argc, char *argv[])
{
    if (getuid() == 0) 
    {
        printf("Nie uruchamiaj jako root\n");
        return 1;
    }

    int port = (argc > 1) ? atoi(argv[1]) : 8080;

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in addr;
    memset((char*)&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port);

    bind(server_fd, (struct sockaddr*)&addr, sizeof(addr));
    listen(server_fd, 5);

    printf("Serwer działa na porcie %d...\n", port);

    while(1)
    {
        int client_fd = accept(server_fd, NULL, NULL);

        char buf[1000];
        recv(client_fd, buf, sizeof(buf), 0);

        FILE *fp = fopen("/proc/uptime", "r");
        float uptime;
        fscanf (fp, "%f", &uptime);
        fclose(fp);

        char body[100];
        sprintf(body, "Uptime: %.2f seconds\n", uptime);

        char header[300];
        sprintf(header,
            "HTTP/1.0 200 OK\r\n"
            "Content-Type: text/plain\r\n"
            "Content-Length: %ld\r\n"
            "Connection: close\r\n\r\n",
            strlen(body));

        send(client_fd, header, strlen(header), 0);
        send(client_fd, body, strlen(body), 0);

        shutdown(client_fd, SHUT_WR);
        close(client_fd);
    }

    close(server_fd);
    return 0;
    
}

// gcc server.c -o server
// ./server 8080