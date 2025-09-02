#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CAPACITY 100 
#define BUFFER_LENGTH 100

typedef struct person {
	char * name;
	char * number;
	char * email;
	char * group;
	
} Person;

Person directory[CAPACITY];

int n = 0;                  //numbers of people in directory


//void init_directory();
int read_line(FILE *, char *,int);
//void process_command();
void load1(char* );
void add(char * , char * , char *, char *);
//void reallocate();
void save(char *);
void handle_add(char *);
int compose_name(char *, int);
int search(char *);
void find(char *);
void status();
void remove1(char *);
void print_person(Person);




int main(){
 	char command_line[BUFFER_LENGTH];
        char *command, *argument;
	char name_str[BUFFER_LENGTH];

        while(1) {
                printf("$ ");

                if (read_line(stdin, command_line,BUFFER_LENGTH)<=0)
                        continue;   //비정상 입력(바로 엔터)

                command = strtok(command_line, " ");  //정상입력 >> 명령어 구분

                //if (command == NULL) continue;

                if (strcmp(command, "read") == 0){    //파일 읽기
                        argument = strtok(NULL, " ");
                        if (argument == NULL){
                                printf("file name required\n"); //파일이름 지정x
                                continue;
                        }
                        load1(argument);
                }

                else if (strcmp(command, "add") == 0){

                        if (compose_name(name_str, BUFFER_LENGTH) <= 0) {
				printf("name required\n");
				continue;
			}
			handle_add(name_str);
		}
		else if (strcmp(command, "find") == 0){

                        if (compose_name(name_str, BUFFER_LENGTH) <= 0) {
                                printf("name required\n");
                                continue;
                        }
                        find(name_str);
                }
		else if (strcmp(command, "status") == 0){
			status();}

		else if (strcmp(command, "delete") == 0){

                        if (compose_name(name_str, BUFFER_LENGTH) <= 0) {
                                printf("lnvaild argument\n");
                                continue;
                        }
                        remove(name_str);
                }
		else if (strcmp(command, "save") == 0){
			argument = strtok(NULL, " ");
                        if (strcmp(argument, "as") != 0) {
                                printf("invaild argument\n");
                                continue;
                        }
			argument = strtok(NULL, " ");
                        if (argument == NULL) {
                                printf("invaild argument\n");
                                continue;
                        }
                        save(argument);
                }
		else if (strcmp(command, "exit") == 0)
			break;
	}
	return 0;
}




/*
void init_directory(){
	names = (char **)malloc(INIT_CAPACITY * sizeof(char *));
	numbers = (char **)malloc(INIT_CAPACITY * sizeof(char *));
}
*/
int read_line(FILE * fp, char str[], int n){ //add read file  >> keyboard input >> std in
	int ch, i = 0;

	while ((ch = fgetc(fp)) != '\n' && ch != EOF) // EOF == end of file condition
		if (i < n)
			str[i++] = ch; //줄바꿈 이전까지 읺기 
	str[i] = '\0';  //마지막에 null character 추가 	return i;

	return i;
}


void load1(char* fileName) {
	char buf[BUFFER_LENGTH];
	char *name, *number, *email, *group;

	FILE * fp = fopen(fileName, "r"); //file open
	if (fp==NULL){
		printf("open failed\n");
		return;
	}

	while (1) {  
		if (read_line(fp, buf, BUFFER_LENGTH) <= 0) //read from file one line
			break;
		name = strtok(buf, "#");
		number = strtok(NULL, "#");
		email = strtok(NULL, "#");
		group = strtok(NULL, "#");
		add(name, number, email, group);
	}
	fclose(fp);
}

void add(char * name, char * number, char * email, char * group) {
	int i = n-1;

	while (i >= 0 && strcmp(directory[i].name, name) > 0){
		directory[i+1] = directory[i]; // 알파벳 순 정렬
		i--;
	}

	directory[i+1].name = strdup(name);
	directory[i+1].number = strdup(number);
	directory[i+1].email = strdup(email);    //복제하여 저장
	directory[i+1].group = strdup(group);

	n++;
}
/*
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
*/

int compose_name(char str[], int limit){  //이름을 입력할 때 앞뒤, 사이의 불필요한 공백 제거
	char * ptr;
	int length = 0;

	ptr = strtok(NULL, " ");  //두번째 토큰
	if (ptr == NULL)
		return 0; //이름 없음 >> 필요메시지 출력후 continue

	strcpy(str, ptr);
	length += strlen(ptr);

	while ((ptr = strtok(NULL, " ")) != NULL) { //문장 끝까지 다음 토큰 읽기
		if (length + strlen(ptr) + 1 < limit) { // 버퍼 오버플로우 방지
			str[length++] = ' ';
			str[length] = '\0';   //name\0 >> name \0
			strcat(str, ptr);     // name name1
			length += strlen(ptr);
		}
	}
	return length;
}

void handle_add(char * name){
	char number[BUFFER_LENGTH], email[BUFFER_LENGTH], group[BUFFER_LENGTH];
	char empty[] = " ";

	printf("  phone : ");
	read_line(stdin, number, BUFFER_LENGTH);

	printf("  email : ");
	read_line(stdin, email, BUFFER_LENGTH);

	printf("  group : ");
	read_line(stdin, group, BUFFER_LENGTH);

	add(name, (char *)(strlen(number) > 0 ? number : empty),(char *)(strlen(email) > 0 ? email : empty),(char *)(strlen(group) > 0 ? group : empty)); //입력이 없으면(바로 엔터) 공백문자 하나로 대체한다 
}

void save(char * fileName){
	int i;

	FILE * fp = fopen(fileName, "w");  //no exist then creat
	if (fp == NULL){
		printf("open failed\n");
		return;
	}

	for (i=0 ; i < n ; i++){
		fprintf(fp, "%s#", directory[i].name);  //이미 디렉토리에 저장시 이름은 handle_add에서 하나의 공백으로 처리
		fprintf(fp, "%s#", directory[i].number);
		fprintf(fp, "%s#", directory[i].email);
		fprintf(fp, "%s#\n", directory[i].group);
	}
	fclose(fp);
}

int search(char *name){
	int i;
	for (i = 0 ; i<n ; i++){
		if (strcmp(name, directory[i].name)==0)
			return i;
	}
	return -1;
}

void print_person(Person p) {
	printf("%s\n", p.name);
	printf("  %s\n", p.number);
	printf("  %s\n", p.email);
	printf("  %s\n", p.group);
}

void find(char *name){
	int index = search(name);

	if (index == -1)
		printf("No person named '%s' exist\n", name);
	else
		print_person(directory[index]);
}

void status() {
	int i;
	for (i = 0 ; i<n ; i++)
		print_person(directory[i]);
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
		directory[j] = directory[j+1]; // 삭제하고 다시 당겨옴
	}

	n--;
	printf("No person named '%s' exists.\n", name);
}



