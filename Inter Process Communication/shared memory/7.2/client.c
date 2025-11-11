#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

struct shmget{
    int flag;
    char message[100];
};

int main(){
    key_t key = 1234;
    int shmid = shmget(key,sizeof(struct shmget),0666 | IPC_CREAT);
    struct shmget *shm = (struct shmget *)shmat(shmid,NULL,0);
    printf("Client : Waiting for server to write message....\n");
    while(shm->flag != 1){
        sleep(1);
    }
    printf("Client : Message from server = %s \n",shm->message);
    shm->flag = 2;
    return 0;
    shmdt(shm);
    return 0;
}
