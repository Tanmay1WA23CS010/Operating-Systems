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

    int mem[frames], last_used[frames];
    for (i = 0; i < frames; i++) {
        mem[i] = -1;
        last_used[i] = -1;
    }

    for (i = 0; i < n; i++) {
        int page = pages[i] - '0';
        int found = 0;

        for (j = 0; j < frames; j++) {
            if (mem[j] == page) {
                hits++;
                last_used[j] = i;
                found = 1;
                break;
            }
        }

        if (!found) {
            int lru = 0;
            for (j = 1; j < frames; j++) {
                if (last_used[j] < last_used[lru]) {
                    lru = j;
                }
            }
            mem[lru] = page;
            last_used[lru] = i;
            page_faults++;
        }
    }

    printf("LRU Page Faults: %d, Page Hits: %d\n", page_faults, hits);
    return 0;
}
