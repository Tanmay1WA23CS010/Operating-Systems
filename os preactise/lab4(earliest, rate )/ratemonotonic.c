#include <stdio.h>

typedef struct {
    int exec, period, remaining, id;
} Process;

void sort(Process p[], int n) {
    for (int i = 0 ; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].period > p[j + 1].period) {
                Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void Rate(Process p[], int n, int lcm) {
    for (int i = 0; i < n; i++) {
        p[i].remaining = 0;  // Initialize remaining time to 0
    }

    for (int time = 0; time < lcm; time++) {
        // Reset tasks if their period starts
        for (int i = 0; i < n; i++) {
            if (time % p[i].period == 0) {
                p[i].remaining = p[i].exec;
            }
        }

        int selected = -1;
        // Select highest-priority task (shortest period) with remaining time
        for (int i = 0; i < n; i++) {
            if (p[i].remaining > 0) {
                selected = i;
                break;
            }
        }

        if (selected != -1) {
            p[selected].remaining--;
            printf("Time %2d: Task %d\n", time, p[selected].id);
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
        printf("Enter execution time and period for Task %d: ", i + 1);
        scanf("%d %d", &p[i].exec, &p[i].period);
    }

    int lcm;
    printf("Enter simulation time (LCM): ");
    scanf("%d", &lcm);

    sort(p, n);  // Sort by shortest period (highest priority)
    Rate(p, n, lcm);

    return 0;
}
