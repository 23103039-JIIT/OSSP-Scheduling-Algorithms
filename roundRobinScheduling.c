#include <stdio.h>
#include <stdbool.h>

#define MAX 100   // maximum number of processes

// Simple queue implementation
typedef struct {
    int data[MAX];
    int front, rear;
} Queue;

void initQueue(Queue *q) {
    q->front = 0;
    q->rear = 0;
}

bool isEmpty(Queue *q) {
    return q->front == q->rear;
}

void enqueue(Queue *q, int val) {
    q->data[q->rear++] = val;
}

int dequeue(Queue *q) {
    if (isEmpty(q)) return -1;
    return q->data[q->front++];
}

void roundRobin(int n, int t, int arrivalTime[], int burstTime[]) {
    int remainingTime[MAX], waitingTime[MAX], turnaroundTime[MAX];
    bool inQueue[MAX];
    Queue q;
    initQueue(&q);

    for (int i = 0; i < n; i++) {
        remainingTime[i] = burstTime[i];
        waitingTime[i] = 0;
        turnaroundTime[i] = 0;
        inQueue[i] = false;
    }

    int currentTime = 0, completed = 0;

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (arrivalTime[i] <= currentTime && !inQueue[i] && remainingTime[i] > 0) {
                enqueue(&q, i);
                inQueue[i] = true;
            }
        }

        if (!isEmpty(&q)) {
            int idx = dequeue(&q);

            if (remainingTime[idx] > t) {
                currentTime += t;
                remainingTime[idx] -= t;
            } else {
                currentTime += remainingTime[idx];
                waitingTime[idx] = currentTime - arrivalTime[idx] - burstTime[idx];
                turnaroundTime[idx] = waitingTime[idx] + burstTime[idx];
                remainingTime[idx] = 0;
                completed++;
            }

            for (int i = 0; i < n; i++) {
                if (arrivalTime[i] <= currentTime && !inQueue[i] && remainingTime[i] > 0) {
                    enqueue(&q, i);
                    inQueue[i] = true;
                }
            }

            if (remainingTime[idx] > 0) {
                enqueue(&q, idx);
            } else {
                inQueue[idx] = false;
            }
        } else {
            currentTime++;
        }
    }

    double totalWaitingTime = 0, totalTurnaroundTime = 0;
    for (int i = 0; i < n; i++) {
        totalWaitingTime += waitingTime[i];
        totalTurnaroundTime += turnaroundTime[i];
    }

    printf("\nPreemptive Round Robin Scheduling:\n");
    printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, arrivalTime[i], burstTime[i], waitingTime[i], turnaroundTime[i]);
    }

    printf("Average Waiting Time: %.2f\n", totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", totalTurnaroundTime / n);
}

int main() {
    int n, t;
    int arrivalTime[MAX], burstTime[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter time quantum: ");
    scanf("%d", &t);

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time of process %d: ", i + 1);
        scanf("%d", &arrivalTime[i]);
        printf("Enter burst time of process %d: ", i + 1);
        scanf("%d", &burstTime[i]);
    }

    roundRobin(n, t, arrivalTime, burstTime);
    return 0;
}
