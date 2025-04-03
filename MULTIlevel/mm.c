#include <stdio.h>

typedef struct {
    int pid, AT, BT, CT, TAT, WT, queue, remaining, completed;
} Process;

void Sort(Process p[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            if (p[i].AT > p[j].AT) {
                Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
        p[i].completed = 0;
        p[i].remaining = p[i].BT;
    }
}

int FCFS(Process p[], int n, int time) {
    for (int i = 0; i < n; i++) {
        if (p[i].queue == 2 && p[i].completed == 0) {
            if (time < p[i].AT) {
                time = p[i].AT;
            }
            p[i].CT = time + p[i].BT;
            p[i].TAT = p[i].CT - p[i].AT;
            p[i].WT = p[i].TAT - p[i].BT;
            p[i].completed = 1;
            time = p[i].CT;
            printf("%d\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].WT, p[i].TAT, p[i].WT);
        }
    }
    return time;
}

int RoundRobin(Process p[], int n, int quantum, int time) {
    int done = 0;
    while (done == 0) {
        done = 1;
        for (int i = 0; i < n; i++) {
            if (p[i].queue == 1 && p[i].completed == 0 && p[i].AT <= time) {
                done = 0;
                if (p[i].remaining > quantum) {
                    time += quantum;
                    p[i].remaining -= quantum;
                } else {
                    time += p[i].remaining;
                    p[i].remaining = 0;
                    p[i].completed = 1;
                    p[i].CT = time;
                    p[i].TAT = p[i].CT - p[i].AT;
                    p[i].WT = p[i].TAT - p[i].BT;
                    printf("%d\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].WT, p[i].TAT, p[i].WT);
                }
            }
        }
    }
    return time;
}

int main() {
    int n, quantum = 2;
    printf("Queue 1 is system process\n");
    printf("Queue 2 is User Process\n");
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].pid = i+1;
        printf("Enter Burst Time, Arrival Time and Queue of P%d: ", i+1);
        scanf("%d %d %d", &p[i].BT, &p[i].AT, &p[i].queue);
    }

    Sort(p, n);

    int time = 0;
    printf("\nProcess\tWaiting Time\tTurn Around Time\tResponse Time\n");

    // Execute Queue 1 (RR) first and get updated time
    time = RoundRobin(p, n, quantum, time);
    // Then execute Queue 2 (FCFS) and get updated time
    time = FCFS(p, n, time);

    // Calculate averages
    float avgWT = 0, avgTAT = 0, avgRT = 0;
    for (int i = 0; i < n; i++) {
        avgWT += p[i].WT;
        avgTAT += p[i].TAT;
        avgRT += p[i].WT; // Response time same as waiting time in this case
    }

    printf("\nAverage Waiting Time: %.2f\n", avgWT/n);
    printf("Average Turn Around Time: %.2f\n", avgTAT/n);
    printf("Average Response Time: %.2f\n", avgRT/n);
    printf("Throughput: %.2f\n", (float)n/p[n-1].CT);

    return 0;
}
