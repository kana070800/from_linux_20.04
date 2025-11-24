#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>

int main(void){
	
	int targetPID = 0;

	while(1){
		printf("Enter PID to kill : ");
		scanf("%d", &targetPID);
		if (kill(targetPID, SIGKILL) == -1){
			switch (errno){
			case EPERM:
				printf("not enough permission!\n");
				break;
			case ESRCH:
				printf("cannot find the process %d\n", targetPID);
				break;
			}
		}
		else {printf("Bang! -> %d\n", targetPID);}
	}
	return 0;
}
