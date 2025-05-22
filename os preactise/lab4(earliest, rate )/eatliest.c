#include <stdio.h>

// Define the structure for a periodic real-time task
typedef struct {
    int exec;          // Execution time of the task
    int period;        // Period of the task
    int remaining;     // Remaining execution time of the current job
    int deadline;      // Relative deadline (from release)
    int id;            // Task ID
    int release_time;  // When the current job was released
    int abs_deadline;  // Absolute deadline (release_time + deadline)
} Process;

// Sort tasks based on earliest absolute deadline (EDF principle)
void sort_by_deadline(Process p[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            // Only compare tasks with remaining execution
            if (p[j].remaining > 0 && p[j + 1].remaining > 0) {
                // Swap if current task's deadline is later
                if (p[j].abs_deadline > p[j + 1].abs_deadline) {
                    Process temp = p[j];
                    p[j] = p[j + 1];
                    p[j + 1] = temp;
                }
            }
            // Push tasks with 0 remaining execution to the end
            else if (p[j].remaining == 0 && p[j + 1].remaining > 0) {
                Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

// EDF scheduling simulation for time units from 0 to LCM
void EDF(Process p[], int n, int lcm) {
    // Initialize remaining time and deadline for all tasks
    for (int i = 0; i < n; i++) {
        p[i].remaining = 0;
        p[i].release_time = -1;
        p[i].abs_deadline = -1;
    }

    for (int time = 0; time < lcm; time++) {
        // Check for job releases based on period
        for (int i = 0; i < n; i++) {
            if (time % p[i].period == 0) {
                p[i].remaining = p[i].exec;                      // Reset remaining time
                p[i].release_time = time;                        // Set new release time
                p[i].abs_deadline = time + p[i].deadline;        // Compute new absolute deadline
            }
        }

        // Sort all tasks according to earliest deadline first
        sort_by_deadline(p, n);

        // Check for any missed deadlines before executing any task
        for (int i = 0; i < n; i++) {
            // If deadline is missed and task is not finished
            if (p[i].remaining > 0 && time >= p[i].abs_deadline) {
                printf("Time %2d: Task %d MISSED deadline (Deadline: %d)\n", 
                       time, p[i].id, p[i].abs_deadline);
                p[i].remaining = 0;  // Drop the task/job
            }
        }

        // Select the first task with remaining execution time (earliest deadline)
        int selected = -1;
        for (int i = 0; i < n; i++) {
            if (p[i].remaining > 0) {
                selected = i;
                break;
            }
        }

        // Execute the selected task, or print IDLE if none are available
        if (selected != -1) {
            p[selected].remaining--;
            printf("Time %2d: Running Task %d (Remaining: %d, Deadline: %d)\n", 
                   time, p[selected].id, p[selected].remaining, p[selected].abs_deadline);
        } else {
            printf("Time %2d: IDLE\n", time);
        }
    }
}

int main() {
    int n;
    printf("Enter number of tasks: ");
    scanf("%d", &n);

    Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter execution time, period, and deadline for Task %d: ", i + 1);
        scanf("%d %d %d", &p[i].exec, &p[i].period, &p[i].deadline);
    }

    int lcm;
    printf("Enter simulation time (LCM): ");
    scanf("%d", &lcm);

    // Start EDF scheduler
    EDF(p, n, lcm);

    return 0;
}
