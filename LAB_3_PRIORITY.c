#include <stdio.h>

#define MAX 100

void priorityPreemptive(int n, int at[], int bt[], int pr[]) {
    int ct[n], tat[n], wt[n], rem_bt[n], is_completed[n];
    int time = 0, completed = 0, min_priority, index;

    for (int i = 0; i < n; i++) {
        rem_bt[i] = bt[i];
        is_completed[i] = 0;
    }

    while (completed < n) {
        min_priority = 9999;
        index = -1;

        for (int i = 0; i < n; i++) {
            if (at[i] <= time && is_completed[i] == 0 && pr[i] < min_priority && rem_bt[i] > 0) {
                min_priority = pr[i];
                index = i;
            }
        }

        if (index == -1) {
            time++;
        } else {
            rem_bt[index]--;
            time++;

            if (rem_bt[index] == 0) {
                ct[index] = time;
                is_completed[index] = 1;
                completed++;
            }
        }
    }

    float total_tat = 0, total_wt = 0;
    printf("\nP#\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        total_tat += tat[i];
        total_wt += wt[i];
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], pr[i], ct[i], tat[i], wt[i]);
    }

    printf("Average TAT: %.2f\n", total_tat / n);
    printf("Average WT: %.2f\n", total_wt / n);
}

void priorityNonPreemptive(int n, int at[], int bt[], int pr[]) {
    int ct[n], tat[n], wt[n], is_completed[n], rem_bt[n];
    int time = 0, completed = 0;

    for (int i = 0; i < n; i++) {
        is_completed[i] = 0;
        rem_bt[i] = bt[i];
    }

    while (completed < n) {
        int min_priority = 9999, index = -1;

        for (int i = 0; i < n; i++) {
            if (at[i] <= time && is_completed[i] == 0 && pr[i] < min_priority) {
                min_priority = pr[i];
                index = i;
            }
        }

        if (index == -1) {
            time++;
        } else {
            time += bt[index];
            ct[index] = time;
            is_completed[index] = 1;
            completed++;
        }
    }

    float total_tat = 0, total_wt = 0;
    printf("\nP#\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        total_tat += tat[i];
        total_wt += wt[i];
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], pr[i], ct[i], tat[i], wt[i]);
    }

    printf("Average TAT: %.2f\n", total_tat / n);
    printf("Average WT: %.2f\n", total_wt / n);
}

int main() {
    int n, choice;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], pr[n];
    for (int i = 0; i < n; i++) {
        printf("Enter AT, BT, and Priority P%d: ", i + 1);
        scanf("%d %d %d", &at[i], &bt[i], &pr[i]);
    }

    printf("\nChoose Scheduling Algorithm:\n");
    printf("1. Preemptive Priority Scheduling\n");
    printf("2. Non-Preemptive Priority Scheduling\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        priorityPreemptive(n, at, bt, pr);
    } else if (choice == 2) {
        priorityNonPreemptive(n, at, bt, pr);
    } else {
        printf("Invalid choice!\n");
    }

    return 0;
}
==output=
Enter number of processes: 5
Enter AT, BT, and Priority P1: 2 6 3
Enter AT, BT, and Priority P2: 5 2 1
Enter AT, BT, and Priority P3: 1 8 4
Enter AT, BT, and Priority P4: 0 3 5
Enter AT, BT, and Priority P5: 4 4 2

Choose Scheduling Algorithm:
1. Preemptive Priority Scheduling
2. Non-Preemptive Priority Scheduling
Enter choice: 2

P#      AT      BT      PR      CT      TAT     WT
1       2       6       3       9       7       1
2       5       2       1       11      6       4
3       1       8       4       23      22      14
4       0       3       5       3       3       0
5       4       4       2       15      11      7
Average TAT: 9.80
Average WT: 5.20

Process returned 0 (0x0)   execution time : 34.835 s
Press any key to continue.
Enter number of processes: 5
Enter AT, BT, and Priority P1: 2 6 3
Enter AT, BT, and Priority P2: 5 2 1
Enter AT, BT, and Priority P3: 1 8 4
Enter AT, BT, and Priority P4: 0 3 5
Enter AT, BT, and Priority P5: 4 4 2

Choose Scheduling Algorithm:
1. Preemptive Priority Scheduling
2. Non-Preemptive Priority Scheduling
Enter choice: 1

P#      AT      BT      PR      CT      TAT     WT
1       2       6       3       14      12      6
2       5       2       1       7       2       0
3       1       8       4       21      20      12
4       0       3       5       23      23      20
5       4       4       2       10      6       2
Average TAT: 12.60
Average WT: 8.00

Process returned 0 (0x0)   execution time : 19.680 s
Press any key to continue.
