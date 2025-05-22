#include <stdio.h>
//page replacement algo 
void FIFO(char pages[], int n, int frames){
    
    int page_faults = 0;
    int hit =0;
    int mem[frames];
    int front = 0;
    int rear = 0;
    for(int i =0; i< frames; i++){
        mem[i] = -1;
    }
    for(int i =0; i< n;i++){
        int page = pages[i]-'0';
        int found = 0;
        for(int j = 0; j<frames; j++){
            if(mem[j] == page){
                hit++;
                found = 1;
                break;
            }
        }
        if(found == 0){
            page_faults++;
            mem[front] = pages[i];
            front = (front +1) % frames;

        }


    }
}

void LRU(char pages[], int n ,int frames){

    int page_faults = 0;
    int hit =0;
    int mem[frames], lastused[frames];
   
    for(int i =0; i< frames; i++){
        mem[i] = -1;
    }

    for(int i=0; i< n; i++){
        int page = pages[i]-'0';
 
        int found = 0;
        for(int j = 0; j< frames ;j++){
            if(mem[j] == pages[i]-'0'){
                hit++;
                lastused[j] =i;
                found = 1;
        }
        if(found == 0){
            page_faults++;
            int index =-1; int lru = 999;
            for(int k=0; k< frames; k++){
                if(mem[j] == -1){
                    index =j;
                    break;
                }
                if(lastused[k]< lru){
                    lru = lastused[k];
                    index = j;
                }
            }
            mem[index] = page;
            lastused[index] = i;
        }
    }
}
}

void OPTIMAL(char pages[], int n ,int frames){

    int page_faults = 0;
    int hit =0;
    int mem[frames];

    for(int i =0; i< frames; i++){
        mem[i] = -1;
    }

    for(int i=0; i< n; i++){
        int page = pages[i]-'0';
     
        int found = 0;
        for(int j = 0; j< frames ;j++){
            if(mem[j] == pages[i]-'0'){
                hit++;
                found = 1;
        }
        if(found == 0){
            page_faults++;
            int index =-1; int farthest = -1;
            for(int k=0; k< frames; k++){
                if(mem[j] == -1){
                    index =j;
                    break;
                }
                for(int i= 0; i< n;i++){
                    if(mem[k] == page){
                        if(i>farthest){
                            farthest = i;
                            index = k;
                        }
                    }
                }
            }
            mem[index] = page;
            
        }
    }
}
}
