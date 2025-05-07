#include <stdio.h>
#include <stdlib.h>

typedef struct Process {
    int AT, BT, CT, TAT, WT, RT, remainingBT, finished;
} Process;

void Sort(Process p[], int n) {
    Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].AT > p[j].AT) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

void RoundRobin(Process p[], int n, int quantum) {
    int time = 0, completed = 0, totalTAT = 0, totalWT = 0;

    // Queue for processes that need to be executed
    int queue[n], front = 0, rear = 0;
    
    for (int i = 0; i < n; i++) {
        p[i].remainingBT = p[i].BT;
        p[i].finished = 0;
    }

    while (completed < n) {
        int flag = 0;

        // Add processes to queue if they have arrived
        for (int i = 0; i < n; i++) {
            if (p[i].AT <= time && p[i].finished == 0) {
                queue[rear++] = i;
                p[i].finished = 1; // Mark process as added to queue
            }
        }

        // Process execution
        if (front < rear) {
            int ind = queue[front++];
            if (p[ind].remainingBT > quantum) {
                time += quantum;
                p[ind].remainingBT -= quantum;
                queue[rear++] = ind; // Put back the process in the queue
            } else {
                time += p[ind].remainingBT;
                p[ind].remainingBT = 0;
                p[ind].CT = time;
                p[ind].TAT = p[ind].CT - p[ind].AT;
                p[ind].WT = p[ind].TAT - p[ind].BT;

                totalTAT += p[ind].TAT;
                totalWT += p[ind].WT;
                completed++;
            }
            flag = 1;
        }

        // If no process is executing, increment time
        if (flag == 0) {
            time++;
        }
    }

    // Printing the results
    printf("Process\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, p[i].AT, p[i].BT, p[i].CT, p[i].TAT, p[i].WT, p[i].RT);
    }

    printf("\nAverage Turnaround Time: %.2f\n", (float)totalTAT / n);
    printf("Average Waiting Time: %.2f\n", (float)totalWT / n);
}

int main() {
    int n, quantum;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process p[n];

    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for Process %d: ", i + 1);
        scanf("%d %d", &p[i].AT, &p[i].BT);
        p[i].remainingBT = p[i].BT;
    }

    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

    Sort(p, n);
    RoundRobin(p, n, quantum);

    return 0;
}
