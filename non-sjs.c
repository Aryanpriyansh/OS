#include <stdio.h>

// Function to sort processes based on arrival time and burst time
void sortProcesses(int n, int processes[], int arrival_time[], int burst_time[]) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arrival_time[i] > arrival_time[j] || 
               (arrival_time[i] == arrival_time[j] && burst_time[i] > burst_time[j])) {
                // Swap arrival time
                int temp = arrival_time[i];
                arrival_time[i] = arrival_time[j];
                arrival_time[j] = temp;

                // Swap burst time
                temp = burst_time[i];
                burst_time[i] = burst_time[j];
                burst_time[j] = temp;

                // Swap process ID
                temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
}

// Function to calculate waiting time for each process
void calculateWaitingTime(int n, int arrival_time[], int burst_time[], int waiting_time[]) {
    int completion_time[n];
    int total_time = 0;

    // First process always starts execution at its arrival time
    total_time = arrival_time[0] + burst_time[0];
    waiting_time[0] = 0;

    // Calculate completion time and waiting time for each process
    for (int i = 1; i < n; i++) {
        // Update total time if CPU is idle (process arrives after CPU is free)
        if (total_time < arrival_time[i])
            total_time = arrival_time[i];

        // Calculate waiting time for each process
        waiting_time[i] = total_time - arrival_time[i];

        // Update total time after the process completes
        total_time += burst_time[i];
    }
}

// Function to calculate turnaround time for each process
void calculateTurnaroundTime(int n, int burst_time[], int waiting_time[], int turnaround_time[]) {
    for (int i = 0; i < n; i++) {
        turnaround_time[i] = burst_time[i] + waiting_time[i];
    }
}

// Function to calculate and display the results
void calculateAverageTimes(int n, int processes[], int arrival_time[], int burst_time[]) {
    int waiting_time[n], turnaround_time[n];
    int total_waiting_time = 0, total_turnaround_time = 0;

    // Sort processes based on arrival time and burst time
    sortProcesses(n, processes, arrival_time, burst_time);

    // Calculate waiting time for all processes
    calculateWaitingTime(n, arrival_time, burst_time, waiting_time);

    // Calculate turnaround time for all processes
    calculateTurnaroundTime(n, burst_time, waiting_time, turnaround_time);

    // Display process details and calculate total waiting and turnaround times
    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i], arrival_time[i], burst_time[i], waiting_time[i], turnaround_time[i]);
    }

    // Display average waiting time and turnaround time
    printf("\nAverage Waiting Time: %.2f", (float)total_waiting_time / n);
    printf("\nAverage Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
}

int main() {
    int n;

    // Input the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int processes[n], arrival_time[n], burst_time[n];

    // Input arrival time and burst time for each process
    for (int i = 0; i < n; i++) {
        processes[i] = i + 1;  // Process IDs (P1, P2, P3, ...)
        printf("Enter arrival time for process P%d: ", i + 1);
        scanf("%d", &arrival_time[i]);
        printf("Enter burst time for process P%d: ", i + 1);
        scanf("%d", &burst_time[i]);
    }

    // Call function to calculate and display average waiting and turnaround times
    calculateAverageTimes(n, processes, arrival_time, burst_time);

    return 0;
}
