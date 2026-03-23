#include <stdio.h>

#define MAX_TASKS 10
#define MAX_TIME 20

typedef struct {
    int C;
    int P;
    int remaining_time;
    int next_arrival;
} Task;

void sort(Task tasks[], int n) {
    Task temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (tasks[i].P > tasks[j].P) {
                temp = tasks[i];
                tasks[i] = tasks[j];
                tasks[j] = temp;
            }
        }
    }
}

int main() {
    int n;
    Task tasks[MAX_TASKS];

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter execution time and period for Task %d: ", i + 1);
        scanf("%d %d", &tasks[i].C, &tasks[i].P);
        tasks[i].remaining_time = 0;
        tasks[i].next_arrival = 0;
    }

    sort(tasks, n);

    int time = 0;
    int timeline[MAX_TIME];

    printf("\nExecution Timeline:\n");

    while (time < MAX_TIME) {

        for (int i = 0; i < n; i++) {
            if (time == tasks[i].next_arrival) {
                tasks[i].remaining_time = tasks[i].C;
                tasks[i].next_arrival += tasks[i].P;
            }
        }

        int current_task = -1;
        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining_time > 0) {
                current_task = i;
                break;
            }
        }

        if (current_task != -1) {
            printf("Time %d: Task %d running\n", time, current_task + 1);
            tasks[current_task].remaining_time--;
            timeline[time] = current_task + 1;
        } else {
            printf("Time %d: CPU Idle\n", time);
            timeline[time] = 0;
        }

        for (int i = 0; i < n; i++) {
            if (time > tasks[i].next_arrival - tasks[i].P &&
                tasks[i].remaining_time > 0) {
                printf("Deadline Missed by Task %d at time %d\n", i + 1, time);
            }
        }

        time++;
    }

    printf("\nGantt Chart:\n");

    for (int i = 0; i < MAX_TIME; i++) {
        printf("----");
    }
    printf("-\n|");

    for (int i = 0; i < MAX_TIME; i++) {
        if (timeline[i] == 0)
            printf(" I |");
        else
            printf("T%d |", timeline[i]);
    }

    printf("\n");

    for (int i = 0; i < MAX_TIME; i++) {
        printf("----");
    }
    printf("-\n");

    for (int i = 0; i <= MAX_TIME; i++) {
        printf("%-4d", i);
    }
    printf("\n");

    return 0;
}
