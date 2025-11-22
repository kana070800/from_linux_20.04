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

	if (fileOpen(&fp, fileName, "r") < 0)
		exit(1);

	int Numstudent = 0;
	float sum = 0;

	while (!feof(fp)){
		fscanf(fp, "%d %s %f\n", &info.ID, (char *)&info.name, &info.score);
		sum += info.score;
		Numstudent++;
	}

	printf("%d students, average = %.2f\n", Numstudent, sum/Numstudent);
	fclose(fp);
}
