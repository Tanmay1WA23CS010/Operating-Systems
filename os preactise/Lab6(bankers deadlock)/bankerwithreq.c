#include <stdio.h>
#include <stdbool.h>

// Function to check if system is in safe state
bool isSafe(int n, int m, int alloc[n][m], int need[n][m], int avail[m], int safeSeq[n]) {
    bool finish[n];
    for (int i = 0; i < n; i++) finish[i] = false;

    int work[m];
    for (int i = 0; i < m; i++) work[i] = avail[i];

    int count = 0;

    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canAlloc = true;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        canAlloc = false;
                        break;
                    }
                }
                if (canAlloc) {
                    for (int j = 0; j < m; j++) {
                        work[j] += alloc[i][j];
                    }
                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found) return false;
    }

    return true;
}

// Function to handle a resource request
void handleRequest(int n, int m, int alloc[n][m], int max[n][m], int avail[m], int need[n][m]) {
    int pid;
    printf("Enter process ID (0 to %d): ", n - 1);
    scanf("%d", &pid);

    int req[m];
    printf("Enter request vector of size %d: ", m);
    for (int i = 0; i < m; i++) {
        scanf("%d", &req[i]);

        if (req[i] > need[pid][i]) {
            printf("Request exceeds maximum need. Denied.\n");
            return;
        }

        if (req[i] > avail[i]) {
            printf("Resources not available. Denied.\n");
            return;
        }
    }

    // Try allocating temporarily
    for (int i = 0; i < m; i++) {
        avail[i] -= req[i];
        alloc[pid][i] += req[i];
        need[pid][i] -= req[i];
    }

    int safeSeq[n];
    if (isSafe(n, m, alloc, need, avail, safeSeq)) {
        printf("Request can be granted. New safe sequence: ");
        for (int i = 0; i < n; i++) {
            printf("P%d", safeSeq[i]);
            if (i != n - 1) printf(" -> ");
        }
        printf("\n");
    } else {
        // Rollback
        for (int i = 0; i < m; i++) {
            avail[i] += req[i];
            alloc[pid][i] -= req[i];
            need[pid][i] += req[i];
        }
        printf("Request leads to unsafe state. Denied.\n");
    }
}

int main() {
    int n, m;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);

    int alloc[n][m], max[n][m], avail[m], need[n][m];

    // Input allocation matrix
    printf("Enter allocation matrix (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++) {
        printf("Allocation for process %d: ", i);
        for (int j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    // Input max matrix
    printf("Enter max matrix (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++) {
        printf("Max for process %d: ", i);
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Input available resources
    printf("Enter available resources (%d values): ", m);
    for (int i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
    }

    // Calculate need matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    // Check safe state
    int safeSeq[n];
    if (isSafe(n, m, alloc, need, avail, safeSeq)) {
        printf("System is in a safe state.\nSafe sequence is: ");
        for (int i = 0; i < n; i++) {
            printf("P%d", safeSeq[i]);
            if (i != n - 1) printf(" -> ");
        }
        printf("\n");
    } else {
        printf("System is not in a safe state.\n");
        return 1;
    }

    // Ask for resource request
    char choice;
    printf("Do you want to make a resource request? (y/n): ");
    scanf(" %c", &choice);
    if (choice == 'y' || choice == 'Y') {
        handleRequest(n, m, alloc, max, avail, need);
    }

    return 0;
}
