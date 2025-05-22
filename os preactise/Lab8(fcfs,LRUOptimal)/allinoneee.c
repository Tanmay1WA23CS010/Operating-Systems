#include <stdio.h>

void FIFO(char pages[], int n, int frames) {
    int mem[frames], front = 0, page_faults = 0, hit = 0;
    for (int i = 0; i < frames; i++) mem[i] = -1;

    for (int i = 0; i < n; i++) {
        int page = pages[i] - '0';
        int found = 0;

        for (int j = 0; j < frames; j++) {
            if (mem[j] == page) {
                hit++;
                found = 1;
                break;
            }
        }

        if (!found) {
            mem[front] = page;
            front = (front + 1) % frames;
            page_faults++;
        }
    }

    printf("FIFO:\nPage Faults: %d\nHits: %d\n", page_faults, hit);
}

void LRU(char pages[], int n, int frames) {
    int mem[frames], lastused[frames], page_faults = 0, hit = 0;

    for (int i = 0; i < frames; i++) {
        mem[i] = -1;
        lastused[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int page = pages[i] - '0';
        int found = 0;

        for (int j = 0; j < frames; j++) {
            if (mem[j] == page) {
                hit++;
                lastused[j] = i;
                found = 1;
                break;
            }
        }

        if (!found) {
            page_faults++;
            int index = -1;

            for (int j = 0; j < frames; j++) {
                if (mem[j] == -1) {
                    index = j;
                    break;
                }
            }

            if (index == -1) {
                int lru = i;
                for (int j = 0; j < frames; j++) {
                    if (lastused[j] < lru) {
                        lru = lastused[j];
                        index = j;
                    }
                }
            }

            mem[index] = page;
            lastused[index] = i;
        }
    }

    printf("LRU:\nPage Faults: %d\nHits: %d\n", page_faults, hit);
}

void OPTIMAL(char pages[], int n, int frames) {
    int mem[frames], page_faults = 0, hit = 0;

    for (int i = 0; i < frames; i++) mem[i] = -1;

    for (int i = 0; i < n; i++) {
        int page = pages[i] - '0';
        int found = 0;

        for (int j = 0; j < frames; j++) {
            if (mem[j] == page) {
                hit++;
                found = 1;
                break;
            }
        }

        if (!found) {
            page_faults++;
            int index = -1;

            for (int j = 0; j < frames; j++) {
                if (mem[j] == -1) {
                    index = j;
                    break;
                }
            }

            if (index == -1) {
                int farthest = -1, pos = -1;
                for (int j = 0; j < frames; j++) {
                    int next_use = -1;
                    for (int k = i + 1; k < n; k++) {
                        if (pages[k] - '0' == mem[j]) {
                            next_use = k;
                            break;
                        }
                    }
                    if (next_use == -1) {
                        pos = j;
                        break;
                    }
                    if (next_use > farthest) {
                        farthest = next_use;
                        pos = j;
                    }
                }
                index = pos;
            }

            mem[index] = page;
        }
    }

    printf("OPTIMAL:\nPage Faults: %d\nHits: %d\n", page_faults, hit);
}

int main() {
    char pages[] = {'1', '2', '3', '4', '1', '2', '5', '1', '2', '3', '4', '5'};
    int n = sizeof(pages) / sizeof(pages[0]);
    int frames = 3;

    FIFO(pages, n, frames);
    LRU(pages, n, frames);
    OPTIMAL(pages, n, frames);

    return 0;
}
