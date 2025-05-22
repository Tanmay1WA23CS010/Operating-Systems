#include <stdio.h>
#include <string.h>

int main() {
    int frames;
    char pages_str[50];

    printf("Enter the page sequence (digits only, e.g. 12345): ");
    scanf("%s", pages_str);

    int n = strlen(pages_str);
    int pages[n];
    for (int i = 0; i < n; i++) {
        pages[i] = pages_str[i] - '0';
    }

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    int mem[frames], front = 0, faults = 0, hits = 0;

    for (int i = 0; i < frames; i++)
        mem[i] = -1;

    printf("\nFIFO Page Replacement Process:\n");
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
            mem[front] = page;
            front = (front + 1) % frames;
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

    printf("\nTotal FIFO Page Faults: %d, Page Hits: %d\n", faults, hits);
    return 0;
}
