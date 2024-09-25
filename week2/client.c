#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main()
{
    int clnt_sock;

    struct sockaddr_in serv_addr;

    char message[1024] = {0x00, };

    clnt_sock = socket(PF_INET, SOCK_STREAM, 0);

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(atoi("8080"));
    
    // 연결 요청 (클라 소켓, 서버 정보)
    connect(clnt_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    
    // 데이터 수신 (내가 최대 몇글자까지 읽을지(1023))
    // -1 : 버퍼 오버플로우 위험 막기용
    // return : 수신한 바이트 수 != 1023 or -1
    read(clnt_sock, message, sizeof(message)-1);
    printf("Message from server : %s\n", message);

    close(clnt_sock);
    return 0;
}