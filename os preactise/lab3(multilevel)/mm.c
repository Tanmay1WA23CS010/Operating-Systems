#include <stdio.h>

// Define the structure for a process
typedef struct {
    int pid;        // Process ID
    int AT;         // Arrival Time
    int BT;         // Burst Time
    int CT;         // Completion Time
    int TAT;        // Turn Around Time
    int WT;         // Waiting Time
    int queue;      // Queue number (1 for system, 2 for user)
    int remaining;  // Remaining burst time (for RR)
    int completed;  // Completion status (0 for not completed, 1 for completed)
} Process;

// Sort processes based on Arrival Time
void Sort(Process p[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].AT > p[j].AT) {
                Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
        // Initialize additional fields
        p[i].completed = 0;
        p[i].remaining = p[i].BT;
    }
}

// Round Robin scheduling for Queue 1 (System processes)
int RoundRobin(Process p[], int n, int quantum, int time) {
    int queue[n];            // Ready queue
    int front = 0, rear = 0; // Queue pointers

    // Initial enqueue of available Queue 1 processes
    for (int i = 0; i < n; i++) {
        if (p[i].queue == 1 && p[i].AT <= time && p[i].completed == 0) {
            queue[rear++] = i;
        }
    }

    while (front < rear) {
        int i = queue[front++];  // Dequeue a process

        // Execute the process for one time slice
        if (p[i].remaining > quantum) {
            time += quantum;
            p[i].remaining -= quantum;
        } else {
            time += p[i].remaining;
            p[i].remaining = 0;
            p[i].CT = time;
            p[i].TAT = p[i].CT - p[i].AT;
            p[i].WT = p[i].TAT - p[i].BT;
            p[i].completed = 1;
        }

        // Enqueue any new arrivals
        for (int j = 0; j < n; j++) {
            if (p[j].queue == 1 && p[j].AT <= time && p[j].completed == 0) {
                int found = 0;
                for (int k = front; k < rear; k++) {
                    if (queue[k] == j) {
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    queue[rear++] = j;
                }
            }
        }

        // If not finished, re-enqueue the current process
        if (p[i].remaining > 0) {
            queue[rear++] = i;
        }
    }

    return time; // Return updated time
}

// First Come First Serve scheduling for Queue 2 (User processes)
int FCFS(Process p[], int n, int time) {
    for (int i = 0; i < n; i++) {
        if (p[i].queue == 2 && p[i].completed == 0) {
            if (time < p[i].AT) {
                time = p[i].AT; // CPU waits if no process has arrived yet
            }
            time += p[i].BT;
            p[i].CT = time;
            p[i].TAT = p[i].CT - p[i].AT;
            p[i].WT = p[i].TAT - p[i].BT;
            p[i].completed = 1;
        }
    }
    return time; // Return updated time
}

int main() {
    int n, quantum = 2;

    printf("Queue 1 is system process\n");
    printf("Queue 2 is User process\n");
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Burst Time, Arrival Time and Queue (1 for system, 2 for user) of P%d: ", i + 1);
        scanf("%d %d %d", &p[i].BT, &p[i].AT, &p[i].queue);
    }

    Sort(p, n); // Sort processes based on Arrival Time

    int time = 0;
    time = RoundRobin(p, n, quantum, time); // Handle system processes (Queue 1)
    time = FCFS(p, n, time);                // Handle user processes (Queue 2)

    // Display process details
    printf("\nProcess\tWaiting Time\tTurn Around Time\tResponse Time\n");
    float avgWT = 0, avgTAT = 0, avgRT = 0;
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t\t%d\n", p[i].pid, p[i].WT, p[i].TAT, p[i].WT);
        avgWT += p[i].WT;
        avgTAT += p[i].TAT;
        avgRT += p[i].WT; // Response Time = Waiting Time
    }

    // Print averages and throughput
    printf("\nAverage Waiting Time: %.2f\n", avgWT / n);
    printf("Average Turn Around Time: %.2f\n", avgTAT / n);
    printf("Average Response Time: %.2f\n", avgRT / n);
    printf("Throughput: %.2f\n", (float)n / p[n - 1].CT);

    return 0;
}
