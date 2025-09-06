#include <stdio.h>
#include <string.h>

int main(void) {
	char str[] = "now # is the time # to start preparing ### for the exam### for the exam#";
	char delim[] = "#";
	char *token;               //한글 

	token = strtok( str, delim );

       	while ( token != NULL ) {
		printf( "next token is: %s:%ld\n", token, strlen(token));
		token = strtok( NULL, delim );
	}
	return 0;
}
