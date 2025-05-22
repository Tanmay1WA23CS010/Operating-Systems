#include <stdio.h>

typedef struct {
    int no;
    int bsize;
    int isfree;
    int fallocated;
    int frag;
} Block;

typedef struct {
    int no;
    int fsize;
} File;

// First Fit allocation
void FirstFit(Block blocks[], File files[], int b, int f) {
    // Initialize blocks as free
    for (int i = 0; i < b; i++) {
        blocks[i].isfree = 0;
        blocks[i].fallocated = -1;
        blocks[i].frag = 0;
    }

    for (int i = 0; i < f; i++) {
        int allocatedIndex = -1;

        // Find first block that fits
        for (int j = 0; j < b; j++) {
            if (blocks[j].isfree == 0 && blocks[j].bsize >= files[i].fsize) {
                allocatedIndex = j;
                break;  // stop on first fit found
            }
        }

        if (allocatedIndex != -1) {
            blocks[allocatedIndex].isfree = 1;
            blocks[allocatedIndex].fallocated = files[i].no;
            blocks[allocatedIndex].frag = blocks[allocatedIndex].bsize - files[i].fsize;
        } else {
            printf("No space available for file %d\n", files[i].no);
        }
    }
}

// Best Fit allocation
void BestFit(Block blocks[], File files[], int b, int f) {
    // Initialize blocks as free
    for (int i = 0; i < b; i++) {
        blocks[i].isfree = 0;
        blocks[i].fallocated = -1;
        blocks[i].frag = 0;
    }

    for (int i = 0; i < f; i++) {
        int minFrag = 1e9; // large number
        int allocatedIndex = -1;

        // Find block with minimum leftover (fragment) that fits
        for (int j = 0; j < b; j++) {
            if (blocks[j].isfree == 0 && blocks[j].bsize >= files[i].fsize) {
                int frag = blocks[j].bsize - files[i].fsize;
                if (frag < minFrag) {
                    minFrag = frag;
                    allocatedIndex = j;
                }
            }
        }

        if (allocatedIndex != -1) {
            blocks[allocatedIndex].isfree = 1;
            blocks[allocatedIndex].fallocated = files[i].no;
            blocks[allocatedIndex].frag = minFrag;
        } else {
            printf("No space available for file %d\n", files[i].no);
        }
    }
}

// Worst Fit allocation
void WorstFit(Block blocks[], File files[], int b, int f) {
    // Initialize blocks as free
    for (int i = 0; i < b; i++) {
        blocks[i].isfree = 0;
        blocks[i].fallocated = -1;
        blocks[i].frag = 0;
    }

    for (int i = 0; i < f; i++) {
        int maxFrag = -1;
        int allocatedIndex = -1;

        // Find block with maximum leftover (fragment) that fits
        for (int j = 0; j < b; j++) {
            if (blocks[j].isfree == 0 && blocks[j].bsize >= files[i].fsize) {
                int frag = blocks[j].bsize - files[i].fsize;
                if (frag > maxFrag) {
                    maxFrag = frag;
                    allocatedIndex = j;
                }
            }
        }

        if (allocatedIndex != -1) {
            blocks[allocatedIndex].isfree = 1;
            blocks[allocatedIndex].fallocated = files[i].no;
            blocks[allocatedIndex].frag = maxFrag;
        } else {
            printf("No space available for file %d\n", files[i].no);
        }
    }
}

// Utility to print allocation results
void printAllocation(Block blocks[], int b) {
    printf("\nBlock No\tBlock Size\tAllocated File\tFragment\n");
    for (int i = 0; i < b; i++) {
        printf("%d\t\t%d\t\t", blocks[i].no, blocks[i].bsize);
        if (blocks[i].isfree)
            printf("%d\t\t%d\n", blocks[i].fallocated, blocks[i].frag);
        else
            printf("Not Allocated\t-\n");
    }
}

// Deallocate file by file number
void Deallocate(Block blocks[], int b, int fileNo) {
    int found = 0;
    for (int i = 0; i < b; i++) {
        if (blocks[i].isfree && blocks[i].fallocated == fileNo) {
            blocks[i].isfree = 0;
            blocks[i].fallocated = -1;
            blocks[i].frag = 0;
            found = 1;
            printf("File %d deallocated from block %d\n", fileNo, blocks[i].no);
            break;  // Assuming one file per block, stop after found
        }
    }
    if (!found) {
        printf("File %d not found in any block.\n", fileNo);
    }
}

int main() {
    int b, f;
    printf("Enter number of blocks: ");
    scanf("%d", &b);
    Block blocks[b];
    for (int i = 0; i < b; i++) {
        printf("Enter block %d size: ", i);
        scanf("%d", &blocks[i].bsize);
        blocks[i].no = i;
        blocks[i].isfree = 0;
        blocks[i].fallocated = -1;
        blocks[i].frag = 0;
    }

    printf("Enter number of files: ");
    scanf("%d", &f);
    File files[f];
    for (int i = 0; i < f; i++) {
        printf("Enter file %d size: ", i);
        scanf("%d", &files[i].fsize);
        files[i].no = i;
    }

    // First Fit
    printf("\nFirst Fit Allocation:\n");
    FirstFit(blocks, files, b, f);
    printAllocation(blocks, b);

    // Allow deallocation in First Fit
    char choice;
    printf("\nDo you want to deallocate any file in First Fit? (y/n): ");
    scanf(" %c", &choice);
    while (choice == 'y' || choice == 'Y') {
        int fileNo;
        printf("Enter file number to deallocate: ");
        scanf("%d", &fileNo);
        Deallocate(blocks, b, fileNo);
        printAllocation(blocks, b);
        printf("Deallocate another? (y/n): ");
        scanf(" %c", &choice);
    }

    // Reset blocks for Best Fit
    for (int i = 0; i < b; i++) {
        blocks[i].isfree = 0;
        blocks[i].fallocated = -1;
        blocks[i].frag = 0;
    }

    printf("\nBest Fit Allocation:\n");
    BestFit(blocks, files, b, f);
    printAllocation(blocks, b);

    // Allow deallocation in Best Fit
    printf("\nDo you want to deallocate any file in Best Fit? (y/n): ");
    scanf(" %c", &choice);
    while (choice == 'y' || choice == 'Y') {
        int fileNo;
        printf("Enter file number to deallocate: ");
        scanf("%d", &fileNo);
        Deallocate(blocks, b, fileNo);
        printAllocation(blocks, b);
        printf("Deallocate another? (y/n): ");
        scanf(" %c", &choice);
    }

    // Reset blocks for Worst Fit
    for (int i = 0; i < b; i++) {
        blocks[i].isfree = 0;
        blocks[i].fallocated = -1;
        blocks[i].frag = 0;
    }

    printf("\nWorst Fit Allocation:\n");
    WorstFit(blocks, files, b, f);
    printAllocation(blocks, b);

    // Allow deallocation in Worst Fit
    printf("\nDo you want to deallocate any file in Worst Fit? (y/n): ");
    scanf(" %c", &choice);
    while (choice == 'y' || choice == 'Y') {
        int fileNo;
        printf("Enter file number to deallocate: ");
        scanf("%d", &fileNo);
        Deallocate(blocks, b, fileNo);
        printAllocation(blocks, b);
        printf("Deallocate another? (y/n): ");
        scanf(" %c", &choice);
    }

    return 0;
}
