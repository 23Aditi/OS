#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int n,m;
int alloc[10][10] , max[10][10],need[10][10],avail[10];
int safeSeq[10];

void readData(){
    FILE* fp = fopen("state.txt","r");
    if(!fp){
        printf("\nUnable to open file! Pls check if file exists!");
        exit(0);
    }
    printf("\nreading no of processes and resources....");
    fscanf(fp,"%d %d",&n,&m);
    printf("\nreading the allocation matrix.....");
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < m ; j++){
            fscanf(fp,"%d",&alloc[i][j]);
        }
    }

    printf("\nreading the MAX matrix.....");
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < m ; j++){
            fscanf(fp,"%d",&max[i][j]);
        }
    }

    printf("\nreading the available matrix");
    for(int j = 0 ; j < m ; j++){
        fscanf(fp,"%d",&avail[j]);
    }
    fclose(fp);
    printf("\nRead operation completed.....");
    sleep(1);
    printf("\nComputing the NEED matrix...");
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < m ; j++){
            need[i][j]= max[i][j]-alloc[i][j];
        }
    }
}

void printSafeSeq(){
    printf("\n SAFE SEQUENCE IS : \n");
    for(int i = 0 ; i < n - 1 ; i++){
        printf("Process %d -> ",safeSeq[i]+1);
    }
    printf("Process %d\n",safeSeq[n-1]+1);
}

int isSafe(){
    int work[10], finish[10]={0}; // finish is used to track processes (n)
    for(int i = 0 ; i < m ; i++) work[i]=avail[i];
    int count = 0;
    while(count < n){
        int found = 0;
        for(int i = 0 ; i < n ; i++){
            if(!finish[i]){
                int j;
                for(j = 0 ; j < m ; j++){
                    if(need[i][j]>work[j]){break;}
                }
                if(j==m){
                    for(int k = 0 ; k < m ; k++){
                        work[k]+=alloc[i][k];
                    }
                    found = 1;
                    finish[i]=1;
                    safeSeq[count]=i;
                    count++;
                }
            }
        }
        if(!found)return 0;
    }
    printSafeSeq();
    return 1;
}

void bankers(int pid){
    int req[10];
    printf("Enter %d resources required : \n",m);
    for(int i = 0 ; i < m ; i++){
        scanf("%d",&req[i]);
    }
    for(int i = 0 ; i < m ; i++){
        if(max[pid][i]<req[i]){
            printf("Invalid request ! Requesting more resouces than MAX allocation !\n");
            exit(0);
        }
        if(avail[i]<req[i]){
            printf("Invalid request ! Requesting more resouces than currently available !\n");
            exit(0);
        }
        if(req[i]>need[pid][i]){
            printf("Invalid request ! Requesting more resouces than needed!!\n");
            exit(0);
        }
    }
    for(int i = 0 ; i < m ; i++){
        alloc[pid][i]+=req[i];
        need[pid][i]-=req[i];
        avail[i]-=req[i];
    }
    if(!isSafe()){
        for(int i = 0 ; i < m ; i++){
            alloc[pid][i]-=req[i];
            need[pid][i]+=req[i];
            avail[i]+=req[i];
        }
        printf("Restoring safe state !! Request rejected ! Changing allocation and need to previous values......\n");
        return;
    }
    printf("Request accepted!!!\n");
}

int main(){
    readData();
    if(isSafe()){
        printf("\nSystem is in safe state!!!!\n");
    }else{
        printf("\nSystem is NOT in safe state!!!!\n");
    }
    int pid;
    printf("Enter requesting process no:\n");
    scanf("%d",&pid);
    if(pid>n){
        printf("invalid pid");
        exit(0);
    }else{
        pid--;
    }
    bankers(pid);
    return 0;
}
