과제 1. 오류 처리
    오류가 발생할 수 있는 부분 - error_handling으로 처리
    write와 close, memset 는 처리하지 않음

추가 코드
    setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse))
    껐켰 반복시 바인드 살려둠 -> 오류 발생 -> 오류 막기 위한 함수임.
    int reuse = 1; 추가하면 됨

과제 2. 데이터 재전송
    read와 write를 추가해서 구현
    함수를 더 만들던 뭐하든 상관 없음