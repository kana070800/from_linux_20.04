#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
int main(void){
	pid_t pid;
	int st;

	switch (pid = fork()){
		case -1 : //fork failed
			perror("fork");
			exit(1);
			break;
		case 0 : //child
			printf("--> Child Process\n");
			if (execlp("ls", "ls", "-a", (char *)NULL) == -1){
				perror("execlp");
				exit(1);
			}
			exit(0);
			break;
		default : //parent
			printf("--> Parent process -My PID:%d\n", (int)getpid());
			wait(&st);
			break;
	}
	return 0;
}
