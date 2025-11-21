#include <unistd.h>
#include <stdio.h>

int main(void)
{
	char *cwd;
	char wd[BUFSIZ];

	cwd = getcwd(NULL, BUFSIZ);
	printf("1.current directory : %s\n", cwd);

	chdir("./systemprogramming");

	getcwd(wd, BUFSIZ);
	printf("2.current directory : %s\n", wd);

	return 0;
}
