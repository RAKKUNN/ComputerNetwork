#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main()
{
    int serv_sock;
    int clnt_sock;

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;

    serv_sock=socket(PF_INET, SOCK_STREAM, 0);
    
    memset(&serv_addr, 0, sizeof(serv_addr)); // 초기화
    serv_addr.sin_family=AF_INET; // 주소 체계
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY); // 실제 주소
    serv_addr.sin_port=htons(atoi("8080")); // 포트 번호
    
    // 주소 할당(바인딩)
    bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr));

    // 연결 요청 가능한 상태 = 대기 상태
    listen(serv_sock, 5);
    
    // 연결된 친구의 정보를 저장 - 보낼 때 씀, 받을 때는 serv_sock
    clnt_addr_size = sizeof(clnt_addr);
    clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
    
    char msg[] = "202002546 임우진입니다\n"; // size : 30UL

    // \n도 포함된 길이이기에 주의해야 함
    // 뭔가 적어서 보내겠다!(클라 소켓, 메시지가 저장된 주소 값, 크기)
    write(clnt_sock, msg, sizeof(msg));
    
    // 소켓 종료 (클라 먼저 닫기)
    // 실패 - 이미 죽어있는 경우 -1이 나옴. 오류 처리 보통 안 함
    close(clnt_sock);
    close(serv_sock);
    
    return 0;
}