// Write a c program to implement ROUND ROBIN scheduling algorithm. (Assume all the processes arrive at time zero)
#include <stdio.h>

int main(){
    int n;
    printf("Enter the number of processes: ");
    scanf("%d",&n);
    int pr[n],bt[n],rem_bt[n],wt[n],tat[n];
    
    for(int i=0;i<n;i++){
        printf("Enter the burst time of process %d: ",i+1);
        scanf("%d",&bt[i]);
        rem_bt[i]=bt[i];
        pr[i]=i+1;
    }
    int tq;
    printf("Enter the time quantum: ");
    scanf("%d",&tq);
    int total_wt=0,total_tat=0;
    int flag=0;
    while(flag!=n){
        for(int i=0;i<n;i++){
            if(rem_bt[i]>0){
                rem_bt[i]-=tq;
                if(rem_bt[i]<=0){
                    flag++;
                    total_tat+=rem_bt[i]+tq;
                    tat[i]=total_tat;
                    wt[i]=tat[i]-bt[i];
                    total_wt+=wt[i];
                    rem_bt[i]=0;
                }
                else{
                    total_tat+=tq;
                }
            }
            else{
                continue;
            }
        }
        
    }
    printf("Process\tBurst Time\tTurn Around Time\tWaiting Time\n");
    for(int i=0;i<n;i++){
        printf("%d\t%d\t\t%d\t\t\t\t%d\n",pr[i],bt[i],tat[i],wt[i]);
    }
    printf("Average Waiting Time: %.2f\n",(float)total_wt/n);
    printf("Average Turn Around Time: %.2f\n",(float)total_tat/n);
}