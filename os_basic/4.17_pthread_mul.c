#include <stdio.h>
 #include <unistd.h>
 #include <wait.h>
 #include <pthread.h>


 void * runner(void *param);

 int main(int argc, char *argv[])
 {
    pid_t pid;
    pthread_t tid;

    printf("A=%d\n",getpid());

    pid = fork();
    if (pid > 0) { // parent process
        wait(NULL);
        printf("B = %d\n", pid); // LINE P
    }
    if (pid == 0) { // child process
        pid = fork();
        if (pid > 0)
        { 
            wait(NULL);
            printf("C = %d\n",pid);
        }
        pthread_create(&tid, NULL, runner, NULL);
    }
    pid = fork();
    if (pid > 0)
    {
        wait(NULL);
        printf("D = %d\n",pid);
    }
 }

  void *runner(void *param)
 {
    printf("i'm a thread!\n");
    pthread_exit(0);
 }