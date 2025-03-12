FCFS :
#include <stdio.h>

// Function to sort processes according to Arrival Time
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

                // Swap Process IDs (optional, but keeps track of process order)
                int temp_p = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp_p;
            }
        }
    }
}

// Function to calculate Completion Time (CT)
void CT(int processes[], int n, int at[], int bt[], int ct[]) {
    ct[0] = at[0] + bt[0];  // Completion time for the first process
    for (int i = 1; i < n; i++) {
        if (ct[i - 1] < at[i]) {
            ct[i] = at[i] + bt[i];  // If the CPU is idle until the next process arrives
        } else {
            ct[i] = ct[i - 1] + bt[i];  // Otherwise, start as soon as the previous process finishes
        }
    }
}

// Function to calculate Turnaround Time (TAT) and Waiting Time (WT)
void TAT_WT(int processes[], int n, int at[], int bt[], int ct[], int wt[], int tat[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];  // Turnaround Time = Completion Time - Arrival Time
        wt[i] = tat[i] - bt[i];  // Waiting Time = Turnaround Time - Burst Time
    }
}

// Function to calculate and display the average times
void Average_Time(int processes[], int n, int at[], int bt[]) {
    int wt[n], tat[n], ct[n];
    int total_wt = 0, total_tat = 0, total_ct = 0;

    CT(processes, n, at, bt, ct);  // Calculate Completion Time
    TAT_WT(processes, n, at, bt, ct, wt, tat);  // Calculate Waiting Time and Turnaround Time

    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\tCompletion Time\n");

    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        total_ct += ct[i];
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i], at[i], bt[i], wt[i], tat[i], ct[i]);
    }

    printf("\nAverage waiting time: %.2f", (float)total_wt / n);
    printf("\nAverage turnaround time: %.2f", (float)total_tat / n);
    printf("\nAverage completion time: %.2f", (float)total_ct / n);
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int processes[n];
    int burst_time[n];
    int arrival_time[n];

    // Taking arrival and burst times as input
    printf("Enter the arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        processes[i] = i + 1;  // Assign process numbers as 1, 2, 3, ...
        printf("Arrival Time for Process %d: ", processes[i]);
        scanf("%d", &arrival_time[i]);
        printf("Burst Time for Process %d: ", processes[i]);
        scanf("%d", &burst_time[i]);
    }

    // Sorting processes based on arrival time
    sortProcesses(processes, n, arrival_time, burst_time);

    // Calculate and display average times
    Average_Time(processes, n, arrival_time, burst_time);

    return 0;
}
==OUTPUT==
Enter the number of processes: 3
Enter the arrival time and burst time for each process:
Arrival Time for Process 1: 1
Burst Time for Process 1: 3
Arrival Time for Process 2: 0
Burst Time for Process 2: 5
Arrival Time for Process 3: 2
Burst Time for Process 3: 8

Process Arrival Time    Burst Time      Waiting Time    Turnaround Time Completion Time
2       0               5               0               5               5
1       1               3               4               7               8
3       2               8               6               14              16

Average waiting time: 3.33
Average turnaround time: 8.67
Average completion time: 9.67
Process returned 0 (0x0)   execution time : 6.422 s
Press any key to continue.



