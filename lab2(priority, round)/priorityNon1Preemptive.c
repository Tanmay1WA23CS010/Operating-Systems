#include <stdio.h>

typedef struct Process {
    int AT, BT, PT, CT, TAT, WT, RT, finished;
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

void Priority(Process p[], int n) {
    int time = 0, completed = 0, totalTAT = 0, totalWT = 0;
    
    while (completed < n) {
        int ind = -1;
        int highestP = 9999;
        
        for (int i = 0; i < n; i++) {
            if (p[i].AT <= time && p[i].finished == 0) {
                if (p[i].PT < highestP) {
                    highestP = p[i].PT;
                    ind = i;
                }
            }
        }

        if (ind != -1) {
            p[ind].CT = time + p[ind].BT;
            p[ind].TAT = p[ind].CT - p[ind].AT;
            p[ind].WT = p[ind].TAT - p[ind].BT;
            p[ind].RT = time - p[ind].AT;
            
            totalTAT += p[ind].TAT;
            totalWT += p[ind].WT;
            
            p[ind].finished = 1;
            time = p[ind].CT;
            completed++;
        } else {
            time++;
        }
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
        p[i].finished = 0;
    }

    Sort(p, n);

    Priority(p, n);

    return 0;
}
