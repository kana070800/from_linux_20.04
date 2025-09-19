#include <stdio.h>
 #include <pthread.h>
 #define true 1
 #define false 0
 int sum = 0;

 pthread_mutex_t mutex;

  void *producer(void *param)
 {
    int k;
    for (k = 0; k < 100000; k++) {
        /* entry section */
        pthread_mutex_lock(&mutex);

         /* critical section */
        sum++;
        /* exit section */
        pthread_mutex_unlock(&mutex);
        /* remainder section */
    }
    pthread_exit(0);
 }

 void *consumer(void *param)
 {
    int k;
    for (k = 0; k < 100000; k++) {
        /* entry section */
        pthread_mutex_lock(&mutex);
        /* critical section */
        sum--;
        /* exit section */
        pthread_mutex_unlock(&mutex);
        /* remainder section */
    }
 pthread_exit(0);
 
}



  int main()
 {
    pthread_t tid1, tid2;
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&tid1, NULL, producer, NULL);
    pthread_create(&tid2, NULL, consumer, NULL);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    printf("sum = %d\n", sum);
 }