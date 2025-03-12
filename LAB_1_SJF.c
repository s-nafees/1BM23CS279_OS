#include <stdio.h>
#include <stdlib.h>

void sortProcesses(int n, int at[], int bt[], int processes[]) {
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

// Non-preemptive SJF scheduling
void nonPreemptiveSJF(int n, int at[], int bt[], int processes[], int ct[], int wt[], int tat[]) {
    int completed = 0;
    int time = 0;
    int min_bt = 100000;  // A large value for comparison
    int process_index = -1;

    // Initialize
    int remaining_bt[n];
    for (int i = 0; i < n; i++) {
        remaining_bt[i] = bt[i];
        ct[i] = 0;  // Initialize completion times to 0
    }

    // Sort processes by burst time (for non-preemptive)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (at[j] <= time && at[j + 1] <= time && bt[j] > bt[j + 1]) {
                // Swap Burst Time
                int temp_bt = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = temp_bt;

                // Swap Arrival Time
                int temp_at = at[j];
                at[j] = at[j + 1];
                at[j + 1] = temp_at;

                // Swap Process IDs
                int temp_p = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp_p;
            }
        }
    }

    // Execute the processes
    while (completed < n) {
        min_bt = 100000;
        process_index = -1;

        // Find the process with the minimum burst time
        for (int i = 0; i < n; i++) {
            if (at[i] <= time && remaining_bt[i] > 0 && remaining_bt[i] < min_bt) {
                min_bt = remaining_bt[i];
                process_index = i;
            }
        }

        if (process_index == -1) {
            time++;  // Idle CPU
        } else {
            // Execute the selected process for its entire burst time
            time += bt[process_index];

            // Set the completion time
            ct[process_index] = time;
            tat[process_index] = ct[process_index] - at[process_index];  // TAT = CT - AT
            wt[process_index] = tat[process_index] - bt[process_index];  // WT = TAT - BT

            completed++;
        }
    }
}

// Preemptive SJF (SRTF) scheduling
void preemptiveSJF(int n, int at[], int bt[], int processes[], int ct[], int wt[], int tat[]) {
    int completed = 0;
    int time = 0;
    int min_remaining_time = 100000;
    int process_index = -1;

    int remaining_bt[n];
    for (int i = 0; i < n; i++) {
        remaining_bt[i] = bt[i];
        ct[i] = 0;  // Initialize completion times to 0
    }

    while (completed < n) {
        min_remaining_time = 100000;
        process_index = -1;

        // Find the process with the shortest remaining burst time that has arrived
        for (int i = 0; i < n; i++) {
            if (at[i] <= time && remaining_bt[i] > 0 && remaining_bt[i] < min_remaining_time) {
                min_remaining_time = remaining_bt[i];
                process_index = i;
            }
        }

        if (process_index == -1) {
            time++;  // Idle CPU
        } else {
            // Execute the selected process for 1 unit of time
            remaining_bt[process_index]--;

            // If the process is completed, update its completion time
            if (remaining_bt[process_index] == 0) {
                completed++;
                ct[process_index] = time + 1;
                tat[process_index] = ct[process_index] - at[process_index];  // TAT = CT - AT
                wt[process_index] = tat[process_index] - bt[process_index];  // WT = TAT - BT
            }
            time++;  // Increment time
        }
    }
}

// Calculate and display the average times
void Average_Time(int n, int at[], int bt[], int processes[], void (*schedulingAlgo)(int, int[], int[], int[], int[], int[], int[])) {
    int wt[n], tat[n], ct[n];
    int total_wt = 0, total_tat = 0, total_ct = 0;

    schedulingAlgo(n, at, bt, processes, ct, wt, tat);  // Run the selected scheduling algorithm

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
    int arrival_time[n];
    int burst_time[n];

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
    sortProcesses(n, arrival_time, burst_time, processes);

    int choice;
    printf("\nChoose Scheduling Algorithm:\n");
    printf("1. Non-preemptive SJF\n");
    printf("2. Preemptive SJF (SRTF)\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        // Non-preemptive SJF
        Average_Time(n, arrival_time, burst_time, processes, nonPreemptiveSJF);
    } else if (choice == 2) {
        // Preemptive SJF
        Average_Time(n, arrival_time, burst_time, processes, preemptiveSJF);
    } else {
        printf("Invalid choice.\n");
    }

    return 0;
}
Enter the number of processes: 3
Enter the arrival time and burst time for each process:
Arrival Time for Process 1: 1
Burst Time for Process 1: 3
Arrival Time for Process 2: 0
Burst Time for Process 2: 5
Arrival Time for Process 3: 2
Burst Time for Process 3: 8

Choose Scheduling Algorithm:
1. Non-preemptive SJF
2. Preemptive SJF (SRTF)
Enter your choice: 1

Process Arrival Time    Burst Time      Waiting Time    Turnaround Time Completion Time
2       0               5               0               5               5
1       1               3               7               10              11
3       2               8               -850809058              3               0

Average waiting time: -283603008.00
Average turnaround time: 6.00
Average completion time: 5.33
Process returned 0 (0x0)   execution time : 19.907 s
Press any key to continue.

Enter the number of processes: 3
Enter the arrival time and burst time for each process:
Arrival Time for Process 1: 1
Burst Time for Process 1: 3
Arrival Time for Process 2: 0
Burst Time for Process 2: 5
Arrival Time for Process 3: 2
Burst Time for Process 3: 8

Choose Scheduling Algorithm:
1. Non-preemptive SJF
2. Preemptive SJF (SRTF)
Enter your choice: 2

Process Arrival Time    Burst Time      Waiting Time    Turnaround Time Completion Time
2       0               5               3               8               8
1       1               3               0               3               4
3       2               8               6               14              16

Average waiting time: 3.00
Average turnaround time: 8.33
Average completion time: 9.33
Process returned 0 (0x0)   execution time : 7.720 s
Press any key to continue.
