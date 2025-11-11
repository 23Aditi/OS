#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

struct shmseg{
    int flag;
    char message[100];
};

int main(){
    key_t key = 1234;
    int shmid = shmget(key,sizeof(struct shmseg),0666 | IPC_CREAT);
    struct shmseg *shm = (struct shmseg *)shmat(shmid,NULL,0);
    printf("Server : Enter message to send to client : ");
    fgets(shm->message,sizeof(shm->message),stdin);
    shm->message[strcspn(shm->message,"\n")]=0;
    shm->flag = 1;
    printf("Server : Message writter. Waiting for client to read....\n");
    while(shm->flag !=2){
        sleep(1);
    }
    printf("Server : Client read the message. Cleaning up.\n");
    shmdt(shm);
    shmctl(shmid,IPC_RMID,NULL); // delete shared memory segment
    return 0;
}

/*
@23Aditi ➜ .../OS/Inter Process Communication/shared memory/7.2 (main) $ gcc server.c -o s
@23Aditi ➜ .../OS/Inter Process Communication/shared memory/7.2 (main) $ ./s
Server : Enter message to send to client : fghjkl
Server : Message writter. Waiting for client to read....
Server : Client read the message. Cleaning up.
@23Aditi ➜ .../OS/Inter Process Communication/shared memory/7.2 (main) $ 
@23Aditi ➜ .../OS/Inter Process Communication/shared memory/7.2 (main) $ gcc client.c -o c
@23Aditi ➜ .../OS/Inter Process Communication/shared memory/7.2 (main) $ ./c
Client : Waiting for server to write message....
Client : Message from server = fghjkl 
@23Aditi ➜ .../OS/Inter Process Communication/shared memory/7.2 (main) $ 

*/

