#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024

int main(){
    key_t key;
    int shmid;
    key = ftok("shmfile",65);
    if(key==-1){
        perror("ftok");
        exit(EXIT_FAILURE);
    }
    shmid = shmget(key,SHM_SIZE,0666);
    if(shmid == -1){
        perror("shmget");
        exit(EXIT_FAILURE);
    }
    char *data;
    data = shmat(shmid,NULL,0 |IPC_CREAT);
    if(data == (char *)-1){
        perror("shmat");
        exit(EXIT_FAILURE);
    }
    printf("Client : Hello from client side\n");
    printf("SHARED MEMORY : data in the shared memory is : \n%s\n",data);
    if(shmdt(data)==-1){
        perror("shmdt");
        exit(EXIT_FAILURE);
    }
    return 0;
}
