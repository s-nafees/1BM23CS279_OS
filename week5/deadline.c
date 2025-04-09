DEADLINE FIRST
#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 10
#define MAX_TIME 50  // Maximum simulation time

typedef struct {
    int pid;
    int burst;
    int deadline;
    int period;
    int remaining_time;
    int next_arrival;
} Process;

void earliest_deadline_first(Process p[], int n) {
    int time = 0, executed;
    printf("\nEarliest Deadline Scheduling:\n");
    printf("PID\tBurst\tDeadline\tPeriod\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t\t%d\n", p[i].pid, p[i].burst, p[i].deadline, p[i].period);

    while (time < MAX_TIME) {
        executed = -1;

        for (int i = 0; i < n; i++) {
            if (p[i].next_arrival <= time && p[i].remaining_time > 0) {
                if (executed == -1 || p[i].deadline < p[executed].deadline)
                    executed = i;
            }
        }

        if (executed != -1) {
            printf("%dms : Task %d is running.\n", time, p[executed].pid);
            p[executed].remaining_time--;
            if (p[executed].remaining_time == 0) {
                p[executed].next_arrival += p[executed].period;
                p[executed].remaining_time = p[executed].burst;
            }
        }
        time++;
    }
}

int main() {
    int n;
    Process processes[MAX_PROCESSES];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the CPU burst times:\n");
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        scanf("%d", &processes[i].burst);
        processes[i].remaining_time = processes[i].burst;
    }

    printf("Enter the time periods:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &processes[i].period);
        processes[i].next_arrival = 0;
    }

    printf("Enter the deadlines:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &processes[i].deadline);
    }

    earliest_deadline_first(processes, n);

    return 0;
}
==OUTPUT==
Enter the number of processes: 3
Enter the CPU burst times:
2 3 4
Enter the time periods:
1 2 3
Enter the deadlines:
1 2 3

Earliest Deadline Scheduling:
PID     Burst   Deadline        Period
1       2       1               1
2       3       2               2
3       4       3               3
0ms : Task 1 is running.
1ms : Task 1 is running.
2ms : Task 1 is running.
3ms : Task 1 is running.
4ms : Task 1 is running.
5ms : Task 1 is running.
6ms : Task 1 is running.
7ms : Task 1 is running.
8ms : Task 1 is running.
9ms : Task 1 is running.
10ms : Task 1 is running.
11ms : Task 1 is running.
12ms : Task 1 is running.
13ms : Task 1 is running.
14ms : Task 1 is running.
15ms : Task 1 is running.
16ms : Task 1 is running.
17ms : Task 1 is running.
18ms : Task 1 is running.
19ms : Task 1 is running.
20ms : Task 1 is running.
21ms : Task 1 is running.
22ms : Task 1 is running.
23ms : Task 1 is running.
24ms : Task 1 is running.
25ms : Task 1 is running.
26ms : Task 1 is running.
27ms : Task 1 is running.
28ms : Task 1 is running.
29ms : Task 1 is running.
30ms : Task 1 is running.
31ms : Task 1 is running.
32ms : Task 1 is running.
33ms : Task 1 is running.
34ms : Task 1 is running.
35ms : Task 1 is running.
36ms : Task 1 is running.
37ms : Task 1 is running.
38ms : Task 1 is running.
39ms : Task 1 is running.
40ms : Task 1 is running.
41ms : Task 1 is running.
42ms : Task 1 is running.
43ms : Task 1 is running.
44ms : Task 1 is running.
45ms : Task 1 is running.
46ms : Task 1 is running.
47ms : Task 1 is running.
48ms : Task 1 is running.
49ms : Task 1 is running.
