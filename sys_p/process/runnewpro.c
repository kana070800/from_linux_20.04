#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void){

	printf("--> before exec function\n");

	if (execlp("ls", "ls", "-a", (char *)NULL) == -1) {
		perror("execlp");
		exit(1);
	}

	printf("--> After exec function\n"); //not execution

	return 0;
}
