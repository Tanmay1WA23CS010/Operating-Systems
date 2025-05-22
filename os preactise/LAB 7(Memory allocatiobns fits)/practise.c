#include <stdio.h>

typedef struct {
    int bno, bsize, isfree;
} Block;

typedef struct {
    int fno, fsize;
} File;

void printHeader() {
    printf("\n%-8s %-10s %-9s %-11s %-8s\n", "File No", "File Size", "Block No", "Block Size", "Fragment");
    printf("---------------------------------------------------------\n");
}

void firstFit(Block blocks[], File files[], int n, int f) {
    printf("\nFirst Fit Allocation:\n");
    printHeader();
    for (int i = 0; i < f; i++) {
        int allocated = 0;
        for (int j = 0; j < n; j++) {
            if (blocks[j].isfree && blocks[j].bsize >= files[i].fsize) {
                blocks[j].isfree = 0;
                int fragment = blocks[j].bsize - files[i].fsize;
                printf("%-8d %-10d %-9d %-11d %-8d\n", files[i].fno, files[i].fsize, blocks[j].bno, blocks[j].bsize, fragment);
                allocated = 1;
                break;
            }
        }
        if (!allocated) {
            printf("%-8d %-10d %-9s %-11s %-8s\n", files[i].fno, files[i].fsize, "N/A", "N/A", "N/A");
        }
    }
}

void bestFit(Block blocks[], File files[], int n, int f) {
    printf("\nBest Fit Allocation:\n");
    printHeader();
    for (int i = 0; i < f; i++) {
        int minFragment = 100000, index = -1;
        for (int j = 0; j < n; j++) {
            if (blocks[j].isfree && blocks[j].bsize >= files[i].fsize) {
                int fragment = blocks[j].bsize - files[i].fsize;
                if (fragment < minFragment) {
                    minFragment = fragment;
                    index = j;
                }
            }
        }
        if (index != -1) {
            blocks[index].isfree = 0;
            printf("%-8d %-10d %-9d %-11d %-8d\n", files[i].fno, files[i].fsize, blocks[index].bno, blocks[index].bsize, minFragment);
        } else {
            printf("%-8d %-10d %-9s %-11s %-8s\n", files[i].fno, files[i].fsize, "N/A", "N/A", "N/A");
        }
    }
}

void worstFit(Block blocks[], File files[], int n, int f) {
    printf("\nWorst Fit Allocation:\n");
    printHeader();
    for (int i = 0; i < f; i++) {
        int maxFragment = -1, index = -1;
        for (int j = 0; j < n; j++) {
            if (blocks[j].isfree && blocks[j].bsize >= files[i].fsize) {
                int fragment = blocks[j].bsize - files[i].fsize;
                if (fragment > maxFragment) {
                    maxFragment = fragment;
                    index = j;
                }
            }
        }
        if (index != -1) {
            blocks[index].isfree = 0;
            printf("%-8d %-10d %-9d %-11d %-8d\n", files[i].fno, files[i].fsize, blocks[index].bno, blocks[index].bsize, maxFragment);
        } else {
            printf("%-8d %-10d %-9s %-11s %-8s\n", files[i].fno, files[i].fsize, "N/A", "N/A", "N/A");
        }
    }
}

void resetBlocks(Block blocks[], int n) {
    for (int i = 0; i < n; i++) {
        blocks[i].isfree = 1;
    }
}

int main() {
    int n, f;

    printf("Enter number of blocks: ");
    scanf("%d", &n);

    Block blocks[n];
    for (int i = 0; i < n; i++) {
        printf("Enter size of Block %d: ", i);
        scanf("%d", &blocks[i].bsize);
        blocks[i].bno = i;
        blocks[i].isfree = 1;
    }

    printf("Enter number of files: ");
    scanf("%d", &f);

    File files[f];
    for (int i = 0; i < f; i++) {
        printf("Enter size of File %d: ", i);
        scanf("%d", &files[i].fsize);
        files[i].fno = i;
    }

    firstFit(blocks, files, n, f);
    resetBlocks(blocks, n);

    bestFit(blocks, files, n, f);
    resetBlocks(blocks, n);

    worstFit(blocks, files, n, f);

    return 0;
}
