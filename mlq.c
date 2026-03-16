#include <stdio.h>

struct Process {
    int pid,at,bt,type,ct,tat,wt,rt;
};

int main() {

    int n = 6;

    struct Process p[6] = {
        {1, 0, 4, 0},
        {2, 1, 3, 1},
        {3, 2, 5, 0},
        {4, 3, 2, 1},
        {5, 4, 6, 1},
        {6, 5, 3, 0}
    };

    int sysQ[6], sysCount = 0;
    int usrQ[6], usrCount = 0;

    for (int i = 0; i < n; i++) {
        if (p[i].type == 0)
            sysQ[sysCount++] = i;
        else
            usrQ[usrCount++] = i;
    }

    for (int i = 0; i < sysCount - 1; i++) {
        for (int j = 0; j < sysCount - i - 1; j++) {
            if (p[sysQ[j]].at > p[sysQ[j+1]].at) {
                int tmp    = sysQ[j];
                sysQ[j]   = sysQ[j+1];
                sysQ[j+1] = tmp;
            }
        }
    }
    for (int i = 0; i < usrCount - 1; i++) {
        for (int j = 0; j < usrCount - i - 1; j++) {
            if (p[usrQ[j]].at > p[usrQ[j+1]].at) {
                int tmp    = usrQ[j];
                usrQ[j]   = usrQ[j+1];
                usrQ[j+1] = tmp;
            }
        }
    }

    int time = 0;
    for (int i = 0; i < sysCount; i++) {
        int idx = sysQ[i];
        if (time < p[idx].at)
            time = p[idx].at;
        p[idx].rt  = time - p[idx].at;
        time      += p[idx].bt;
        p[idx].ct  = time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt  = p[idx].tat - p[idx].bt;
    }

    for (int i = 0; i < usrCount; i++) {
        int idx = usrQ[i];
        if (time < p[idx].at)
            time = p[idx].at;
        p[idx].rt  = time - p[idx].at;
        time      += p[idx].bt;
        p[idx].ct  = time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt  = p[idx].tat - p[idx].bt;
    }

    float totalTAT = 0, totalWT = 0, totalRT = 0;

    printf("Multilevel Queue Scheduling\n");
    printf("%-5s %-5s %-5s %-6s %-5s %-5s %-5s %-5s\n",
           "PID", "AT", "BT", "TYPE", "CT", "TAT", "WT", "RT");

    printf("System Queue\n");
    for (int i = 0; i < sysCount; i++) {
        int idx = sysQ[i];.
        totalTAT += p[idx].tat;
        totalWT  += p[idx].wt;
        totalRT  += p[idx].rt;
        printf("%-5d %-5d %-5d %-6d %-5d %-5d %-5d %-5d\n",
               p[idx].pid, p[idx].at, p[idx].bt, p[idx].type,
               p[idx].ct, p[idx].tat, p[idx].wt, p[idx].rt);
    }

    printf("User Queue\n");
    for (int i = 0; i < usrCount; i++) {
        int idx = usrQ[i];
        totalTAT += p[idx].tat;
        totalWT  += p[idx].wt;
        totalRT  += p[idx].rt;
        printf("%-5d %-5d %-5d %-6d %-5d %-5d %-5d %-5d\n",
               p[idx].pid, p[idx].at, p[idx].bt, p[idx].type,
               p[idx].ct, p[idx].tat, p[idx].wt, p[idx].rt);
    }

    printf("\nAverage TAT = %.2f", totalTAT / n);
    printf("\nAverage WT  = %.2f", totalWT / n);
    printf("\nAverage RT  = %.2f\n", totalRT / n);

    return 0;
}
