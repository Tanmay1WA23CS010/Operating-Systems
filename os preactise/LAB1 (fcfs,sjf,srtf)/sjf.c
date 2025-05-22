#include <stdio.h>
#include <limits.h>

typedef struct {
    int at, bt, tat, wt, ct;
    int completed;
    int pid;
} Process;

void sortByArrival(Process p[], int n) {
    Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (p[j].at > p[j + 1].at) {
                temp      = p[j];
                p[j]      = p[j + 1];
                p[j + 1]  = temp;
            }
        }
    }
}

void SJFScheduling(Process p[], int n) {
    int completed = 0, time = 0;
    int totalTAT = 0, totalWT = 0;

    // mark all as not completed
    for (int i = 0; i < n; i++) {
        p[i].completed = 0;
    }

    printf("\nGantt Chart:\n");
    while (completed < n) {
        int idx    = -1;
        int min_bt = INT_MAX;

        // find the next shortest job that's arrived
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && !p[i].completed) {
                if (p[i].bt < min_bt ||
                    (p[i].bt == min_bt && (idx == -1 || p[i].at < p[idx].at))) {
                        
                    min_bt = p[i].bt;
                    idx    = i;
                }
            }
        }

        if (idx != -1) {
            // schedule process idx
            for(int i=0; i< p[idx].bt; i++){
                printf("| P%d ", p[idx].pid);
            }
            

            p[idx].ct        = time + p[idx].bt;
            p[idx].tat       = p[idx].ct - p[idx].at;
            p[idx].wt        = p[idx].tat - p[idx].bt;
            p[idx].completed = 1;

            // accumulate for averages
            totalTAT += p[idx].tat;
            totalWT  += p[idx].wt;

            time      = p[idx].ct;
            completed++;
        } else {
            // no process ready → idle
            printf("| idle ");
            time++;
        }
    }
    printf("|\n");

    // Final Table
    printf("\nP\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt,
               p[i].ct,  p[i].tat, p[i].wt);
    }

    // Compute and print averages
    double avgTAT = (double)totalTAT / n;
    double avgWT  = (double)totalWT  / n;
    printf("\nAverage Turnaround Time = %.2f\n", avgTAT);
    printf("Average Waiting Time    = %.2f\n", avgWT);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process p[n];
    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for Process %d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].pid = i + 1;
    }

    sortByArrival(p, n);
    SJFScheduling(p, n);

    return 0;
}
