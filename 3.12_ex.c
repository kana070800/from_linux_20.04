#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int value = 5;

int main()
{
/*
    pid_t pid;

    for (int i = 0;i<3;i++) 
    {
        pid = fork();
        value = value + 5;
        printf("%d  %d\n", pid, value);
    }
*/


    pid_t pid, pid1;

    pid = fork();

    if (pid == 0)   //child process
    {
        pid1 = getpid();
        printf("child: pid = %d\n", pid);
        printf("child: pid1 = %d\n", pid1);
    }

    if (pid > 0)   //parent process
    {
        pid1 = getpid();
        printf("parent: pid = %d\n", pid);
        printf("parent: pid1 = %d\n", pid1);
        wait(NULL);
    }



    return 0;
}