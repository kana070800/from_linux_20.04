#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
        FILE *fp;
        int fd, n;
        char str[BUFSIZ];

        fp = fopen("hello.txt", "r"); //high level open, <stdio>
        if (fp == NULL) {
                perror("fopen");
                exit(1);
        }

        fd = fileno(fp);  //change to low level, <system call>

        n = read(fd, str, BUFSIZ); //read
	str[n] = '\0';
        printf("Read : %s\n", str);

        fclose(fp);

        return 0;
}
