 #include <stdio.h>
 #include <stdlib.h>
 #include <pthread.h>

 /* the data shared by the threads */
 int sum;
 /* thread call this function */
 void * runner(void *param);    //thread 동작

 int main(int argc, char *argv[])   //argv[0] = 실행경로, [1] = 입력 문자열
 {
    pthread_t tid;      //thread id 
 // thread identifier
    pthread_attr_t attr;    //thread 속성
 // thread attributes
    pthread_attr_init(&attr);   //기본속성으로 초기화
    pthread_create(&tid, &attr, runner, argv[1]);   //스레드 생성, 명령줄 인자의 첫 번째 값(문자열)을 runner로 전달.
    pthread_join(tid, NULL);

    printf("sum = %d\n", sum);
 }
 
 void *runner(void *param)
 {
    int i, upper = atoi(param); //문자열을 int로 변환.
    sum = 0;
    for (i = 1; i <= upper; i++)
    sum += i;
    pthread_exit(0);
 }

 //        ./a.out 숫자