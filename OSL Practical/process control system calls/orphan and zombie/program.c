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

void insertion_sort(int n, int arr[]){
    int i,j,key;
    for(int i = 1 ; i < n ; i++){
        key = arr[i];
        j = i-1;
        while(j>=0 && arr[j]>key){
            arr[j+1] = arr[j];j--;
        }
        arr[j+1]=key;
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
        printf("\nIn child process!!\n");
        printf("\nChild pid : %d, Parent pid: %d\n",getpid(),getppid());
        printf("\nbefore using insertion sort :\n");
        for(int i = 0 ; i < n ; i++){
            printf("%d ",arr[i]);
        }
        insertion_sort(n,arr);
        printf("\nafter using insertion sort :\n");
        for(int i = 0 ; i < n ; i++){
            printf("%d ",arr[i]);
        }
       // sleep(100); //-> orphan
    }else{
        // parent 
        printf("\nIn parent process!!\n");
        printf("\nparent pid : %d, Parent's parent pid: %d\n",getpid(),getppid());
        printf("\nbefore using bubble sort :\n");
        for(int i = 0 ; i < n ; i++){
            printf("%d ",arr[i]);
        }
        bubble_sort(n,arr);
        printf("\nafter using bubble sort :\n");
        for(int i = 0 ; i < n ; i++){
            printf("%d ",arr[i]);
        }
        //sleep(100); //-> for zombie
        wait(NULL);
        printf("\nParent : child process finished execution\n");
    }
    return 0;
}

