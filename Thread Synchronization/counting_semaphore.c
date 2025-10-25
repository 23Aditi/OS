#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define buffer_size 5
#define no_of_producers 5
#define no_of_consumers 5
#define no_of_items 5

int buffer[buffer_size];
int in = 0 , out = 0;

sem_t empty;
sem_t full;
pthread_mutex_t mutex;

const char* brand_names[no_of_producers] = {
    "Oreo",
    "Oreo1",
    "Oreo2",
    "Oreo3",
    "Oreo4"
};

const char* consumer_cities[no_of_consumers]={
    "city",
    "city1",
    "city2",
    "city3",
    "city4"
};

void* producer(void *arg){
    const char *brand = (const char *)arg;
    int item;
    for(int i = 0 ; i < no_of_items ; i++){
        item = (i*5+23)/2;
        sem_wait(&empty); // wait if full
        pthread_mutex_lock(&mutex);
        buffer[in]=item;
        printf("Producer %s produced item %d at buffer %d\n",brand,item,in);
        in = (in + 1)%buffer_size;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        sleep(3);
    }
    return NULL;
}

void* consumer(void * arg){
    const char *city = (const char *)arg;
    int item;
    for(int i = 0 ; i < no_of_items ; i++){
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        item = buffer[out];
        printf("consumer %s consumed %d at index %d\n",city,item,out);
        out = (out+1)%buffer_size;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        sleep(3);
    }
    return NULL;
}

void main(){
    pthread_t producer_thread[no_of_producers];
    pthread_t consumer_thread[no_of_consumers];

    sem_init(&empty, 0 , buffer_size);
    sem_init(&full,0,0);
    pthread_mutex_init(&mutex,NULL);

    for(int i = 0 ; i < no_of_producers ; i++){
        pthread_create(&producer_thread[i],NULL,producer,(void *)brand_names[i]);
    }
    for(int i = 0 ; i < no_of_consumers ; i++){
        pthread_create(&consumer_thread[i],NULL,consumer,(void *)consumer_cities[i]);
    }
    // wait for all threads to finsih 
    for(int i = 0 ; i < no_of_producers ; i++){
        pthread_join(producer_thread[i],NULL);
    }
    for(int i = 0 ; i < no_of_consumers ; i++){
        pthread_join(consumer_thread[i],NULL);
    }
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);
    return;
}
