#include <stdio.h>
#include <stdlib.h>


void FIFO(int n , int pages[]){
    int hit = 0;
    int frame_size = 3;
    int frame[frame_size];
    for(int i = 0 ; i < frame_size ; i++) frame[i]=-1;
    int first = 0;
    for(int i = 0 ; i < n ; i++){
        int page = pages[i];
        int found = 0;
        int idx = -1;
        for(int j = 0 ; j < frame_size ; j++){
            if(frame[j]==page){
                found = 1; break;
            }
            if(frame[j]==-1){idx = j;}
        }
        if(found){
            hit++;
            continue;
        }
        if(idx!=-1){
            frame[idx]=page;
            continue;
        }
        frame[first]=page;
        first = (first + 1)%frame_size;
    }

    float hit_ratio = (float)hit/n;
    float miss_ratio = (float)(n-hit)/n;
    printf("\nFIFO :\n");
    printf("hit ratio : %f",hit_ratio);
    printf("\tmiss ratio : %f",miss_ratio);
}

void LRU(int n , int pages[]){
    int time = 0;
    int hit = 0;
    int frame_size = 3;
    int frame[frame_size];
    int recent[frame_size];
    for(int i = 0 ; i < frame_size ; i++){ frame[i]=-1; recent[i]=0;}
    for(int i = 0 ; i < n ; i++){
        int idx = -1;
        int found = 0;
        int page = pages[i];
        time++;
        for(int j = 0 ; j < frame_size ; j++){
            if(page == frame[j]){
                found = 1;
                recent[j]=time;
                hit++;
                break;
            }
            if(frame[j]==-1){
                idx = j;
            }
        }
        if(found)continue;
        if(idx != -1){
            frame[idx]=page;
            recent[idx]=time;
            continue;
        }
        int mini = 99999;
        idx = -1;
        for(int j = 0 ; j < frame_size ; j++){
            if(recent[j]<mini){mini=recent[j];idx = j;}
        }
        frame[idx]=page;
        recent[idx]=time;
    }
    float hit_ratio = (float)hit/n;
    float miss_ratio = (float)(n-hit)/n;
    printf("\nLRU :\n");
    printf("hit ratio : %f",hit_ratio);
    printf("\tmiss ratio : %f",miss_ratio);
}

void Optimal(int n, int pages[]){
    int frame_size = 3;
    int time = 0;
    int hit = 0;
    int frame[frame_size];
    for(int i = 0 ; i < frame_size ; i++){
        frame[i]=-1;
    }
    for(int i = 0 ; i < n ; i++){
        int idx = -1;
        int found = 0;
        int page = pages[i];
        for(int j = 0 ; j < frame_size ; j++){
            if(frame[j]==page){
                hit++;
                found = 1;
                break;
            }
            if(frame[j]==-1){
                idx = j;
            }
        }
        if(found)continue;
        if(idx!=-1){
            frame[idx]=page;continue;
        }

        int farthest = -1, replace_idx = -1;
        for(int j = 0; j < frame_size ; j++){
            int next_use = -1;
            for(int k = i+1 ; k < n ; k++){
                if(pages[k]==frame[j]){
                    next_use = k;
                }
            }
            if(next_use == -1){
                replace_idx = j;
                break;
            }
            if(next_use > farthest){
                farthest = next_use;
                replace_idx = j;
            }
        }
        frame[replace_idx]=page;
    }
    float hit_ratio = (float)hit/n;
    float miss_ratio = (float)(n-hit)/n;
    printf("\nOptimal :\n");
    printf("hit ratio : %f",hit_ratio);
    printf("\tmiss ratio : %f",miss_ratio);
}


int main(){
    int n;
    printf("\nEnter no of requests\n");
    scanf("%d",&n);
    int pages[n];
    printf("Enter %d pages!\n",n);
    for(int i = 0 ; i < n ; i++){scanf("%d",&pages[i]);}
    FIFO(n,pages);
    LRU(n,pages);
    Optimal(n,pages);
}

