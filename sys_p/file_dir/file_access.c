#include <sys/errno.h>
#include <unistd.h>
#include <stdio.h>

extern int errno;

int main(void){
	int per;

	if (access("linux.bak", F_OK) == -1 && errno == ENOENT)
		printf("linux.bak: file not exist\n");

	per = access("file_access.c", R_OK);
	if (per == 0)
		printf("file_access.c : read permission is permitted\n");
	else if (per == -1 && errno == EACCES)
		printf("file_access.c : read permission is not permitted\n");

	return 0;
}
