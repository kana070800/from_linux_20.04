#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct mymsgbuf {
	long mtype;
	char mtest[80];
};

int main(void){
	key_t key;
	int msgid;
	struct mymsgbuf mesg;
	
}
