#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void sort(int arr[], int n){
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n - 1- i ; j++){
            int temp;
            if(arr[j]>arr[j+1]){ // A
                temp = arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }
}

void SCAN(int req[], int n , int head, int dir , int disk_size){
    sort(req,n);
    int total = 0;
    printf("\nSCAN direction is %s",dir?"Right":"Left");
    int pos = 0;
    while(pos<n && req[pos]<head)pos++;
    printf("%d",head);
    if(dir){ //Right
        for(int i = pos; i < n ; i++){
            total += abs(head-req[i]);
            head = req[i];
            printf(" -> %d",head);
        }
        if(head != disk_size - 1 ){
            total += abs((disk_size - 1) - head);
            head = disk_size - 1;
            printf(" -> %d",head);
        }
        for(int i = pos - 1 ; i >= 0 ; i--){
            total += abs(head-req[i]);
            head = req[i];
            printf(" -> %d",head);
        }
    }else{ //Left
        for(int i = pos - 1 ; i>=0 ; i--){
            total += abs(head-req[i]);
            head = req[i];
            printf(" -> %d",head);
        }
        if(head != 0){
            total += abs(head - 0);;
            head = 0;
            printf(" -> %d",head);
        }
        for(int i = pos ; i < n ; i++){
            total += abs(head - req[i]);
            head = req[i];
            printf(" -> %d",head);
        }
    }
    printf("\nTotal = %d\n",total);
}


void SSTF(int req[],int n , int head){
    int visited[n];
    for(int i = 0 ; i < n ; i++){
        visited[i]=0;
    }
    int total = 0;
    int count = 0;
    printf("SSTF : head is %d\n",head);
    printf("%d -> ",head);

    while(count < n){
        int dist = 1000000; 
        int idx = -1;
        for(int i = 0 ; i < n ; i++){
            if(!visited[i] && abs(head-req[i])<dist){
                dist = abs(head-req[i]);
                idx = i;
            }
        }
        visited[idx]=1;
        count++;
        total += dist;
        head = req[idx];
        printf("%d -> ",req[idx]);
    }
    printf("\nTotal : %d",total);
}

void c_look(int req[],int n,int head,int dir){
    sort(req,n);
    printf("\nC-LOOK ....\n");
    int pos = 0, total = 0;
    printf("%d -> ",head);
    while(req[pos]<head) pos++;
    if(dir){ // right
        for(int i = pos ; i < n ; i++){
            total += abs(head-req[i]);
            head = req[i];
            printf("%d -> ",head);
        }
        //total += abs(req[0]-head);
        head = req[0];
        for(int i = 0 ; i < pos ; i++){
            total += abs(head-req[i]);
            head = req[i];
            printf("%d ->",head);
        }
    }else{ // left
        for(int i = pos - 1 ; i >= 0 ; i--){
            total += abs(head-req[i]);
            head = req[i];
            printf("%d ->",head);
        }
        //total += abs(req[n-1]-head);
        head = req[n-1];
        for(int i = n-1 ; i >=pos ; i--){
            total += abs(head-req[i]);
            head = req[i];
            printf("%d -> ",head);
        }
    }
    printf("\nTotal : %d",total);
}

int main(){
    int n;
    printf("Enter n : ");
    scanf("%d",&n);
    int req[n];
    printf("Enter n numbers : ");
    for(int i = 0 ; i < n ; i++){
        scanf("%d",&req[i]);
    }
    int head;
    printf("Enter head : ");
    scanf("%d",&head);
    SSTF(req,n,head);
    printf("\nEnter size of disk : \n");
    int disk_size;
    scanf("%d",&disk_size);
    int dir;
    printf("\nEnter:\n0.Left\n1.Right\n");
    scanf("%d",&dir);
    SCAN(req,n,head,dir,disk_size);
    c_look(req,n,head,dir);
    return 0;
}

/*Admin@DESKTOP-KMA1ERO MINGW64 /f/ME/3-Year/LABS/OS/OS/Disk Scheduling (main)
$ gcc disk.c -o d

Admin@DESKTOP-KMA1ERO MINGW64 /f/ME/3-Year/LABS/OS/OS/Disk Scheduling (main)
$ ./d
Enter n : 5
Enter n numbers : 10 20 60 70 100
Enter head : 50
SSTF : head is 50
50 -> 60 -> 70 -> 100 -> 20 -> 10 ->
Total : 140
Enter size of disk :
130

Enter:
0.Left
1.Right
0

SCAN direction is Left50 -> 20 -> 10 -> 0 -> 60 -> 70 -> 100
Total = 150

C-LOOK ....
50 -> 20 ->10 ->100 -> 70 -> 60 ->
Total : 80
Admin@DESKTOP-KMA1ERO MINGW64 /f/ME/3-Year/LABS/OS/OS/Disk Scheduling (main)
$ ./d
Enter n : 5
Enter n numbers : 10 20 70 60 100
Enter head : 50
SSTF : head is 50
50 -> 60 -> 70 -> 100 -> 20 -> 10 ->
Total : 140
Enter size of disk :
130

Enter:
0.Left
1.Right
1

SCAN direction is Right50 -> 60 -> 70 -> 100 -> 129 -> 20 -> 10
Total = 198

C-LOOK ....
50 -> 60 -> 70 -> 100 -> 10 ->20 ->
Total : 60
Admin@DESKTOP-KMA1ERO MINGW64 /f/ME/3-Year/LABS/OS/OS/Disk Scheduling (main)
$*/
