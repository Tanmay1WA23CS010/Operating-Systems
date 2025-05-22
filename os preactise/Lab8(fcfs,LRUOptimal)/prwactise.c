#include <stdio.h>

#include <stdio.h>

int main() {
    int n, frames, i, j, k, page_faults = 0, hits = 0;

    printf("Enter the size of the pages:\n");
    scanf("%d", &n);

    char pages[n + 1];
    printf("Enter the page strings:\n");
    scanf("%s", pages);

    printf("Enter the no of page frames:\n");
    scanf("%d", &frames);

    int mem[frames], front = 0;
    for (i = 0; i < frames; i++) {
        mem[i] = -1;
    }

    for (i = 0; i<n ;i++){
        int page = pages[i] -'0';
        int found =0;
        for (j = 0; j<frames; j++){
            if(mem[j] == page){
                found = 1;
                hits++;
                break;
            }
        }
        if(found == 0){
            page_faults++;
            mem[front] = page;
            front = (front+1)%frames;
            }
    }

// lru

#include <stdio.h>

#include <stdio.h>

int main() {
    int n, frames, i, j, k, page_faults = 0, hits = 0;

    printf("Enter the size of the pages:\n");
    scanf("%d", &n);

    char pages[n + 1];
    printf("Enter the page strings:\n");
    scanf("%s", pages);

    printf("Enter the no of page frames:\n");
    scanf("%d", &frames);

    int mem[frames],lastused[frames], front = 0;
    for (i = 0; i < frames; i++) {
        mem[i] = -1;
        lastused[i] = -1;
    }

    for (i = 0; i<n ;i++){
        int page = pages[i] -'0';
        int found =0;
        for (j = 0; j<frames; j++){
            if(mem[j] == page){
                lastused[j] = i;
                found = 1;
                hits++;
                break;
            }
        }
        if(found == 0){
            page_faults++;
            mem[front] = page;
            front = (front+1)%frames;
            }
    }
