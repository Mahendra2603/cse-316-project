#include <stdio.h>

typedef struct {
    int burst_time;
    int priority;
    int arrival_time;
    int waiting_time;
    int turnaround_time;
} Process;

void calculateTimes(Process processes[], int n) {
    int remaining_time[n];
    for (int i = 0; i < n; i++) {
        remaining_time[i] = processes[i].burst_time;
    }

    int complete = 0;
    int current_time = 0;

    while (complete != n) {
        int highest_priority = -1;
        int selected_process = -1;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && remaining_time[i] > 0) {
                if (highest_priority == -1 || processes[i].priority < highest_priority) {
                    highest_priority = processes[i].priority;
                    selected_process = i;
                }
            }
        }

        if (selected_process == -1) {
            current_time++;
            continue;
        }

        remaining_time[selected_process]--;

        if (remaining_time[selected_process] == 0) {
            complete++;
            int finish_time = current_time + 1;
            processes[selected_process].turnaround_time = finish_time - processes[selected_process].arrival_time;
            processes[selected_process].waiting_time = processes[selected_process].turnaround_time - processes[selected_process].burst_time;
        }

        current_time++;
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    for (int i = 0; i < n; i++) {
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].priority = processes[i].burst_time; // Assign priority based on burst time
        processes[i].arrival_time = i; // Assuming processes arrive sequentially
    }

    calculateTimes(processes, n);

    // Calculate averages
    float avg_waiting_time = 0;
    float avg_turnaround_time = 0;

    for (int i = 0; i < n; i++) {
        avg_waiting_time += processes[i].waiting_time;
        avg_turnaround_time += processes[i].turnaround_time;
    }

    avg_waiting_time /= n;
    avg_turnaround_time /= n;

    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);

    return 0;
}

