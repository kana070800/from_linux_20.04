#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INIT_CAPACITY 3 // 배열 재할당을 위한 작은 값 
#define BUFFER_SIZE 20

char ** names;  // char pointer array 재할당을 위해 크기지정 x
char ** numbers;

int capacity = INIT_CAPACITY;
int n = 0;                  //numbers of people in directory

char delim[] = " ";



void init_directory();
int read_line(char *, int);
void process_command();
void load1(char* );
void add(char * , char * );
void reallocate();
void save(char *);
int search(char *);
void find(char *);
void status();
void remove1(char *);




int main(){
	init_directory();
	process_command();

	return 0;
}





void init_directory(){
	names = (char **)malloc(INIT_CAPACITY * sizeof(char *));
	numbers = (char **)malloc(INIT_CAPACITY * sizeof(char *));
}

int read_line(char str[], int limit){ //array size input
	int ch, i = 0;

	while ((ch = getchar()) != '\n')
		if (i < limit - 1)
			str[i++] = ch; //줄바꿈 이전까지 읺기 
	str[i] = '\0';  //마지막에 null character 추가 
	return i;
}

void process_command() {
	char command_line[BUFFER_SIZE];
	char *command, *argument1, *argument2;
	
	while(1) {
		printf("$ ");

		if (read_line(command_line, BUFFER_SIZE)<=0)
			continue;

		command = strtok(command_line, delim);
		if (command == NULL) continue;

		if (strcmp(command, "read") == 0){
			argument1 = strtok(NULL, delim);
			if (argument1 == NULL){
				printf("file name required\n");
				continue;
			}
			load1(argument1);
		}

		else if (strcmp(command, "add") == 0){
			argument1 = strtok(NULL, delim);
			argument2 = strtok(NULL, delim);
			
			if (argument1 == NULL || argument2 == NULL) {
				printf("invalid arguments\n");
				continue;
			}
			add(argument1, argument2);

			printf("%s was added successfully\n", argument1);
		}
		
		else if (strcmp(command, "find") == 0){
			argument1 = strtok(NULL, delim);
			if (argument1 == NULL) {
				printf("invalid arguments\n");
				continue;
			}
			find(argument1);
		}
		
		else if (strcmp(command, "status")==0)
			status();

		else if (strcmp(command, "delete") == 0){
			argument1 = strtok(NULL, delim);
			if (argument1 == NULL) {
				printf("invalid argument\n");
				continue;
			}	
			remove1(argument1);
		}

		else if (strcmp(command, "save") == 0) {
			argument1 = strtok(NULL, delim);
			argument2 = strtok(NULL, delim);
			
			if (argument1 == NULL || argument2 == NULL || strcmp("as", argument1) != 0) {
				printf("invalid command format\n");
				continue;
			}

			save(argument2);
		}
	
		else if (strcmp(command, "exit") == 0)
			break;
	}

}



void load1(char* fileName) {
	char buf1[BUFFER_SIZE];
	char buf2[BUFFER_SIZE];

	FILE * fp = fopen(fileName, "r"); //file open
	if (fp==NULL){
		printf("open failed\n");
		return;
	}

	while ((fscanf(fp, "%s", buf1) != EOF)) {  //read from file one string
		fscanf(fp, "%s", buf2);            // store next string
		add(buf1, buf2);
	}
	fclose(fp);
}

void add(char * name, char * number) {
	
	if (n >= capacity)
		reallocate();

	int i = n-1;

	while (i >= 0 && strcmp(names[i], name) > 0){
		names[i+1] = names[i];
		numbers[i+1] = numbers[i];
		i--;
	}

	names[i+1] = strdup(name);
	numbers[i+1] = strdup(number);
	n++;
}

void reallocate() {
	int i;

	capacity *= 2;
	char **tmp1 = (char **)malloc(capacity * sizeof(char *));
	char **tmp2 = (char **)malloc(capacity * sizeof(char *));
	
	for (i = 0 ; i < n ; i++) {
		tmp1[i] = names[i];
		tmp2[i] = numbers[i];
	}

	free(names);
	free(numbers);

	names = tmp1;
	numbers = tmp2;
}

void save(char * fileName){
	int i;

	FILE * fp = fopen(fileName, "w");  //no exist then creat
	if (fp == NULL){
		printf("open failed\n");
		return;
	}

	for (i=0 ; i < n ; i++){
		fprintf(fp, "%s %s\n", names[i], numbers[i]);
	}
	fclose(fp);
}

int search(char *name){
	int i;
	for (i = 0 ; i<n ; i++){
		if (strcmp(name, names[i])==0)
			return i;
	}
	return -1;
}

void find(char *name){
	int index = search(name);

	if (index == -1)
		printf("No person named '%s' exist\n", name);
	else
		printf("%s\n", numbers[index]);
}

void status() {
	int i;
	for (i = 0 ; i<n ; i++)
		printf("%s	%s\n", names[i], numbers[i]);
	printf("Total %d persons.\n",n);
}

void remove1(char *name) {
	int index = search(name);  //if not exist return -1
	if (index == -1){
		printf("No person named '%s' exist\n",name);
		return;
	}
	int j = index;
	for (; j<n-1 ; j++){  //easy to mistake 
		names[j] = names[j+1];
		numbers[j] = numbers[j+1];
	}

	n--;
	printf("No person named '%s' exists.\n", name);
}



