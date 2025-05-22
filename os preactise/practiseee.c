#include <stdio.h>

typedef struct {
    int no;
    int bsize;
    int isfree;
    int fallocated;
    int frag;
}Block;

#include <stdio.h>

typedef struct {
    int no;
    int fsize;

    int ballocated;
    
}File;



FirstFit(Block blocks[],File files[], int b, int f){
    for(int i=0; i< b; i++){
        blocks[i].isfree =0;
    }
    for(int i= 0; i<f; i++){
        int index =- 1;
        for(int j =0; j< b;j++){
            int fragment;
            if(blocks[j].isfree == 0 && blocks[i].bsize >= files[i].fsize){
                 fragment = blocks[j].bsize - files[i].fsize;
                index = j;
            }
            blocks[j].frag = fragment;
            blocks[j].fallocated = i;
            inde = 1;
            blocks[j].isfree = 1;

            
        }
        if(allocated == -1){
            printf("No space available for file %d\n",files[i].no);
        }
        
    }
}

BestFit(Block blocks[],File files[], int b, int f){
    for(int i= 0; i< f; i++){
        int min =0;
        int index = -1;
        int fragment;
        for(int j = 0; j<b; j++){
            if(blocks[j].isfree == 0 && blocks[j].bsize> files[i].fsize){
                fragment = blocks[j].bsize = files[i].fsize;
                if(fragment<min){
                    min = fragment;
                    index = j;
                    break;
                }
            }
            if(index != -1){
                blocks[index].frag = fragment;
                blocks[index].fallocated = i;
                blocks[index].isfree = 1;
                break;
            }else{
                printf("No space available for file %d\n",files[i].no);
            }
        }
    }
    printf("the allocations are::");
    printf("%d")
}