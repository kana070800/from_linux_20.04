#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>

#define PRINT_EER_EXIT(_msg) {perror(_msg); exit(1);}

int main(void){
	DIR *dp;
	struct dirent *dent;

	int temp = 0;
	long ret = 0;
	if ((dp = opendir(".")) == NULL)
		PRINT_EER_EXIT("OPENDIR");

	printf("** Directory content **\n");
	printf("Start Offset : %ld\n", telldir(dp));
	while ((dent = readdir(dp)))
	{
		printf("Read : %s  ", dent->d_name);
		printf("Cur Offset : %ld\n", telldir(dp));
		temp += 1;

		if (temp == 4)
			ret = telldir(dp);	
	}

	printf("**directory pointer rewind**\n");
	rewinddir(dp);
	printf("Cur Offset : %ld\n", telldir(dp));

	printf("**Move directory pointer**\n");
	seekdir(dp, ret);
	printf("Cur Offset : %ld\n", telldir(dp));

	dent = readdir(dp);
	printf("Read %s ", dent->d_name);
	printf("Next Offset : %ld\n", telldir(dp));

	closedir(dp);
	return 0;
}
