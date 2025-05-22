#include <stdio.h>

int main() {
    int n, frames;
    printf("Enter number of pages: ");
    scanf("%d", &n);

    int pages[n];
    printf("Enter the page sequence: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    int mem[frames], age[frames], faults = 0, hits = 0;

    for (int i = 0; i < frames; i++) {
        mem[i] = -1;
        age[i] = -1;
    }

    printf("\nLRU Page Replacement Process:\n");
    for (int i = 0; i < n; i++) {
        int page = pages[i], found = 0;

        for (int j = 0; j < frames; j++) {
            if (mem[j] == page) {
                hits++;
                age[j] = i;  // update last used time
                found = 1;
                break;
            }
        }

        if (!found) {
            // find empty frame or least recently used
            int index = -1, min_age = 1e9;
            for (int j = 0; j < frames; j++) {
                if (mem[j] == -1) {
                    index = j;
                    break;
                }
                if (age[j] < min_age) {
                    min_age = age[j];
                    index = j;
                }
            }
            mem[index] = page;
            age[index] = i;
            faults++;
            printf("Page %d caused a fault. Frames: ", page);
        } else {
            printf("Page %d hit. Frames: ", page);
        }

        for (int j = 0; j < frames; j++) {
            if (mem[j] == -1)
                printf("- ");
            else
                printf("%d ", mem[j]);
        }
        printf("\n");
    }

    printf("\nTotal LRU Page Faults: %d, Page Hits: %d\n", faults, hits);
    return 0;
}
