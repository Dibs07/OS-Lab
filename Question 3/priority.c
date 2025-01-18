//  Write a c program to implement PRIORITY scheduling algorithm. (Assume all the processes arrive at time zero)
#include <stdio.h>

int main(){
    int n;
    printf("Enter the number of processes: ");
    scanf("%d",&n);
    int pr[n],bt[n],wt[n],tat[n],pri[n];
    for(int i=0;i<n;i++){
        printf("Enter the burst time of process %d: ",i+1);
        scanf("%d",&bt[i]);
        printf("Enter the priority of process %d: ",i+1);
        scanf("%d",&pri[i]);
        pr[i]=i+1;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n-i-1;j++){
            if(pri[j]>pri[j+1]){
                int temp=bt[j];
                bt[j]=bt[j+1];
                bt[j+1]=temp;
                temp=pr[j];
                pr[j]=pr[j+1];
                pr[j+1]=temp;
                temp=pri[j];
                pri[j]=pri[j+1];
                pri[j+1]=temp;
            }
        }
    }
    tat[0]=bt[0];
    wt[0]=0;
    int total_wt=0,total_tat=bt[0];
    for(int i=1;i<n;i++){
        tat[i]=tat[i-1]+bt[i];
        wt[i]=tat[i]-bt[i];
        total_wt+=wt[i];
        total_tat+=tat[i];
    }
    printf("Process\tPriority\tBurst Time\tTurn Around Time\tWaiting Time\n");
    for(int i=0;i<n;i++){
        printf("%d\t\t%d\t%d\t\t%d\t\t%d\n",pr[i],pri[i],bt[i],tat[i],wt[i]);
    }
    printf("Average Waiting Time: %.2f\n",(float)total_wt/n);
    printf("Average Turn Around Time: %.2f\n",(float)total_tat/n);
}