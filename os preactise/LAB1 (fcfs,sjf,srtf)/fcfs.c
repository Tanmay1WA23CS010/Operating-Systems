#include <stdio.h>

typedef struct {
    int id, AT, BT, TAT, RT, CT, WT;
} Process;

void sorted(Process p[], int n) {
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < n-i-1; j++) {
            if(p[j].AT > p[j+1].AT) {
                Process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
}

void FCFS(Process p[], int n) {
    int TotalTAT = 0, TotalWT = 0, time = 0;

    printf("\nGantt Chart:\n|");
    for(int i = 0; i < n; i++) {
        if(time < p[i].AT)
            time = p[i].AT;

        p[i].RT = time - p[i].AT;
        p[i].CT = time + p[i].BT;
        p[i].TAT = p[i].CT - p[i].AT;
        p[i].WT = p[i].TAT - p[i].BT;
        TotalTAT += p[i].TAT;
        TotalWT += p[i].WT;

        // Gantt Chart Process Block
        for(int k = 0; k< p[i].BT; k++){
            printf(" P%d |", p[i].id);
        }
        
        time = p[i].CT;
    }

    float avgTAT = (float)TotalTAT / n;
    float avgWT = (float)TotalWT / n;

    printf("\n\nFinal Table:\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", 
            p[i].id, p[i].AT, p[i].BT, p[i].CT, p[i].TAT, p[i].WT);
    }

    printf("\nAverage TurnAround Time: %.2f\n", avgTAT);
    printf("Average Waiting Time: %.2f\n", avgWT);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    Process p[n];

    for(int i = 0; i < n; i++) {
        p[i].id = i+1;
        printf("Enter Arrival Time and Burst Time for Process %d: ", i+1);
        scanf("%d %d", &p[i].AT, &p[i].BT);
    }

    sorted(p, n);
    FCFS(p, n);

    return 0;
}
