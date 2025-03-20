#include <stdio.h>

typedef struct Process {
    int AT, BT, PT, CT, TAT, WT, RT, remainingBT, finished;
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

void PriorityPreemptive(Process p[], int n) {
    int time = 0, completed = 0, totalTAT = 0, totalWT = 0;
    int flag = 0; // To keep track if there is any process executing

    while (completed < n) {
        int ind = -1;
        int highestP = 9999;

        for (int i = 0; i < n; i++) {
            if (p[i].AT <= time && p[i].remainingBT > 0) {
                if (p[i].PT < highestP) {
                    highestP = p[i].PT;
                    ind = i;
                }
            }
        }

        if (ind != -1) {
            if (flag == 0) {
                p[ind].RT = time - p[ind].AT;
            }

            p[ind].remainingBT--;

            if (p[ind].remainingBT == 0) {
                p[ind].CT = time + 1;
                p[ind].TAT = p[ind].CT - p[ind].AT;
                p[ind].WT = p[ind].TAT - p[ind].BT;
                
                totalTAT += p[ind].TAT;
                totalWT += p[ind].WT;
                completed++;
            }

            flag = 1;
        }

        time++;
    }

    printf("Process\tAT\tBT\tPT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, p[i].AT, p[i].BT, p[i].PT, p[i].CT, p[i].TAT, p[i].WT, p[i].RT);
    }

    printf("\nAverage Turnaround Time: %.2f\n", (float)totalTAT / n);
    printf("Average Waiting Time: %.2f\n", (float)totalWT / n);
}

int main() {
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process p[n];

    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time, Burst Time, and Priority for Process %d: ", i + 1);
        scanf("%d %d %d", &p[i].AT, &p[i].BT, &p[i].PT);
        p[i].remainingBT = p[i].BT;
        p[i].finished = 0;
    }

    Sort(p, n);

    PriorityPreemptive(p, n);

    return 0;
}
