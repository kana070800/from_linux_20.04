#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
	FILE *fp;
	int fd;
	char str[BUFSIZ];

	fd = open("hello.txt", O_RDONLY); //low level open, <system call>
	if (fd == -1) {
		perror("open");
		exit(1);
	}

	fp = fdopen(fd, "r");  //change to high level, <stdio control>

	fgets(str, BUFSIZ, fp); //read
	printf("Read : %s\n", str);

	fclose(fp);

	return 0;
}
