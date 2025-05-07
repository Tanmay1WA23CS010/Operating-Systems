#include <stdio.h>

typedef struct {
    int pid;
    int deadline;
    int burst;
    int remaining;
    int arrival;
} Task;

void sortByDeadline(Task tasks[], int n, int current_time) {
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            int di = tasks[i].arrival + tasks[i].deadline;
            int dj = tasks[j].arrival + tasks[j].deadline;
            if (di > dj) {
                Task temp = tasks[i];
                tasks[i] = tasks[j];
                tasks[j] = temp;
            }
        }
    }
}

void earliestDeadlineFirst(Task tasks[], int n, int sim_time) {
    printf("\nEarliest-Deadline First Scheduling:\n");
    printf("Time\tTask\n");

    for (int i = 0; i < n; i++) {
        tasks[i].remaining = tasks[i].burst;
    }

    for (int time = 0; time < sim_time; time++) {
        for (int i = 0; i < n; i++) {
            if (time == tasks[i].arrival) {
                tasks[i].remaining = tasks[i].burst;
            }
        }

        sortByDeadline(tasks, n, time);

        int scheduled = -1;

        for (int i = 0; i < n; i++) {
            if (tasks[i].arrival <= time && tasks[i].remaining > 0) {
                scheduled = i;
                break;
            }
        }

        if (scheduled != -1) {
            tasks[scheduled].remaining--;
            printf("%d\tT%d\n", time, tasks[scheduled].pid);
        } else {
            printf("%d\tIdle\n", time);
        }
    }
}

int main() {
    int n, sim_time;
    printf("Enter number of tasks: ");
    scanf("%d", &n);

    Task tasks[n];
    for (int i = 0; i < n; i++) {
        tasks[i].pid = i+1;
        printf("Enter arrival time, relative deadline and burst time for task T%d: ", i+1);
        scanf("%d %d %d", &tasks[i].arrival, &tasks[i].deadline, &tasks[i].burst);
    }

    printf("Enter simulation time: ");
    scanf("%d", &sim_time);

    earliestDeadlineFirst(tasks, n, sim_time);

    return 0;
}
