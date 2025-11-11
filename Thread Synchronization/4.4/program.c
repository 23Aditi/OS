#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

volatile int running = 1;
int avail_flights = 100;

sem_t db;
pthread_mutex_t mutex;

#define max_reader 2
#define max_writer 5

int readcount = 0;


void * reader(void* args){
    while(running){
        pthread_mutex_lock(&mutex);
        readcount++;
        if(readcount == 1){
            sem_wait(&db);
        }
        pthread_mutex_unlock(&mutex);        
        printf("Reader %d read :- no of flights = %d\n",readcount,avail_flights);
        sleep(1);
        pthread_mutex_lock(&mutex);
        readcount--;
        if(readcount==0){
            sem_post(&db); // last reader to read db
        }
        sleep(1);
        pthread_mutex_unlock(&mutex);        
    }
    pthread_exit(NULL);
}

void* writer(void * args){
    while(running){
        sem_wait(&db);

        int num = rand()%10 + 1;
        if(avail_flights >= num){
            avail_flights -=num;
            printf("Writer booked seats %d | Remaining %d\n",num,avail_flights);
        }else{
            printf("Writer tried booking %d seats but seats not available!\n",num);
        }
        sleep(1);
        sem_post(&db);
    }
    pthread_exit(NULL);
}

int main(){
    pthread_t flight_reader[max_reader], flight_writer[max_writer];
    sem_init(&db,0,1);
    pthread_mutex_init(&mutex,NULL);
    srand(time(NULL));
    for(int i = 0 ; i < max_writer ; i++){
        pthread_create(&flight_writer[i],NULL,writer,NULL);
    }

    for(int i = 0 ; i < max_reader ; i++){
        pthread_create(&flight_reader[i],NULL,reader,NULL);
    }

    
    printf("Press enter to exit !:\n");
    getchar();
    running = 0;

    for(int i = 0 ; i < max_reader ; i++){
        pthread_join(flight_reader[i],NULL);
    }

    for(int i = 0 ; i < max_writer ; i++){
        pthread_join(flight_writer[i],NULL);
    }
    sem_destroy(&db);
    pthread_mutex_destroy(&mutex);

}

/*✅ Use a mutex when

You want to ensure only one thread modifies or reads a critical section at a time.

Example:

pthread_mutex_lock(&mutex);
shared_counter++;
pthread_mutex_unlock(&mutex);


Only one thread can update shared_counter safely.

✅ Use a semaphore when

You need:

To limit how many threads can enter (e.g., only 3 at once),

Or to signal between threads that something happened.

Example 1: Limit access (counting)

sem_init(&sem, 0, 3);  // only 3 threads allowed
sem_wait(&sem);
// critical section
sem_post(&sem);*/

/*
Admin@DESKTOP-KMA1ERO MINGW64 /f/ME/3-Year/LABS/OS/OS/Thread Synchronization/4.4 (main) 
$ ./p
Writer booked seats 2 | Remaining 98
Press enter to exit !:
Writer booked seats 2 | Remaining 96
Writer booked seats 2 | Remaining 94
Writer booked seats 2 | Remaining 92
Writer booked seats 2 | Remaining 90
Reader 1 read :- no of flights = 90
Reader 2 read :- no of flights = 90
Reader 2 read :- no of flights = 90
Writer booked seats 8 | Remaining 82
Writer booked seats 8 | Remaining 74
Writer booked seats 8 | Remaining 66
Writer booked seats 8 | Remaining 58
Writer booked seats 8 | Remaining 50
Reader 1 read :- no of flights = 50
Reader 2 read :- no of flights = 50
Reader 2 read :- no of flights = 50
Writer booked seats 5 | Remaining 45
Writer booked seats 5 | Remaining 40
Writer booked seats 5 | Remaining 35
Writer booked seats 5 | Remaining 30
Writer booked seats 5 | Remaining 25
Writer booked seats 1 | Remaining 24
Reader 1 read :- no of flights = 24
Reader 2 read :- no of flights = 24
Reader 2 read :- no of flights = 24
Reader 2 read :- no of flights = 24
Reader 2 read :- no of flights = 24
Writer booked seats 1 | Remaining 23
Writer booked seats 1 | Remaining 22
Writer booked seats 1 | Remaining 21
Writer booked seats 1 | Remaining 20
Writer booked seats 10 | Remaining 10
Reader 1 read :- no of flights = 10
Reader 2 read :- no of flights = 10
Reader 2 read :- no of flights = 10
Reader 2 read :- no of flights = 10
Reader 2 read :- no of flights = 10
Reader 2 read :- no of flights = 10
Reader 2 read :- no of flights = 10
Reader 2 read :- no of flights = 10
Writer booked seats 10 | Remaining 0
Writer tried booking 10 seats but seats not available!
Writer tried booking 10 seats but seats not available!
Writer tried booking 10 seats but seats not available!
Writer tried booking 5 seats but seats not available!

Reader 1 read :- no of flights = 0
Reader 2 read :- no of flights = 0
Writer tried booking 5 seats but seats not available!
Writer tried booking 5 seats but seats not available!
Writer tried booking 5 seats but seats not available!
Writer tried booking 5 seats but seats not available!

Admin@DESKTOP-KMA1ERO MINGW64 /f/ME/3-Year/LABS/OS/OS/Thread Synchronization/4.4 (main) 
$*/