#include <stdio.h>

typedef struct Process {
    int AT, BT, CT, TAT, WT, RT, remainingBT, addedToQueue;
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
    int queue[100], front = 0, rear = 0;

    // Initialize all processes
    for (int i = 0; i < n; i++) {
        p[i].remainingBT = p[i].BT;
        p[i].addedToQueue = 0;  // Prevents duplicate insertion
        p[i].RT = -1;           // Used to calculate response time
    }

    // Add the first arriving process to the queue
    queue[rear++] = 0;
    p[0].addedToQueue = 1;
printf("GANTT CHART");
    while (completed < n) {
        // If queue is not empty
        if (front < rear) {
            int ind = queue[front++];

            // Set response time only once
            if (p[ind].RT == -1) {
                p[ind].RT = time - p[ind].AT;
            }

            if (p[ind].remainingBT > quantum) {
                time += quantum;
                p[ind].remainingBT -= quantum;
                for(int i=0; i< quantum; i++){
                    printf("P%d |", ind);
                }
            } else {
                time += p[ind].remainingBT;
                p[ind].remainingBT = 0;
                p[ind].CT = time;
                p[ind].TAT = p[ind].CT - p[ind].AT;
                p[ind].WT = p[ind].TAT - p[ind].BT;
                completed++;
                for(int i=0; i< p[ind].remainingBT; i++){
                    printf("P%d |", ind);
                }
            }

            // Enqueue any newly arrived processes
            for (int i = 0; i < n; i++) {
                if (p[i].AT <= time && p[i].addedToQueue == 0) {
                    queue[rear++] = i;
                    p[i].addedToQueue = 1;
                }
            }

            // Re-add current process if it’s not done
            if (p[ind].remainingBT > 0) {
                queue[rear++] = ind;
            }

        } else {
            // If no process is in queue, advance time
            time++;
            // Check for any new arrivals
            for (int i = 0; i < n; i++) {
                if (p[i].AT == time && p[i].addedToQueue == 0) {
                    queue[rear++] = i;
                    p[i].addedToQueue = 1;
                }
            }
        }
    }

    // Print results
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1, p[i].AT, p[i].BT, p[i].CT,
               p[i].TAT, p[i].WT, p[i].RT);
        totalTAT += p[i].TAT;
        totalWT += p[i].WT;
    }

    printf("\nAverage Turnaround Time: %.2f", (float)totalTAT / n);
    printf("\nAverage Waiting Time: %.2f\n", (float)totalWT / n);
}

int main() {
    int n, quantum;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process p[n];
    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for Process %d: ", i + 1);
        scanf("%d %d", &p[i].AT, &p[i].BT);
    }

    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

    Sort(p, n); // Sort by Arrival Time
    RoundRobin(p, n, quantum);

    return 0;
}
