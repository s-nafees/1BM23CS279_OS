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

    // Calculate Need Matrix
    int need[MAX_PROCESSES][MAX_RESOURCES];
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    bool finish[MAX_PROCESSES] = {false};
    int safeSequence[MAX_PROCESSES];
    int count = 0;

    // Banker's Algorithm for Deadlock Avoidance
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
            // Call Deadlock Detection Function here
            detectDeadlock(alloc, need, n, m, avail);
            return 0;
        }
    }

    // Print Safe Sequence if No Deadlock
    printf("\nSystem is in a safe state.\nSafe sequence is: ");
    for (i = 0; i < n; i++)
        printf("P%d ", safeSequence[i]);
    printf("\n");

    return 0;
}

// Function to detect deadlock by checking for cycles in the Resource Allocation Graph (RAG)
void detectDeadlock(int alloc[MAX_PROCESSES][MAX_RESOURCES], int need[MAX_PROCESSES][MAX_RESOURCES], 
                    int n, int m, int avail[MAX_RESOURCES]) {
    bool visited[MAX_PROCESSES] = {false};
    bool recStack[MAX_PROCESSES] = {false};
    
    // Check each process for a cycle (deadlock)
    for (int i = 0; i < n; i++) {
        if (visited[i] == false) {
            if (isCyclic(i, alloc, need, n, m, visited, recStack)) {
                printf("Deadlock detected: Cycle found involving process P%d\n", i);
                return;
            }
        }
    }
    printf("No deadlock detected in the system.\n");
}

// Function to detect cycles (deadlocks) using DFS
bool isCyclic(int node, int alloc[MAX_PROCESSES][MAX_RESOURCES], int need[MAX_PROCESSES][MAX_RESOURCES], 
              int n, int m, bool visited[MAX_PROCESSES], bool recStack[MAX_PROCESSES]) {
    // Mark the current node as visited and add to the recursion stack
    visited[node] = true;
    recStack[node] = true;

    // Check for all processes that are requesting resources
    for (int i = 0; i < n; i++) {
        if (need[node][i] > 0) {  // process 'node' is requesting resource 'i'
            // If the resource is not available, it's blocked, check the cycle
            if (!visited[i] && isCyclic(i, alloc, need, n, m, visited, recStack)) {
                return true;
            } else if (recStack[i]) {
                // Cycle found
                return true;
            }
        }
    }

    // Remove the node from the recursion stack
    recStack[node] = false;
    return false;
}
