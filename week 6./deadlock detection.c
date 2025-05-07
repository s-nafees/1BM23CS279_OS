#include <stdio.h>
#include <stdbool.h>

#define P 10 // Number of processes (can be modified)
#define R 10 // Number of resources (can be modified)

int main() {
    int allocation[P][R], request[P][R], available[R];
    int finish[P] = {0}, safeSequence[P];
    int i, j, k;

    printf("Enter the number of processes: ");
    int n;
    scanf("%d", &n);

    printf("Enter the number of resources: ");
    int m;
    scanf("%d", &m);

    printf("Enter the allocation matrix:\n");
    for (i = 0; i < n; i++) {
        printf("Process %d: ", i);
        for (j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter the request matrix:\n");
    for (i = 0; i < n; i++) {
        printf("Process %d: ", i);
        for (j = 0; j < m; j++) {
            scanf("%d", &request[i][j]);
        }
    }

    printf("Enter the available resources: ");
    for (i = 0; i < m; i++) {
        scanf("%d", &available[i]);
    }

    int count = 0;
    while (count < n) {
        bool found = false;
        for (i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canAllocate = true;
                for (j = 0; j < m; j++) {
                    if (request[i][j] > available[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    for (k = 0; k < m; k++)
                        available[k] += allocation[i][k];
                    safeSequence[count++] = i;
                    finish[i] = 1;
                    found = true;
                }
            }
        }
        if (!found) {
            break;
        }
    }

    if (count == n) {
        printf("System is in safe state.\n");
        printf("Safe Sequence is: ");
        for (i = 0; i < n; i++) {
            printf("P%d ", safeSequence[i]);
        }
        printf("\n");
    } else {
        printf("System is NOT in a safe state. Deadlock may occur.\n");
    }

    return 0;
}
==OUTPUT==
Enter the number of processes: 5
Enter the number of resources: 3
Enter the allocation matrix:
Process 0: 0 1 0
Process 1: 2 0 0
Process 2: 3 0 3
Process 3: 2 1 1
Process 4: 0 0 2
Enter the request matrix:
Process 0: 0 0 0
Process 1: 2 0 2
Process 2: 0 0 0
Process 3: 1 0 0
Process 4: 0 0 2
Enter the available resources: 0 0 0
System is in safe state.
Safe Sequence is: P0 P2 P3 P4 P1

Process returned 0 (0x0)   execution time : 39.780 s
Press any key to continue.
