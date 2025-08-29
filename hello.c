#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    pid = fork();  // unix 시스템 콜?
    printf("hello wsl\n");

    return 0;
}