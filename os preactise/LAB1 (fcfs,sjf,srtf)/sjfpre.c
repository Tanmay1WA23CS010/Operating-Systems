#include <stdio.h>
#include <limits.h>

typedef struct {
    int pid, at, bt, ct, tat, wt, rt;
    int remaining_bt;
    int completed;
    int started;
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

void SRTF(Process p[], int n) {
    int time = 0, completed = 0;
    float totalWT = 0, totalTAT = 0;

    for (int i = 0; i < n; i++) {
        p[i].remaining_bt = p[i].bt;
        p[i].completed = 0;
        p[i].started = 0;
    }

    printf("\nGantt Chart:\n");

    while (completed < n) {
        int idx = -1;
        int min_bt = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].at <= time && p[i].remaining_bt > 0) {
                if (p[i].remaining_bt < min_bt) {
                    min_bt = p[i].remaining_bt;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            if (!p[idx].started) {
                p[idx].rt = time - p[idx].at;
                p[idx].started = 1;
            }

            printf("| P%d ", p[idx].pid);
            p[idx].remaining_bt--;
            time++;

            if (p[idx].remaining_bt == 0) {
                p[idx].ct = time;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
                p[idx].completed = 1;
                completed++;
                totalWT += p[idx].wt;
                totalTAT += p[idx].tat;
            }
        } else {
            printf("| IDLE ");
            time++;
        }
    }

    printf("|\n");

    printf("\nP\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].ct,
               p[i].tat, p[i].wt, p[i].rt);
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
        printf("Enter Arrival Time and Burst Time for Process %d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].pid = i + 1;
    }

    sortByArrival(p, n);
    SRTF(p, n);

    return 0;
}
