#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_CHAIRS 3      // number of waiting chairs
#define NUM_STUDENTS 8    // total number of students

sem_t students;   // counts waiting students
sem_t ta_ready;   // indicates TA is ready
pthread_mutex_t mutex;  // protects shared variable

int waiting_students = 0;
volatile int running = 1;  // shared flag to stop threads safely

// Teaching Assistant thread function
void* ta_thread(void* arg) {
    while (running) {
        // Wait for a student to arrive
        if (sem_trywait(&students) != 0) {
            // If no students, TA naps
            usleep(100000); // short nap (0.1 sec)
            continue;
        }

        pthread_mutex_lock(&mutex);
        waiting_students--;
        printf("TA starts helping a student. Waiting students: %d\n", waiting_students);
        pthread_mutex_unlock(&mutex);

        // Simulate helping student
        sleep(2);
        printf("TA finished helping a student.\n");

        // Signal that TA is ready for the next student
        sem_post(&ta_ready);
    }

    printf("TA is done for the day. Office closed.\n");
    return NULL;
}

// Student thread function
void* student_thread(void* id) {
    int student_id = *(int*)id;

    while (running) {
        pthread_mutex_lock(&mutex);
        if (waiting_students < NUM_CHAIRS) {
            waiting_students++;
            printf("Student %d sits in waiting chair. Waiting students: %d\n", student_id, waiting_students);
            pthread_mutex_unlock(&mutex);

            // Notify TA that a student is waiting
            sem_post(&students);

            // Wait until TA is ready
            sem_wait(&ta_ready);

            // Get help from TA
            printf("Student %d is getting help from the TA.\n", student_id);
            sleep(3); // simulate help time
        } else {
            pthread_mutex_unlock(&mutex);
            printf("Student %d found no chair and will try later.\n", student_id);
            sleep(rand() % 3 + 1); // try again later
        }

        // Come back after some random time
        sleep(rand() % 4 + 1);
    }

    printf("Student %d goes home.\n", student_id);
    return NULL;
}

int main() {
    pthread_t ta_tid;
    pthread_t student_tids[NUM_STUDENTS];
    int student_ids[NUM_STUDENTS];

    srand(time(NULL));

    // Initialize semaphores and mutex
    sem_init(&students, 0, 0);
    sem_init(&ta_ready, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    // Create TA thread
    pthread_create(&ta_tid, NULL, ta_thread, NULL);

    // Create student threads
    for (int i = 0; i < NUM_STUDENTS; i++) {
        student_ids[i] = i + 1;
        pthread_create(&student_tids[i], NULL, student_thread, &student_ids[i]);
    }

    // Wait for user input to stop
    printf("\nPress ENTER to stop the simulation...\n");
    getchar();  // waits for Enter key
    running = 0;

    // Allow threads to finish their current work
    sleep(2);

    // Cleanup
    pthread_mutex_destroy(&mutex);
    sem_destroy(&students);
    sem_destroy(&ta_ready);

    printf("\nSimulation ended.\n");
    return 0;
}

/*
@23Aditi ➜ /workspaces/OS/Thread Synchronization/4.2 (main) $ ./p
Student 2 sits in waiting chair. Waiting students: 1
Student 1 sits in waiting chair. Waiting students: 2
Student 3 sits in waiting chair. Waiting students: 3
Student 5 found no chair and will try later.
Student 6 found no chair and will try later.
Student 7 found no chair and will try later.
Student 8 found no chair and will try later.

Press ENTER to stop the simulation...
Student 4 found no chair and will try later.
TA starts helping a student. Waiting students: 2

TA finished helping a student.
Student 2 is getting help from the TA.
TA is done for the day. Office closed.

Simulation ended.
@23Aditi ➜ /workspaces/OS/Thread Synchronization/4.2 (main) $ 
*/