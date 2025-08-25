#include <stdio.h>
#include <limits.h>  // for INT_MAX

void preEmptive(int n, int arrivalTime[], int burstTime[]) {
    int remainingTime[n], waitingTime[n], turnAroundTime[n], completionTime[n];
    int completed = 0, currentTime = 0;
    double totalWaitingTime = 0, totalTurnaroundTime = 0;

    // Initialize
    for (int i = 0; i < n; i++) {
        remainingTime[i] = burstTime[i];
        waitingTime[i] = 0;
        turnAroundTime[i] = 0;
        completionTime[i] = 0;
    }

    while (completed < n) {
        int idx = -1, minBurst = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (arrivalTime[i] <= currentTime && remainingTime[i] > 0 && remainingTime[i] < minBurst) {
                minBurst = remainingTime[i];
                idx = i;
            }
        }
        if (idx != -1) {
            remainingTime[idx]--;
            if (remainingTime[idx] == 0) {
                completed++;
                completionTime[idx] = currentTime + 1;
                turnAroundTime[idx] = completionTime[idx] - arrivalTime[idx];
                waitingTime[idx] = turnAroundTime[idx] - burstTime[idx];
            }
        }
        currentTime++;
    }

    printf("\nPreemptive Shortest Job First Scheduling:\n");
    printf("Process\tArrival Time\tBurst Time\tCompletion Time\tTurn Around Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", i + 1, arrivalTime[i], burstTime[i],
               completionTime[i], turnAroundTime[i], waitingTime[i]);
        totalWaitingTime += waitingTime[i];
        totalTurnaroundTime += turnAroundTime[i];
    }

    printf("Average Waiting Time: %.2f\n", totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", totalTurnaroundTime / n);
}

void nonPreEmptive(int n, int arrivalTime[], int burstTime[]) {
    int waitingTime[n], turnAroundTime[n], completionTime[n], isCompleted[n];
    int completed = 0, currentTime = 0;
    double totalWaitingTime = 0, totalTurnaroundTime = 0;

    for (int i = 0; i < n; i++) {
        waitingTime[i] = 0;
        turnAroundTime[i] = 0;
        completionTime[i] = 0;
        isCompleted[i] = 0;
    }

    while (completed < n) {
        int idx = -1, minBurst = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (arrivalTime[i] <= currentTime && !isCompleted[i] && burstTime[i] < minBurst) {
                minBurst = burstTime[i];
                idx = i;
            }
        }
        if (idx != -1) {
            currentTime += burstTime[idx];
            completionTime[idx] = currentTime;
            turnAroundTime[idx] = completionTime[idx] - arrivalTime[idx];
            waitingTime[idx] = turnAroundTime[idx] - burstTime[idx];
            isCompleted[idx] = 1;
            completed++;
        } else {
            currentTime++;
        }
    }

    printf("\nNon-Preemptive Shortest Job First Scheduling:\n");
    printf("Process\tArrival Time\tBurst Time\tCompletion Time\tTurn Around Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", i + 1, arrivalTime[i], burstTime[i],
               completionTime[i], turnAroundTime[i], waitingTime[i]);
        totalWaitingTime += waitingTime[i];
        totalTurnaroundTime += turnAroundTime[i];
    }

    printf("Average Waiting Time: %.2f\n", totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", totalTurnaroundTime / n);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int arrivalTime[n], burstTime[n];

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time of process %d: ", i + 1);
        scanf("%d", &arrivalTime[i]);
        printf("Enter burst time of process %d: ", i + 1);
        scanf("%d", &burstTime[i]);
    }

    preEmptive(n, arrivalTime, burstTime);
    nonPreEmptive(n, arrivalTime, burstTime);

    return 0;
}
