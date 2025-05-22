#include <stdio.h>
#include <limits.h>

typedef struct {
    int pid, at, bt, pri, ct, tat, wt, rt;
    int remainingbt, completed, started;
} Process;

void sort(Process p[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j + 1].at) {
                Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void Priority(Process p[], int n) {
    int completed = 0;
    int time = 0;
    float totaltat = 0, totalwt = 0;

    for (int i = 0; i < n; i++) {
        p[i].remainingbt = p[i].bt;
        p[i].completed = 0;
        p[i].started = 0;
    }

    printf("\nGantt Chart:\n");

    while (completed < n) {
        int idx = -1;
        int highest_priority = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && !p[i].completed && p[i].remainingbt > 0) {
                if (p[i].pri < highest_priority) {
                    highest_priority = p[i].pri;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            if (p[idx].started == 0) {
                p[idx].rt = time - p[idx].at;
                p[idx].started = 1;
            }

            printf("P%d ", p[idx].pid);
            p[idx].remainingbt--;
            time++;

            if (p[idx].remainingbt == 0) {
                p[idx].ct = time;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
                p[idx].completed = 1;
                completed++;
                totaltat += p[idx].tat;
                totalwt += p[idx].wt;
            }
        } else {
            printf("IDLE ");
            time++;
        }
    }

    // Output Table
    printf("\n\nPID\tAT\tBT\tPRI\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].pri,
               p[i].ct, p[i].tat, p[i].wt, p[i].rt);
    }

    printf("\nAverage Turnaround Time: %.2f\n", totaltat / n);
    printf("Average Waiting Time: %.2f\n", totalwt / n);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process p[n];
    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time, Burst Time, Priority for Process %d: ", i + 1);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].pri);
        p[i].pid = i + 1;
    }

    sort(p, n);
    Priority(p, n);

    return 0;
}
