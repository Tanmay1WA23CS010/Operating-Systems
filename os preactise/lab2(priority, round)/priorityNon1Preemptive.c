#include <stdio.h>

typedef struct {
    int pid, at, bt, pri, ct, tat, wt, rt;
    int completed;
} Process;

void sortByArrival(Process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j + 1].at) {
                Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void priorityNonPreemptive(Process p[], int n) {
    int time = 0, completed = 0;
    float totalWT = 0, totalTAT = 0;

    printf("\nGantt Chart:\n");

    while (completed < n) {
        int idx = -1;
        int highestPriority = 1e9;

        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].at <= time) {
                if (p[i].pri < highestPriority || 
                   (p[i].pri == highestPriority && p[i].at < p[idx].at)) {
                    highestPriority = p[i].pri;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            if (time < p[idx].at)
                time = p[idx].at;

            printf("| P%d ", p[idx].pid);
            p[idx].rt = time - p[idx].at;
            time += p[idx].bt;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            p[idx].completed = 1;
            completed++;
            totalWT += p[idx].wt;
            totalTAT += p[idx].tat;
        } else {
            printf("| IDLE ");
            time++;
        }
    }
    printf("|\n");

    printf("\nP\tAT\tBT\tPRI\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", 
            p[i].pid, p[i].at, p[i].bt, p[i].pri, p[i].ct, p[i].tat, p[i].wt, p[i].rt);
    }

    printf("\nAverage Waiting Time: %.2f", totalWT / n);
    printf("\nAverage Turnaround Time: %.2f\n", totalTAT / n);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process p[n];
    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time, Burst Time and Priority for Process %d: ", i + 1);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].pri);
        p[i].pid = i + 1;
        p[i].completed = 0;
    }

    sortByArrival(p, n);
    priorityNonPreemptive(p, n);

    return 0;
}

            
            
