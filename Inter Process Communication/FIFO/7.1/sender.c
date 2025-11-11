#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

#define FIFO "/tmp/fifo1"

int main(){
    char msg[100];
    int fd;

    mkfifo(FIFO,0666);

    printf("Sender ready. Type messages (type 'exit' to quit):\n");
    while(1){
        printf("Message : ");
        fgets(msg,sizeof(msg),stdin);
        //msg[strcspn(msg,"\n")]=0;
        fd = open(FIFO,O_WRONLY);
        write(fd,msg,strlen(msg)+1);
        close(fd);
        if(strcmp(msg,"exit\n")==0){
            break;
        }
    }
    unlink(FIFO);
    return 0;
}


/*
@23Aditi ➜ .../OS/Inter Process Communication/FIFO/7.1 (main) $ ./s
Sender ready. Type messages (type 'exit' to quit):
Message : hi
Message : do u know me?
Message : well the exit is near that door!
Message : let's study os!
Message : indeed our operating systems needs an upgrade in the age of AI!!! 
Message : ok byee!!!
Message : exit
@23Aditi ➜ .../OS/Inter Process Communication/FIFO/7.1 (main) $ 
@23Aditi ➜ .../OS/Inter Process Communication/FIFO/7.1 (main) $ ./r
Received : HI
Received : DO U KNOW ME?
Received : WELL THE EXIT IS NEAR THAT DOOR!
Received : LET'S STUDY OS!
Received : INDEED OUR OPERATING SYSTEMS NEEDS AN UPGRADE IN THE AGE OF AI!!!
Received : OK BYEE!!!
@23Aditi ➜ .../OS/Inter Process Communication/FIFO/7.1 (main) $ 
*/