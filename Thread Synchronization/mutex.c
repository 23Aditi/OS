#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

// reader writer problem 
int readcount = 0;
pthread_mutex_t mutex;
sem_t wrt;

int sharedValue = 10;
volatile int running = 1;

void *reader(void *args){
    int id = *(int *)args;
    while(running){
        pthread_mutex_lock(&mutex);
        readcount++;
        if(readcount==1) sem_wait(&wrt);
        pthread_mutex_unlock(&mutex);
        printf("Reader with id %d is reading shared value %d ....\n",id,sharedValue);
        pthread_mutex_lock(&mutex);
        readcount--;
        if(readcount==0) sem_post(&wrt);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    printf("Reader with id %d is exiting....\n",id);
    pthread_exit(NULL);
}

void *writer(void* args){
    int id = *(int *)args;
    //semaphore -> Either one writer or many readers
    while(running){
        sem_wait(&wrt);
        printf("Writer with id %d is writing shared value as %d...\n",id,sharedValue);
        sharedValue += 5;
        sleep(2);
        sem_post(&wrt);
    }
    printf("Writer exiting with id %d....\n",id);
    pthread_exit(NULL);
}

int main(){
    pthread_t rid[5], wid[2];
    int r[5] = {11,12,13,14,15};
    int w[2] = {1,2};

    pthread_mutex_init(&mutex,NULL);
    sem_init(&wrt,0,1);

    printf("press enter to stop\n");
    for(int i = 0 ; i < 5 ; i++){
        pthread_create(&rid[i],NULL,reader,(void *)&r[i]);
    }
    for(int i = 0 ; i < 2 ; i++){
        pthread_create(&wid[i],NULL,writer,(void *)&w[i]);
    }
    getchar();
    running = 0;
    for(int i = 0 ; i < 5 ; i++){
        pthread_join(rid[i],NULL);
    }
    for(int i = 0 ; i < 2 ; i++){
        pthread_join(wid[i],NULL);
    }
    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);
    printf("program termintated !!\n");
    return 0;
}


/*
Admin@DESKTOP-KMA1ERO MINGW64 /f/ME/3-Year/LABS/OS/OS/Thread Synchronization (main)
$ ./m
press enter to stop
Reader with id 11 is reading shared value 10 ....
Reader with id 12 is reading shared value 10 ....
Reader with id 13 is reading shared value 10 ....
Reader with id 14 is reading shared value 10 ....
Reader with id 15 is reading shared value 10 ....
Writer with id 1 is writing shared value as 10...
Writer with id 2 is writing shared value as 15...
Reader with id 15 is reading shared value 20 ....
Reader with id 14 is reading shared value 20 ....
Reader with id 12 is reading shared value 20 ....
Reader with id 11 is reading shared value 20 ....
Reader with id 13 is reading shared value 20 ....
Writer with id 1 is writing shared value as 20...

Reader with id 13 is exiting....
Reader with id 11 is exiting....
Reader with id 12 is exiting....
Reader with id 14 is exiting....
Reader with id 15 is exiting....
Writer exiting with id 1....
Writer with id 2 is writing shared value as 25...
Writer exiting with id 2....
program termintated !!

Admin@DESKTOP-KMA1ERO MINGW64 /f/ME/3-Year/LABS/OS/OS/Thread Synchronization (main)
$


*/