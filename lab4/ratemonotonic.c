#include <stdio.h>

#define MAX_TASKS 10

typedef struct {
    int id;
    int execution_time;
    int period;
    int remaining_time;
} Task;

void rateMonotonicScheduling(Task tasks[], int n, int hyperPeriod) {
    printf("\nRate-Monotonic Scheduling:\n");
    printf("Time\tExecuting Task\n");

    for (int time = 0; time < hyperPeriod; time++) {
        int selectedTask = -1;

        // Select the highest-priority task (smallest period) that is ready
        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining_time > 0 && (selectedTask == -1 || tasks[i].period < tasks[selectedTask].period)) {
                selectedTask = i;
            }
        }

        if (selectedTask != -1) {
            tasks[selectedTask].remaining_time--;
            printf("%d\tTask %d\n", time, tasks[selectedTask].id);
        } else {
            printf("%d\tIDLE\n", time);
        }

        // Reset remaining execution time for tasks at the beginning of their period
        for (int i = 0; i < n; i++) {
            if ((time + 1) % tasks[i].period == 0) {
                tasks[i].remaining_time = tasks[i].execution_time;
            }
        }
    }
}

int main() {
    int n, hyperPeriod = 1;
    Task tasks[MAX_TASKS];

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter execution time for Task %d: ", i + 1);
        scanf("%d", &tasks[i].execution_time);

        printf("Enter period for Task %d: ", i + 1);
        scanf("%d", &tasks[i].period);

        tasks[i].id = i + 1;
        tasks[i].remaining_time = tasks[i].execution_time;

        // Calculate the hyper-period (LCM of all task periods)
        hyperPeriod *= tasks[i].period;
    }

    rateMonotonicScheduling(tasks, n, hyperPeriod);

    return 0;
}
