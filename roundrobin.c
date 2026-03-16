#include<stdio.h>

struct Process{
    int pid,at,bt,ct,rt,tat,wt,rtm,iQ,started;
};

int main(){

    int n=4;
    int tq=3;

    struct Process p[4]={{1,0,7},{2,2,4},{3,4,1},{4,5,4}};

    int queue[100],f=0,r=0;
    int t=0,c=0;

    int gantt[100], gtime[100], g=0;

    for(int i=0;i<n;i++){
        p[i].rt=p[i].bt;     // remaining time
        p[i].iQ=0;
        p[i].started=0;
    }

    for(int i=0;i<n;i++){
        if(p[i].at<=t){
            queue[r++]=i;
            p[i].iQ=1;
        }
    }

    while(c<n){

        if(f==r){
            t++;
            continue;
        }

        int idx=queue[f++];

        if(p[idx].started==0){
            p[idx].rtm=t-p[idx].at;   // response time
            p[idx].started=1;
        }

        gantt[g]=p[idx].pid;
        gtime[g++]=t;

        if(p[idx].rt>tq){

            t+=tq;
            p[idx].rt-=tq;

            for(int i=0;i<n;i++){
                if(!p[i].iQ && p[i].rt>0 && p[i].at<=t){
                    queue[r++]=i;
                    p[i].iQ=1;
                }
            }

            queue[r++]=idx;
        }

        else{

            t+=p[idx].rt;
            p[idx].rt=0;
            p[idx].ct=t;
            c++;

            for(int i=0;i<n;i++){
                if(!p[i].iQ && p[i].rt>0 && p[i].at<=t){
                    queue[r++]=i;
                    p[i].iQ=1;
                }
            }
        }
    }

    float totalTAT=0,totalWT=0,totalRT=0;

    for(int i=0;i<n;i++){
        p[i].tat=p[i].ct-p[i].at;
        p[i].wt=p[i].tat-p[i].bt;

        totalTAT+=p[i].tat;
        totalWT+=p[i].wt;
        totalRT+=p[i].rtm;
    }

    printf("Round Robin\n");

    printf("PID AT BT CT TAT WT RT\n");

    for(int i=0;i<n;i++){
        printf("%d   %d  %d  %d  %d   %d  %d\n",
        p[i].pid,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt,p[i].rtm);
    }

    printf("\nAverage TAT = %.2f",totalTAT/n);
    printf("\nAverage WT  = %.2f",totalWT/n);
    printf("\nAverage RT  = %.2f\n",totalRT/n);

    printf("\nGantt Chart:\n\n");

    for(int i=0;i<g;i++)
        printf(" P%d ",gantt[i]);



    return 0;
}
