#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t empty,full;
#define buffer_size 5
int counter[buffer_size];
int in = 0 , out = 0;
pthread_mutex_t mutex;
volatile int running = 1;

void* producer(void* args){
    int pizza = 1;
    while(running){
        sem_wait(&empty); // initally all slots are empty and empty = buffer_size
        // so sem_wait decrements empty
        // If empty == 0, it blocks (waits) until another thread calls sem_post(&empty).
        pthread_mutex_lock(&mutex);
        counter[in]=pizza;
        in = (in+1)%buffer_size;
        sleep(1);
        printf("Mr. Simpson produced pizza with id %d\n",pizza);
        pizza++;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
    printf("Mr. Simpson closed the shop!!\n");
    pthread_exit(NULL);
}
void* consumer(void* args){
    while(running){
        sem_wait(&full); // full is initally 0 i.e no pizzas at start so we wait
        // if full has value say 2 we decrement and it i.e 1 pizza is eaten/consumed
        pthread_mutex_lock(&mutex);
        int pi = counter[out];
        out = (out+1)%buffer_size;
        sleep(1);
        printf("Joey consumed pizza with id %d\n",pi);
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
    printf("Joey's stomach is full!!\n");
    pthread_exit(NULL);
}

int main(){
    sem_init(&empty,0,buffer_size); // initally all empty
    sem_init(&full,0,0); // initally zero full/ no pizza at counter
    pthread_mutex_init(&mutex,NULL);

    pthread_t Simpson, Joey;

    pthread_create(&Simpson,NULL,producer,NULL);
    pthread_create(&Joey,NULL,consumer,NULL);

    printf("Press enter to close the counter : \n");
    getchar();
    running = 0;
    sem_post(&empty); // If the producer was waiting for empty, sem_post(&empty) wakes it up.
    sem_post(&full); // If the consumer was waiting for full, sem_post(&full) wakes it up.

    pthread_join(Simpson,NULL);
    pthread_join(Joey,NULL);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

}

/*
@23Aditi ➜ /workspaces/OS/Thread Synchronization/4.1 (main) $ ./p
Press enter to close the counter : 
Mr. Simpson produced pizza with id 1
Mr. Simpson produced pizza with id 2
Mr. Simpson produced pizza with id 3
Mr. Simpson produced pizza with id 4
Mr. Simpson produced pizza with id 5
Joey consumed pizza with id 1
Joey consumed pizza with id 2
Joey consumed pizza with id 3
Joey consumed pizza with id 4
Joey consumed pizza with id 5

Mr. Simpson produced pizza with id 6
Mr. Simpson closed the shop!!
Joey consumed pizza with id 6
Joey's stomach is full!!
*/
