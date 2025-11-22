#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int main(void) {
	struct stat buf;

	stat("file_info.c", &buf);
	
	printf("Inode = %d\n", (int)buf.st_ino);
	printf("Mode = %o\n", (unsigned int)buf.st_mode);
	printf("Nlink = %o\n", (unsigned int)buf.st_nlink);
	printf("UID = %d\n", (int)buf.st_uid);

	return 0;
}
