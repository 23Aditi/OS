#include <stdio.h>
#include <stdlib.h>

int end_of_disc = 499;

void scan(int n , int req[], int head){
    printf("\nSCAN : \n");
    
    int diff = 0;
    int idx = 0;
    while(req[idx]<head){idx++;}
    printf("Direction is right of scan :\n");
    for(int i = idx ; i < n ; i++){
        diff += abs(head-req[i]);
        head = req[i];
    }
    diff += abs(head - end_of_disc);
    head = end_of_disc;
    for(int i = idx-1 ; i >=0 ; i--){
        diff += abs(head-req[i]);
        head = req[i];
    }
    printf("Total seek time is %d\n",diff);
    float seek = (float)diff/n;
    printf("\nAverage seek time for scan algo : %f \n",seek);
}

void look(int n , int req[], int head){
    printf("\nLOOK\n");
    int diff = 0;
    int idx = 0;
    while(idx<n && req[idx]<head)idx++;
    for(int i = idx ; i < n ; i++){
        diff += abs(req[i]-head);
        head = req[i];
    }
    for(int i = idx - 1 ; i >=0 ; i--){
        diff += abs(req[i]-head);
        head = req[i];
    }
    printf("Total seek time is %d\n",diff);
    float seek = (float)diff/n;
    printf("\nAverage seek time for look algo : %f \n",seek);

}

void cscan(int n , int req[], int head){
    // arr is already sorted
    printf("\nCSCAN : \n");
    int idx = 0;
    int diff = 0;
    while(idx<n && req[idx]<head) idx++;
    for(int i = idx ; i < n ; i++){
        diff += abs(head - req[i]);
        head = req[i];
    }
    diff += abs(head - end_of_disc);
    head = end_of_disc;
    diff += abs(head - 0);
    head = 0;
    for(int i = 0 ; i < idx ; i++){
        diff += abs(head - req[i]);
        head = req[i];
    }
    printf("Total seek time is %d\n",diff);
    float seek = (float)diff/n;
    printf("\nAverage seek time for cscan algo : %f \n",seek);
}

void clook(int n , int req[], int head){
    printf("\nCLOOK : \n");
    int diff = 0;
    int idx = 0;
    while(idx < n && req[idx]<head){idx++;}
    for(int i = idx ; i < n ; i++){
        diff += abs(req[i]-head);
        head = req[i];
    }
    for(int i = 0 ; i < idx ; i++){
        diff += abs(req[i]-head);
        head = req[i];
    }
    printf("Total seek time is %d\n",diff);
    float seek = (float)diff/n;
    printf("\nAverage seek time for clook algo : %f \n",seek);
}


int main(){
    int n;
    printf("\nEnter no of requests :\n");
    scanf("%d",&n);
    printf("Enter %d requests : \n",n);
    int requests[n];
    for(int i = 0 ; i < n ; i++){
        scanf("%d",&requests[i]);
    }
    printf("Enter head:\n");
    int head;
    scanf("%d",&head);
    for(int i = 0 ; i < n - 1 ; i++){
        for(int j = 0 ; j < n - i - 1 ; j++){
            if(requests[j]>requests[j+1]){
                int temp = requests[j];
                requests[j] = requests[j+1];
                requests[j+1]=temp;
            }
        }
    }
    scan(n,requests,head);
    look(n,requests,head);
    cscan(n,requests,head);
    clook(n,requests,head);
}

