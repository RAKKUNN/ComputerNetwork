#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
void error_handling(char * message);
int main(int argc, char* argv[])
{
    int serv_sock;
    int clnt_sock;
    int reuse = 1;
    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
    if(serv_sock == -1) {
        error_handling("setsockopt error");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_addr.sin_port=htons(atoi("8080"));

    bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr));
    if(serv_sock == -1) {
        error_handling("bind error");
    }

    listen(serv_sock, 5);
    if(serv_sock == -1) {
        error_handling("listen error");
    }

    clnt_addr_size = sizeof(clnt_addr);
    clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
    if(serv_sock == -1) {
        error_handling("accept error");
    }
    char msg[] = "Hello I'm WoojinIm!\n";
    write(clnt_sock, msg, sizeof(msg));

    char buffer[1024] = {0x00, };
    int reader = read(clnt_sock, buffer, sizeof(buffer)-1);
    printf("Message from Client: %s", buffer);

    close(clnt_sock);
    close(serv_sock);

    return 0;
}

void error_handling(char * message)
{
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}