#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
sem_t full, empty;
pthread_mutex_t mutex;
volatile int running = 1;
#define buffer_size 1

void *producer(void * args){
    while(running){
        int n = rand()%10+1;
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        FILE* fp = fopen("file.txt","w");
        fprintf(fp,"%d",n);
        printf("Producer writing %d to file!\n",n);
        fclose(fp);
        
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        sleep(1);
    }
    pthread_exit(NULL);
}

void *consumer(void * args){
    while(running){
        int n;
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        FILE* fp = fopen("file.txt","r");
        fscanf(fp,"%d",&n);
        printf("Consumer reading %d to file!\n",n);
        fclose(fp);
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        sleep(1);
    }
    pthread_exit(NULL);
}

int main(){
    sem_init(&empty,0,1); // initally all empty
    sem_init(&full,0,0); // initally zero full/ no pizza at counter
    pthread_mutex_init(&mutex,NULL);

    pthread_t Prod , cons;

    pthread_create(&Prod,NULL,producer,NULL);
    pthread_create(&cons,NULL,consumer,NULL);

    printf("Press enter to close the counter : \n");
    getchar();
    running = 0;
    sem_post(&empty); // If the producer was waiting for empty, sem_post(&empty) wakes it up.
    sem_post(&full); // If the consumer was waiting for full, sem_post(&full) wakes it up.

    pthread_join(Prod,NULL);
    pthread_join(cons,NULL);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
}

/*
Admin@DESKTOP-KMA1ERO MINGW64 /f/ME/3-Year/LABS/OS/OS/Thread Synchronization/4.3 (main)
$ gcc program.c -o p

Admin@DESKTOP-KMA1ERO MINGW64 /f/ME/3-Year/LABS/OS/OS/Thread Synchronization/4.3 (main)
$ ./p
Press enter to close the counter : 
Producer writing 2 to file!
Consumer reading 2 to file!
Producer writing 8 to file!
Consumer reading 8 to file!
Producer writing 5 to file!
Consumer reading 5 to file!
Producer writing 1 to file!
Consumer reading 1 to file!
Producer writing 10 to file!
Consumer reading 10 to file!
Producer writing 5 to file!
Consumer reading 5 to file!
Producer writing 9 to file!
Consumer reading 9 to file!
Producer writing 9 to file!
Consumer reading 9 to file!
Producer writing 3 to file!
Consumer reading 3 to file!


Admin@DESKTOP-KMA1ERO MINGW64 /f/ME/3-Year/LABS/OS/OS/Thread Synchronization/4.3 (main)
$

*/