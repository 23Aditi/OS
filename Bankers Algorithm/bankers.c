#include <stdio.h>
#include <stdlib.h>

void input(int n , int m, int allocation[n][m]){
    for(int i = 0 ; i < n ; i++){
        printf("Enter for prcess %d\n",i);
        for(int j = 0 ; j < m ; j++){
            printf("Enter for resouce %d of process %d\n",j,i);
            scanf("%d",&allocation[i][j]);
        }
    }
}

int main(){
    int n, m;
    // n -> no of processes
    // m -> no of resource type availabel
    printf("Enter no of processes followed by no of resouces available : \n");
    scanf("%d %d",&n,&m);
    int max[n][m];
    printf("\t\tMAX MATRIX\n");
    input(n,m,max);
    int allocation[n][m];
    printf("\t\tALLOCATION MATRIX\n");
    input(n,m,allocation);
    int available[m];
    printf("\t\tAVAILABLE MATRIX\n");
    for(int i = 0 ; i < m ; i++){
        scanf("%d",available[i]);
    }
    int need[n][m];
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < m ; j++){
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

}
