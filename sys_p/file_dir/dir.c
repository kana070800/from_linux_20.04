#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define PRINT_EER_EXIT(_msg) {perror(_msg); exit(1);}  //macro func

int main(void)
{
	if (mkdir("system", 0755) == -1)
		PRINT_EER_EXIT("system");
	if (mkdir("programming", 0755) == -1)
		PRINT_EER_EXIT("programming");
	if (rename("system", "systemprogramming") == -1)
		PRINT_EER_EXIT("systemprogramming");
	if (rmdir("programming") == -1)
		PRINT_EER_EXIT("programming");

	return 0;
}
