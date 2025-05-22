
////////

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

    int mem[frames], faults = 0, hits = 0;

    for (int i = 0; i < frames; i++)
        mem[i] = -1;

    printf("\nOptimal Page Replacement Process:\n");
    for (int i = 0; i < n; i++) {
        int page = pages[i], found = 0;

        for (int j = 0; j < frames; j++) {
            if (mem[j] == page) {
                hits++;
                found = 1;
                break;
            }
        }

        if (!found) {
            int index = -1, farthest = i;
            for (int j = 0; j < frames; j++) {
                if (mem[j] == -1) {
                    index = j;
                    break;
                }
                int k;
                for (k = i + 1; k < n; k++) {
                    if (mem[j] == pages[k])
                        break;
                }
                if (k > farthest) {
                    farthest = k;
                    index = j;
                }
            }
            mem[index] = page;
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

    printf("\nTotal Optimal Page Faults: %d, Page Hits: %d\n", faults, hits);
    return 0;
}
