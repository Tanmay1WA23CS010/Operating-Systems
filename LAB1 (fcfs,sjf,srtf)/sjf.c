
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

void SJFNonPreemptive(Process p[], int n)
{
    int TotalTAT = 0, TotalWT = 0, time = 0, completed = 0, i;
    int remainingBT[n];
    for(i = 0; i < n; i++)
    {
        remainingBT[i] = p[i].BT;
    }

    while(completed < n)
    {
        int minBTIndex = -1;
        int minBT = 9999;
        for(i = 0; i < n; i++)
        {
            if(p[i].AT <= time && remainingBT[i] > 0 && remainingBT[i] < minBT)
            {
                minBT = remainingBT[i];
                minBTIndex = i;
            }
        }

        if(minBTIndex != -1)
        {
            time += p[minBTIndex].BT;
            p[minBTIndex].CT = time;
            p[minBTIndex].TAT = p[minBTIndex].CT - p[minBTIndex].AT;
            p[minBTIndex].WT = p[minBTIndex].TAT - p[minBTIndex].BT;
            TotalTAT += p[minBTIndex].TAT;
            TotalWT += p[minBTIndex].WT;
            remainingBT[minBTIndex] = 0;
            completed++;
        }
        else
        {
            time++;
        }
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
    SJFNonPreemptive(p, n);

    return 0;
}
