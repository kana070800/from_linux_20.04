#include <unistd.h>
#include <stdio.h>

int main(void){
	printf("Clock tick : %ld\n", sysconf(_SC_CLK_TCK));
	printf("Max open file : %ld\n", sysconf(_SC_OPEN_MAX));
	printf("Max login name length : %ld\n", sysconf(_SC_LOGIN_NAME_MAX));

	return 0;

}
