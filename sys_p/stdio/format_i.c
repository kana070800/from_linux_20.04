#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int ID;
	char name[8];
	float score;
} Student;

int fileOpen(FILE** _fp, char* _fileName, char* _mode){
	*_fp = fopen(_fileName, _mode);
	if (!*_fp){
		printf("Fail to open - %s\n", _fileName);
		return -1;
	}
	return 0;
}

int main(void){
	Student info = {0};
	char* fileName = "studentlist.txt";
	FILE* fp = NULL;

	if (fileOpen(&fp, fileName, "a") < 0) 
		exit(1);

	while(1) {
		printf("Enter ID Name Score (Exit = -1): ");
		scanf("%d", &info.ID);
		if (info.ID < 0)
			break;
		scanf("%s %f", (char *)&info.name, &info.score);
		getchar();         //remove '\n' in buffer
		fprintf(fp, "%d %s %.1f\n", info.ID, info.name, info.score);
	}
	fclose(fp);

}
