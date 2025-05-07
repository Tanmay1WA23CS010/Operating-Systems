#include <stdio.h>

// Define the Process structure
typedef struct {
    int id;       // Process ID
    int AT;       // Arrival Time
    int BT;       // Burst Time
    int priority; // Priority (lower value means higher priority)
    int TAT;      // Turnaround Time
    int CT;       // Completion Time
    int WT;       // Waiting Time
} Process;

// Function to sort processes by arrival time (AT)
void sorted(Process p[], int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (p[j].AT > p[j + 1].AT) {
                // Swap processes if they are out of order
                Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

// Function to implement Non-Preemptive Priority Scheduling
void PriorityNonPreemptive(Process p[], int n) {
    int TotalTAT = 0, TotalWT = 0; // Total Turnaround Time and Waiting Time
    int time = 0; // Current time
    int completed = 0; // Number of completed processes
    int isCompleted[n]; // Array to track completed processes

    // Initialize all processes as not completed
    for (int i = 0; i < n; i++) {
        isCompleted[i] = 0;
    }

    // Execute until all processes are completed
    while (completed < n) {
        int highestPriorityIndex = -1;
        int highestPriority = 9999; // Initialize to a large value

        // Find the process with the highest priority among arrived processes
        for (int i = 0; i < n; i++) {
            if (p[i].AT <= time && !isCompleted[i] && p[i].priority < highestPriority) {
                highestPriority = p[i].priority;
                highestPriorityIndex = i;
            }
        }

        if (highestPriorityIndex != -1) {
            // Execute the process with the highest priority
            time += p[highestPriorityIndex].BT;
            p[highestPriorityIndex].CT = time; // Completion Time
            p[highestPriorityIndex].TAT = p[highestPriorityIndex].CT - p[highestPriorityIndex].AT; // Turnaround Time
            p[highestPriorityIndex].WT = p[highestPriorityIndex].TAT - p[highestPriorityIndex].BT; // Waiting Time

            // Update totals
            TotalTAT += p[highestPriorityIndex].TAT;
            TotalWT += p[highestPriorityIndex].WT;

            // Mark the process as completed
            isCompleted[highestPriorityIndex] = 1;
            completed++;
        } else {
            // If no process is available, increment time
            time++;
        }
    }

    // Calculate average TAT and WT
    float avgTAT = (float)TotalTAT / n;
    float avgWT = (float)TotalWT / n;

    // Print the results
    printf("Average TurnAround Time: %.2f\n", avgTAT);
    printf("Average Waiting Time: %.2f\n", avgWT);
}

int main() {
    int n; // Number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process p[n]; // Array of processes

    // Input arrival time, burst time, and priority for each process
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1; // Assign process ID
        printf("Enter arrival time, burst time, and priority for process %d: ", i + 1);
        scanf("%d %d %d", &p[i].AT, &p[i].BT, &p[i].priority);
    }

    // Sort processes by arrival time
    sorted(p, n);

    // Execute Non-Preemptive Priority Scheduling
    PriorityNonPreemptive(p, n);

    return 0;
}
