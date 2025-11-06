#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <string.h>

#define SHM_SIZE 1024

int main(){
    key_t key;
    int shmid;
    key = ftok("shmfile",65);
    if(key==-1){
        perror("ftok");
        exit(EXIT_FAILURE);
    }
    char* data;
    shmid = shmget(key,SHM_SIZE,0666|IPC_CREAT);
    if(shmid == -1){
        perror("shmget");
        exit(EXIT_FAILURE);
    }
    data = (char *)shmat(shmid,NULL,0);
    if(data = (char *)-1){
        perror("shmat");
        exit(EXIT_FAILURE);
    }
    const char* message = "Hello , I am SERVER (33201)! Wanna talk?";
    data = strncpy(data,message,SHM_SIZE-1);
    data[SHM_SIZE -1 ]='\0';
    printf("Server writing message\n");
    printf("press enter to detach");
    getchar();
    if(shmdt(data)==-1){
        perror("shmdt");
        exit(EXIT_FAILURE);
    }
    // remove shared memory segment
    if(shmctl(shmid,IPC_RMID,NULL)==-1){
        perror("shmclt");
        exit(EXIT_FAILURE);
    }
    printf("Server : shared memory removed !!!");
    return 0;
}