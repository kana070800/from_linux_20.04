#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <wait.h>

pid_t pid_f;
int us = 0;

union semun {
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};

int initsem(key_t semkey){
	union semun semunarg;
	int status = 0, semid;

	semid = semget(semkey,1,IPC_CREAT | IPC_EXCL | 0600);
	if (semid == -1){
		if (errno == EEXIST)
			semid = semget(semkey, 1, 0);}
	else {
		semunarg.val = 1;
		status = semctl(semid, 0, SETVAL, semunarg);
	}

	if (semid == -1 || status == -1) {perror("initsem"); return -1;}

	return semid;
}

int semlock(int semid){
	struct sembuf buf;

	buf.sem_num = 0;
	buf.sem_op = -1; //P
	buf.sem_flg = SEM_UNDO;
	if (semop(semid, &buf,1) == -1){
		perror("semlock failed"); exit(1);
	}
	return 0;
}

int semunlock(int semid){
	struct sembuf buf;

	buf.sem_num = 0;
	buf.sem_op = 1; //V
	buf.sem_flg = SEM_UNDO;
	if (semop(semid, &buf, 1) == -1) {
		perror("semunlock failed"); exit(1);
	}
	return 0;
}

void semhandle(){
	int semid;
	pid_t pid =getpid();

	if ((semid = initsem(1))<0)  exit(1);

	semlock(semid);
	printf("Lock : Process %d\n", (int)pid);
	printf("***Lock Mode : Critical Section\n");
	sleep(1);
	printf("Unlock : Process %d\n", (int)pid);
	semunlock(semid);
	exit(0);
}

int main(void){
	int a;
	int st;
	pid_t w, ww;
	for (a = 0; a < 3; a++){
		if ((w = fork()) == 0) //child
			semhandle();
		if (a == 2)
			ww = w;
	}
/*	for (int i=0; i<3; i++)
		wait(NULL);*/
	waitpid(ww, &st, 0);
	printf("DONE\n");
	return 0;
}


