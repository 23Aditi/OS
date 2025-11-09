#include <stdlib.h>
#include <stdio.h>

struct Process{
    int pid;
    int at;
    int bt;
    int rt;
    int wt;
    int ct;
    int tat;
    int done;
};

void FCFS(int n, struct Process process[]){
    struct Process temp;
    for(int i = 0 ; i < n - 1 ; i++){
        for(int j = 0 ; j < n - i - 1 ; j++){
            if(process[j].at>process[j+1].at){
                temp = process[j];
                process[j]=process[j+1];
                process[j+1]=temp;
            }
        }
    }
    int time = 0;
    printf("\nFCFS Scheduling : \n");
    for(int i = 0 ; i < n ; i++){
        if(time<process[i].at){time = process[i].at;}
        time += process[i].bt;
        process[i].ct = time;
        process[i].tat = process[i].ct - process[i].at;
        process[i].wt = process[i].ct - process[i].at - process[i].bt;
        process[i].done = 1;
    }
    struct Process t;
    printf("\npid\tat\tbt\tct\ttat\twt\n");
    for(int i = 0 ; i < n ; i++){
        t = process[i];
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",t.pid,t.at,t.bt,t.ct,t.tat,t.wt);
    }

}

void SJF(int n, struct Process process[]){
    int time = 0 , completed = 0;
    while(completed < n ){
        int idx = -1;
        int min_bt = 99999;
        for(int i = 0 ; i < n ; i++){
            if(time >= process[i].at && process[i].done == 0){
                if(process[i].bt < min_bt){
                    idx = i;
                    min_bt = process[i].bt;
                }
            }
        }
        if(idx==-1) {time++; continue;}
        process[idx].done = 1;
        time += process[idx].bt;
        process[idx].ct = time;
        process[idx].tat = process[idx].ct - process[idx].at;
        process[idx].wt = process[idx].ct - process[idx].at - process[idx].bt;
        completed++;
    }

    printf("\nSJF Scheduling : \n");
    // printing 
    struct Process t;
    printf("\npid\tat\tbt\tct\ttat\twt\n");
    for(int i = 0 ; i < n ; i++){
        t = process[i];
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",t.pid,t.at,t.bt,t.ct,t.tat,t.wt);
    }
}


void SRTF(int n , struct Process process[]){
    int completed = 0 , time = 0;
    while(completed < n){
        int idx = -1;
        int min_rt = 99999;
        for(int i = 0 ; i < n ; i++){
            if(process[i].done == 0 && process[i].at <= time){
                if(process[i].rt < min_rt){
                    idx = i;
                    min_rt = process[i].rt;
                }
            }
        }
        if(idx == -1){time ++; continue;}
        process[idx].rt--;time++;
        if(process[idx].rt == 0){
            process[idx].ct = time;
            process[idx].tat = process[idx].ct - process[idx].at;
            process[idx].wt = process[idx].ct - process[idx].at - process[idx].bt;
            process[idx].done = 1;
            completed++;
        }
        
    }
    printf("\nSRTF Scheduling : \n");
    // printing 
    struct Process t;
    printf("\npid\tat\tbt\tct\ttat\twt\n");
    for(int i = 0 ; i < n ; i++){
        t = process[i];
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",t.pid,t.at,t.bt,t.ct,t.tat,t.wt);
    }
}

void roundRobin(int n , struct Process process[]){
    int time = 0;
    int timeQtm;
    printf("\nEnter time quantum : \n");
    scanf("%d",&timeQtm);
    int completed = 0;
    while(completed < n){
        int doneSomething = 0;
        for(int i = 0 ; i < n ; i++){
            if(process[i].at <=time && process[i].done == 0){
                doneSomething= 1;
                if(process[i].rt>timeQtm){
                    process[i].rt -= timeQtm; time += timeQtm;
                }else{
                    process[i].done = 1;
                    time += process[i].rt;
                    process[i].rt = 0;
                    process[i].ct = time;
                    completed++;
                    process[i].tat = process[i].ct - process[i].at;
                    process[i].wt = process[i].ct - process[i].at - process[i].bt;
                }
            }
        }
        if(!doneSomething){time++;}
    }
    printf("\nRound Robin Scheduling : \n");
    // printing 
    struct Process t;
    printf("\npid\tat\tbt\tct\ttat\twt\n");
    for(int i = 0 ; i < n ; i++){
        t = process[i];
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",t.pid,t.at,t.bt,t.ct,t.tat,t.wt);
    }
}

int main(){
    int n;
    printf("enter no of processes:\n");
    scanf("%d",&n);
    struct Process process[n];
    printf("Enter details of %d projects :\n",n);
    for(int i = 0 ; i < n ; i++){
        printf("Enter arrival time : \n");
        scanf("%d",&process[i].at);
        printf("Enter burst time : \n");
        scanf("%d",&process[i].bt);
        process[i].pid=i+1;
        process[i].done = 0;
        process[i].rt = process[i].bt;
    }
    FCFS(n,process);
    for(int i = 0 ; i < n ; i++)process[i].done = 0;
    SJF(n,process);
    for(int i = 0 ; i < n ; i++){process[i].done = 0;process[i].rt = process[i].bt;}
    SRTF(n,process);
    for(int i = 0 ; i < n ; i++){process[i].done = 0;process[i].rt = process[i].bt;}
    roundRobin(n,process);
}