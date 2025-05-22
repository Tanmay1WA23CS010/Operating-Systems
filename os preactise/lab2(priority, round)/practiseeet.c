#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
typedef struct {
    int pid;
    int AT, 
    int BT;
    int ct;
    int wt;
    int tat;
    int remaining;
    int pri;

}Process;

void PriorityPreemptive(Process p[], int n){
    int time =0; int totaltat, int totalwt;
    

    for(int i =0 ;i< n; i++){
        p[i].remaining= p[i].BT;
        p[i].rt = -1;
    }
    
    int completed =0;
    while(completed<n){
        int ind = -1;
        int maxpri = INT_MAX;
        for(int i= 0; i< n; i++){
            if(p[i].remaining>0 && p[i].AT< = time){
                if(p[i].pri < maxpri || p[i].AT == p[ind].AT && p[i].pri<p[i].pri){
                    ind = i;
                    maxpri = p[i].pri;
                }
            }
            if(ind != -1){
                if(p[ind].rt == -1){
                    p[ind].rt = time + p[ind]q.AT;
                    }
                p[ind].remaining--;
                if(p[ind].remaining == 0){
                    p[ind].ct = time + p[ind].AT;
                    p[ind].tat = p[ind].ct - p[ind].AT;
                    p[ind].wt = p[ind].tat - p[ind].BT;
                    completed++;}
            }
        }
    }


}