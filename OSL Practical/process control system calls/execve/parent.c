#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void bubble_sort(int n , int arr[]){
    int i,j,temp;
    for(i = 0 ; i < n-1 ; i++){
        for(j = 0 ; j < n-1-i; j++){
            if(arr[j]>arr[j+1]){
                temp = arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }
}

int main(){
    int n;
    printf("Enter no of elements in array(size of arr):\n");
    scanf("%d",&n);
    int arr[n];
    printf("Enter %d elements: \n",n);
    for(int i = 0 ; i < n ; i++){
        scanf("%d",&arr[i]);
    }
    pid_t pid = fork(); // create child
    if(pid<0){
        perror("fork failed!");
        exit(1);
    }
    else if(pid==0){
        sleep(2);
        char* args[n+3];
        args[0]="./binary_search";
        for(int i = 0 ; i < n ; i++){
            char* num = malloc(10);
            sprintf(num,"%d",arr[i]);
            args[i+1]=num;
        }
        printf("\nEnter key for binary search : \n");
        int key ;
        scanf("%d",&key);
        char* key_str = malloc(10);
        sprintf(key_str,"%d",key);
        args[n+1]=key_str;
        args[n+2]=NULL;
        if(execve(args[0],args,NULL)==-1){
            perror("execve");
            exit(1);
        }
    }else{
        // parent 
        bubble_sort(n,arr);
        
        wait(NULL);
        printf("child process finished");
        
    }
    return 0;
}

