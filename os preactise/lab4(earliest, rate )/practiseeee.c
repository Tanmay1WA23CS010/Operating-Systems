#include <stdio.h>
typedef struct
{
    int id;
    int period;
    int completiontime;
    int remaining /* data */
}Process;

void RateMonotonic(Process p[], int n, int lcm){
    for(int time =0; time<lcm ; time++){
        for (int i=0 ;i< n;i++){
            if(time %p[i].period==0){
                p[i].remaining = p[i].completiontime;
            }
        }
        int selected =-1;
        for(int i= 0; i<n ;i++){
            if(p[i].remaining>0){
                selected = i;
            }
        }
        if(selected != -1){
            p[selected]--;
            printf("jdblsk");
        }else{
            printf("IDLE");
        }
        
    }
}