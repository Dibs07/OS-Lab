// Write a c program for implementing Banker’s Algorithm for Deadlock avoidance.
#include <stdio.h>
int max[50][50],alloc[50][50],need[50][50],avail[50],n,r;

void calneed(){
    int i,j;
    for(i=0;i<n;i++){
        for(j=0;j<r;j++){
            need[i][j]=max[i][j]-alloc[i][j];
        }
    }
}

void show(){
    int i,j;
    printf("Process\tMax\tAlloc\tAvailable\tNeed\n");
    for(i=0;i<n;i++){
        printf("P%d\t",i+1);
        for(j=0;j<r;j++){
            printf("%d ",max[i][j]);
        }
        printf("\t");
        for(j=0;j<r;j++){
            printf("%d ",alloc[i][j]);
        }
        printf("\t");
        if(i==0){
            for(j=0;j<r;j++){
                printf("%d ",avail[j]);
            }
        }
        printf("\t");
        for(j=0;j<r;j++){
            printf("%d ",need[i][j]);
        }
        printf("\n");
    }
}

int checksafe(){
    int i,j,work[50],finish[50]={0},safeseq[50],c=0;
    for(i=0;i<r;i++){
        work[i]=avail[i];
    }
    while(c<n){
        int flag=0;
        for(i=0;i<n;i++){
            if(finish[i]==0){
               for(j=0;j<r;j++){
                   if(need[i][j]>work[j]){
                       break;
                   }
               }
               if(j==r){
                   for(int k=0;k<r;k++){
                       work[k]+=alloc[i][k];
                   }
                   safeseq[c++]=i;
                   finish[i]=1;
                   flag=1;
               }
            }
        }
        if(flag==0){
            printf("System is not in safe state\n");
            return 0;
        }
    }
    printf("System is in safe state\n");
    printf("Safe sequence is: ");
    for(i=0;i<n;i++){
        printf("P%d ",safeseq[i]+1);
    }
}

int main(){
    int i,j;
    printf("Enter the number of processes: ");
    scanf("%d",&n);
    printf("Enter the number of resources: ");
    scanf("%d",&r);
    printf("Enter the max matrix: ");
    for(i=0;i<n;i++){
        for(j=0;j<r;j++){
            scanf("%d",&max[i][j]);
        }
    }
    printf("Enter the allocation matrix: ");
    for(i=0;i<n;i++){
        for(j=0;j<r;j++){
            scanf("%d",&alloc[i][j]);
        }
    }
    printf("Enter the available matrix: ");
    for(i=0;i<r;i++){
        scanf("%d",&avail[i]);
    }
    calneed();
    show();
    checksafe();
    return 0;
}