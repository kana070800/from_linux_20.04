#include <stdio.h>
 #include <pthread.h>
 #include <semaphore.h>
 #define true 1
 #define false 0
 int sum = 0;
 sem_t sem;

 pthread_mutex_t mutex;

  void *counter(void *param)
 {
    int k;
    for (k = 0; k < 100000; k++) {
        /* entry section */
        sem_wait(&sem);

         /* critical section */
        sum++;
        /* exit section */
        sem_post(&sem);
        /* remainder section */
    }
    pthread_exit(0);
 }

                        //1이 아닌 값으로 초기화 시 에러나는게 정상, race condition >> 여러 값들이 동시 접근가능한 자원일 때 유효
  int main()
 {
    pthread_t tid[5];
    sem_init(&sem, 0,1);
    for (int i = 0; i < 5;i++)
        pthread_create(&tid[i], NULL, counter, NULL);
    for (int i = 0; i < 5;i++)
        pthread_join(tid[i], NULL);
    printf("sum = %d\n", sum);
 }