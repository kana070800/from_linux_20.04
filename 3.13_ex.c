#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{

    pid_t pid, pid1;

    pid = fork();

    if (pid == 0)   //child process
    {
        execlp("/bin/ls", "ls", NULL);

        printf("");
    }

    if (pid > 0)   //parent process
    {
        wait(NULL);
        printf("child end\n");
    }

    return 0;
}