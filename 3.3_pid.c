#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    
    pid = fork();    //fork a child process, 복제 >> 자식은 fork이후 실행

    printf("%d\n", pid);
    
    if (pid < 0){   //error occured
        fpirntf(stderr, "Fork Failed");
        return 1;
    }
    else if (pid == 0){  //child process  >>  자식프로세스의 내용 변경 > ls
        execlp("/bin/ls", "ls", NULL); // 이 뒤의 코드는 실행되지 않고
    }       //현재 프로세스를 bin/ls 로 교체(ls 명령 실행) >> 현재 디랙터리 내용이 표준출력으로 실행
    else {  //parent process
        wait(NULL);  //부모 프로세스가 자식 프로세스가 끝날 때까지 기다리는 시스템 호출
        printf("Child complete");
    }

    return 0;
}

/*exec 계열 함수는 새로운 프로그램을 현재 프로세스 공간에 로드하고, 기존 코드를 완전히 덮어씁니다.

호출에 성공하면 execlp 뒤에 있는 코드는 절대 실행되지 않습니다(프로세스가 교체되므로).

호출에 실패하면 -1을 반환하고, errno를 설정합니다.*/