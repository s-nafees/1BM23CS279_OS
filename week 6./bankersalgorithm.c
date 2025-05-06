BANKERS ALGORITHM
#include <stdio.h>
#include <stdbool.h>
#define MAX_PROCESSES 10
#define MAX_RESOURCES 10
int main() {
    int n, m, i, j, k;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);
    int alloc[MAX_PROCESSES][MAX_RESOURCES];  // Allocation matrix
    int max[MAX_PROCESSES][MAX_RESOURCES];    // Maximum matrix
    int avail[MAX_RESOURCES];                 // Available resources
    printf("Enter Allocation Matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);
    printf("Enter Maximum Matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &max[i][j]);
    printf("Enter Available Resources:\n");
    for (i = 0; i < m; i++)
        scanf("%d", &avail[i]);
    int need[MAX_PROCESSES][MAX_RESOURCES];
    // Calculate need matrix
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];
    bool finish[MAX_PROCESSES] = {false};
    int safeSequence[MAX_PROCESSES];
    int count = 0;
    // Banker's Algorithm
    while (count < n) {
        bool found = false;
        for (i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canExecute = true;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]) {
                        canExecute = false;
                        break;
                    }
                }
                if (canExecute) {
                    for (k = 0; k < m; k++)
                        avail[k] += alloc[i][k];
                    safeSequence[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            printf("\nSystem is NOT in a safe state (Deadlock possible)\n");
            return 0;
        }
    }
    printf("\nSystem is in a safe state.\nSafe sequence is: ");
    for (i = 0; i < n; i++)
        printf("P%d ", safeSequence[i]);
    printf("\n");
    return 0;
}
