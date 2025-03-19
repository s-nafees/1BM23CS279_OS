#include <stdio.h>
#define MAX 100

// Sort processes based on Arrival Time
void sortProcesses(int processes[], int n, int at[], int bt[]) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (at[j] > at[j + 1]) {
                // Swap Arrival Time
                int temp_at = at[j];
                at[j] = at[j + 1];
                at[j + 1] = temp_at;

                // Swap Burst Time
                int temp_bt = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = temp_bt;

                // Swap Process IDs
                int temp_p = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp_p;
            }
        }
    }
}

// Round Robin Scheduling
void roundRobin(int n, int processes[], int at[], int bt[], int quant) {
    sortProcesses(processes, n, at, bt);
    int ct[n], tat[n], wt[n], rem_bt[n];
    int queue[MAX], front = 0, rear = 0;
    int time = 0, completed = 0, visited[n];

    for (int i = 0; i < n; i++) {
        rem_bt[i] = bt[i];
        visited[i] = 0;
    }

    // Add the first process to the queue
    queue[rear++] = 0;
    visited[0] = 1;

    while (completed < n) {
        // Get the process from the front of the queue
        int index = queue[front++];

        // If the remaining burst time is greater than the quantum, run the process for 'quant' time
        if (rem_bt[index] > quant) {
            time += quant;
            rem_bt[index] -= quant;
        } else {  // If remaining burst time is less than or equal to quantum, finish the process
            time += rem_bt[index];
            rem_bt[index] = 0;
            ct[index] = time;
            completed++;
        }

        // Add new processes to the queue based on arrival time
        for (int i = 0; i < n; i++) {
            if (at[i] <= time && rem_bt[i] > 0 && !visited[i]) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }

        // If the current process still has remaining burst time, add it back to the queue
        if (rem_bt[index] > 0) {
            queue[rear++] = index;
        }

        // If the queue is empty, add the next process that has not yet been executed
        if (front == rear) {
            for (int i = 0; i < n; i++) {
                if (rem_bt[i] > 0) {
                    queue[rear++] = i;
                    visited[i] = 1;
                    break;
                }
            }
        }
    }

    // Calculate TAT and WT for each process and print the results
    float total_tat = 0, total_wt = 0;
    printf("P#\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];  // Turnaround Time = Completion Time - Arrival Time
        wt[i] = tat[i] - bt[i];  // Waiting Time = Turnaround Time - Burst Time
        total_tat += tat[i];
        total_wt += wt[i];
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", processes[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    // Print average TAT and WT
    printf("Average TAT: %.2f\n", total_tat / n);
    printf("Average WT: %.2f\n", total_wt / n);
}

int main() {
    int n, quant;
    printf("ROUND ROBIN SCHEDULING\n");
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], processes[n];
    for (int i = 0; i < n; i++) {
        processes[i] = i + 1;  // Assigning process IDs
        printf("Enter AT and BT for process %d: ", processes[i]);
        scanf("%d %d", &at[i], &bt[i]);
    }

    printf("Enter time quantum: ");
    scanf("%d", &quant);

    // Sort processes based on arrival time


    // Call the round robin scheduling function
    roundRobin(n, processes, at, bt, quant);

    return 0;
}
==OUTPUT==
ROUND ROBIN SCHEDULING
Enter number of processes: 4
Enter AT and BT for process 1: 2 10
Enter AT and BT for process 2: 4 6
Enter AT and BT for process 3: 0 8
Enter AT and BT for process 4: 6 4
Enter time quantum: 4
P#      AT      BT      CT      TAT     WT
3       0       8       16      16      8
1       2       10      28      26      16
2       4       6       26      22      16
4       6       4       20      14      10
Average TAT: 19.50
Average WT: 12.50

Process returned 0 (0x0)   execution time : 14.058 s
Press any key to continue.

ROUND ROBIN SCHEDULING
Enter number of processes: 5
Enter AT and BT for process 1: 0 5
Enter AT and BT for process 2: 1 6
Enter AT and BT for process 3: 2 3
Enter AT and BT for process 4: 3
1
Enter AT and BT for process 5: 4 5
Enter time quantum: 4
P#      AT      BT      CT      TAT     WT
1       0       5       17      17      12
2       1       6       19      18      12
3       2       3       11      9       6
4       3       1       12      9       8
5       4       5       20      16      11
Average TAT: 13.80
Average WT: 9.80

Process returned 0 (0x0)   execution time : 74.140 s
Press any key to continue.

