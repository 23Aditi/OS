#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

#define FIFO1 "/tmp/fifo1"
#define FIFO2 "/tmp/fifo2"
#define MAX_BUF 1024
#define OUTPUT_FILE "output.txt"

void count_stats(const char *text, int *chars ,int *words, int *lines){
    *chars = strlen(text);
    *words = 0;
    *lines = 1;
    int in_word = 0;
    for(int i = 0 ; text[i]; i++){
        if(text[i]=='\n') (*lines)++;
        if(text[i] !='\n' || text[i] !=' ' || text[i] !='\t'){
            (*words)++;
        }
    }
}


int main(){
    char buffer[MAX_BUF];
    int fd_read,fd_write;
    
    mkfifo(FIFO1,0666);
    mkfifo(FIFO2,0666);

    while(1){
        fd_read = open(FIFO1,O_RDONLY);
        if(fd_read < 0){
            perror("open read fifo1");
            exit(EXIT_FAILURE);
        }
        int n = read(fd_read,buffer,MAX_BUF-1);
        //when we read we need to keep last slot free for /0
        close(fd_read);

        if(n<=0) continue; // no data continue
        buffer[n]='/0'; // null-terminate the string

        if(strcmp(buffer,"exit")==0) break; // exit signal check

        int chars,words,lines;
        count_stats(buffer,&chars,&words,&lines);

        // writing to file
        FILE *fp = fopen(OUTPUT_FILE,"w"); // truncates existing content and then write
        if(!fp){
            perror("fopen");
            exit(EXIT_FAILURE);
        }
        fprintf(fp,"Characters: %d\nWords : %d\nLines : %d\n",chars,words,lines);
        fclose(fp);

        //reading from output.txt
        fp = fopen(OUTPUT_FILE,"r");
        if(!fp){
            perror("fopen");
            exit(EXIT_FAILURE);
        }
        char file_contents[MAX_BUF]; // it temporarily stores entire contents of file
        // fread reads binary data from a file
        // file_content where to store the data
        // 1 -> size of each item (1byte ->reading characters)
        // MAX_BUF - 1 -> no of bytes(so we have space for a \0)
        // fp -> file pointer to output.txt
        // return value is no of bytes actually read from the file.
        size_t bytes_read = fread(file_content,1,NAX_BUF-1,fp);
        file_contents[bytes_read]='\0'; // adding \0 after the last bit
        fclose(fp);

        //send processed output back to process 1 via FIFO2
        fd_write = open(FIFO2,O_WRONLY);
        if(fd_write<0){
            perror("open write fifo2");
            exit(EXIT_FAILURE);
        }
        write(fd_write,file_contents,strlen(file_contents)+1);
        close(fd_write);
    }
    unlink(FIFO1);
    unlink(FIFO2);
}

