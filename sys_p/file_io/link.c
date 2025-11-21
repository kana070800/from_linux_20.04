#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

int main(void){
	struct stat buf;

	stat("linux.txt", &buf);
	printf("Before link Count = %d\n", (int)buf.st_nlink);

	link("linux.txt", "linux.ln");  //make other hard link

	stat("linux.txt", &buf);
	printf("After link Count =%d\n", (int)buf.st_nlink);

	
	symlink("linux.txt", "linux.sym");  //make symbolic link

	return 0;
}         // test use >>> ls -il linux.*
