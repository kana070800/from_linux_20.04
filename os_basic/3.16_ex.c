#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#define SIZE 5
int nums[SIZE] = {0,1,2,3,4};

int main()
{

    pid_t pid;
    int i ;
    pid = fork();

    if (pid == 0)   //child process
    {
        for(i=0;i < SIZE;i++)
        {
            nums[i] *= i;
            printf("Child: %d \n", nums[i]);
        }
    }

    if (pid > 0)   //parent process
    {
        wait(NULL);
        for(i=0;i < SIZE;i++)
        {
            printf("parent: %d \n", nums[i]);
        }
    }

    return 0;
}