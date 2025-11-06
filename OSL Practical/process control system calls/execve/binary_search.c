#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


void binary_search(int n, int key, int arr[]){
    int i = 0;
    int j = n-1;
    while(i<=j){
        int mid = (i+j)/2;
        if(arr[mid]==key){
            printf("\nElement %d found at index %d !!\n",key,mid);return;
        }
        else if(arr[mid]>key){
            j = mid-1;
        }else{
            i = mid +1;
        }
    }
    printf("\nElement %d not found!",key);
}


int main(int argc,char * args[]){
    int n = argc-2;
    int arr[n];
    for(int i = 0 ; i <n ; i++){
        arr[i]=atoi(args[i+1]);
        printf("%d ", arr[i]);
    }
    int key = atoi[args[argc-1]]; 
    binary_search(n,key,arr);
}

