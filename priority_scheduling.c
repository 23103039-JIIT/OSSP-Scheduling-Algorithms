#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

void nonPreEmptive(int n, int arrivalTime[], int burstTime[], int priority[]) {
    int completionTime[n], waitingTime[n], turnAroundTime[n];
    bool isCompleted[n];
    for (int i = 0; i < n; i++) isCompleted[i] = false;

    int currentTime = 0, completed = 0;

    while (completed < n) {
        int idx = -1;
        int highestPriority = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (arrivalTime[i] <= currentTime && !isCompleted[i]) {
                if (priority[i] < highestPriority) {
                    highestPriority = priority[i];
                    idx = i;
                }
                if (priority[i] == highestPriority) {
                    if (arrivalTime[i] < arrivalTime[idx]) {
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1) {
            currentTime += burstTime[idx];
            completionTime[idx] = currentTime;
            turnAroundTime[idx] = completionTime[idx] - arrivalTime[idx];
            waitingTime[idx] = turnAroundTime[idx] - burstTime[idx];
            isCompleted[idx] = true;
            completed++;
        } else {
            currentTime++;
        }
    }

    printf("\nNon-Preemptive Priority Scheduling:\n");
    printf("Process\tArrival Time\tBurst Time\tPriority\tCompletion Time\tTurn Around Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", i + 1, arrivalTime[i], burstTime[i], priority[i], completionTime[i], turnAroundTime[i], waitingTime[i]);
    }
}

void preEmptive(int n, int arrivalTime[], int burstTime[], int priority[]) {
    int remainingTime[n];
    int completionTime[n], waitingTime[n], turnAroundTime[n];
    for (int i = 0; i < n; i++) remainingTime[i] = burstTime[i];

    int currentTime = 0, completed = 0;

    while (completed < n) {
        int idx = -1;
        int highestPriority = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (arrivalTime[i] <= currentTime && remainingTime[i] > 0) {
                if (priority[i] < highestPriority) {
                    highestPriority = priority[i];
                    idx = i;
                }
                if (priority[i] == highestPriority) {
                    if (arrivalTime[i] < arrivalTime[idx]) {
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1) {
            remainingTime[idx]--;
            currentTime++;

            if (remainingTime[idx] == 0) {
                completionTime[idx] = currentTime;
                turnAroundTime[idx] = completionTime[idx] - arrivalTime[idx];
                waitingTime[idx] = turnAroundTime[idx] - burstTime[idx];
                completed++;
            }
        } else {
            currentTime++;
        }
    }

    printf("\nPreemptive Priority Scheduling:\n");
    printf("Process\tArrival Time\tBurst Time\tPriority\tCompletion Time\tTurn Around Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", i + 1, arrivalTime[i], burstTime[i], priority[i], completionTime[i], turnAroundTime[i], waitingTime[i]);
    }
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int arrivalTime[n], burstTime[n], priority[n];

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time of process %d: ", i + 1);
        scanf("%d", &arrivalTime[i]);
        printf("Enter burst time of process %d: ", i + 1);
        scanf("%d", &burstTime[i]);
        printf("Enter priority of process %d: ", i + 1);
        scanf("%d", &priority[i]);
    }

    preEmptive(n, arrivalTime, burstTime, priority);
    nonPreEmptive(n, arrivalTime, burstTime, priority);

    return 0;
}
