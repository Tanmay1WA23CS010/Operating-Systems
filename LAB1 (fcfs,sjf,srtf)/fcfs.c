#include<stdio.h>
typedef struct{
    int id, AT, BT, TAT, RT, CT, WT;
}Process;

void sorted(Process p[], int n)
{
    int i, j;
    for(i = 0; i < n-1; i++)
    {
        for(j = 0; j < n-i-1; j++)
        {
            if(p[j].AT > p[j+1].AT)
            {
                Process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
}

void FCFS(Process p[], int n)
{
    int TotalTAT = 0, TotalWT = 0, time = 0, i;
    for(i = 0; i < n; i++)
    {
        if(time < p[i].AT)
        {
            time = p[i].AT;
        }
        p[i].CT = time + p[i].BT;
        p[i].TAT = p[i].CT - p[i].AT;
        p[i].WT = p[i].TAT - p[i].BT;
        TotalTAT += p[i].TAT;
        TotalWT += p[i].WT;
        time = p[i].CT;

    }
    float avgTAT = (float)TotalTAT / n;
    float avgWT = (float)TotalWT / n;
    printf("Average TurnAround Time: %f\n", avgTAT);
    printf("Average Waiting Time: %f\n", avgWT);
}

int main()
{
    int n, i;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    Process p[n];

    for(i = 0; i < n; i++)
    {
        p[i].id = i+1;
        printf("Enter arrival time and burst time for process %d: ", i+1);
        scanf("%d %d", &p[i].AT, &p[i].BT);
    }

    sorted(p, n);
    FCFS(p, n);

    return 0;
}
