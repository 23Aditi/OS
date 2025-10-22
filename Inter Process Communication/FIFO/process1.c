#include <stdio.h> // i/p and o/p
#include <stdlib.h> // exit, malloc etc
#include <fcntl.h> // file control library open(),O_RDONLY
#include <unistd.h> // for unix system call
#include <string.h> // for strlen etc
#include <sys/stat.h> // for mkfifo()
#define FIFO1 "/tmp/fifo1"
#define FIFO2 "/tmp/fifo2"
#define MAX_BUF 1024 

void main(){
    char buffer[MAX_BUF]; // defining character arr of size 1024
    int fd_write,fd_read;

    // creating FIFOs if they don't exists
    mkfifo(FIFO1,0666); // 0666 means read and write permission for all users
    mkfifo(FIFO2,0666);

    printf("Process 1 : Enter sentences (type : 'exit' to quit):\n");
    while(1){
        fd_write = open(FIFO1, O_WRONLY); // open is a sys call
        // it takes (path,flags eg-> O_RDONLY)
        // if success returns a non negative value else -1
        if(fd_write < 0){
            perror("open write fifo1"); // fd_write < 0 --> failure
            exit(EXIT_FAILURE);
        }
        printf("You : ");
        if(fgets(buffer,MAX_BUF,stdin)==NULL){ // reads a line of text from user in stdin format
            // stores the line in buffer-> array where i/p is stored
            // max_buffer -> max len to read
            //stdin -> standard i/p (keyboard)
            // this returns buffer on success and null on failure
            perror("fgets");
            close(fd_write); // if we fail to read user i/p close fifo
            break;
        }
        //buffer[strcspn(buffer,"\n")] = '\0'; //it returns the idx of first occurance of character in buffer
        for(int i = 0 ; buffer[i]!='\0'; i++){
            if(buffer[i]=='\n'){
                buffer[i]='\0';
                break;
            }
        }
        // \0 means end of string 
        // instead of strcspn we can use the loop
        // \n is removed so that comparision for exit doesn't cause issue
        if(strcmp(buffer,"exit")==0){
            // exit is present
            write(fd_write,buffer,strlen(buffer)+1); // this is imp to send data to process2 otherwise it will wait infiniely
            close(fd_write);
            break;
        }
        write(fd_write,buffer,strlen(buffer)+1); // +1 for end of string
        // since strlen doesn't count /0 as a character
        close(fd_write); // closing fifo1 as user completed writing
        
        //opening fd_read
        fd_read = open(FIFO2,O_RDONLY);
        if(fd_read<0){
            perror("open read fifo2");
            exit(EXIT_FAILURE);
        }
        int n = read(fd_read,buffer,MAX_BUF-1);
        if(n>0){
            buffer[n] = '\0';
            printf("Processed output from process 2 : \n%s\n",buffer);
        }
        close(fd_read);
    }
    unlink(FIFO1);
    unlink(FIFO2);
}


