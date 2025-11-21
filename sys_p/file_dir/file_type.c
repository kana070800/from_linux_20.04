#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int main(void) {
	struct stat buf;
	int kind;

	stat("file_type.c", &buf);

	printf("Mode = %o (Hexa: %x)\n", (unsigned int)buf.st_mode, (unsigned int)buf.st_mode);
	
	kind = buf.st_mode & S_IFMT; //buf.st_mode (AND) (1111 000 000 000)
	printf("Kind = %x\n", kind);
	
	switch (kind){
		case S_IFIFO:
			printf("file_type.c : FIFO\n"); break;
		case S_IFDIR:
			printf("file_type.c : Directory\n"); break;
		case S_IFREG:
			printf("file_type.c : Regular File\n"); break;
	}
	// use macro function
	if(S_ISFIFO(buf.st_mode)) printf("file_type.c : FIFO\n");
	if(S_ISDIR(buf.st_mode)) printf("file_type.c : directory\n");
	if(S_ISREG(buf.st_mode)) printf("file_type.c : Regular\n");

	return 0;
}
