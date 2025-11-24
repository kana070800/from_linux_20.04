#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <string.h>

#define COFFEE 1
#define CAKE 2
int totalOrder[2];

void salesCheck(int _sig){
	printf("\n[Total orders of today!]\n");
	printf("Coffee : %d, Cake : %d\n", totalOrder[0], totalOrder[1]);
	alarm(5);
}

int main(void){
	char buf[32];
	int order = 0;
	memset(totalOrder, 0, sizeof(int)*2);
	signal(SIGALRM, salesCheck);
	signal(SIGTERM, salesCheck);

	alarm(5);
	while (1){
		printf("Enter order (1 : coffee, 2 : cake) : ");
		//scanf("%d", &order);
		fgets(buf, sizeof(buf), stdin);

		sscanf(buf, "%d", &order);
		if (order == 1 || order == 2)
			totalOrder[order-1]++;
		else{
			printf("invaild order\n");
		}
	}

}
