#include <stdio.h>
// Function to find the waiting time for all processes
void findWaitingTime(int processes[], int n, int burst_time[], int waiting_time[]) {
    waiting_time[0] = 0; // First process has no waiting time
    // Calculate waiting time for each process
    for (int i = 1; i < n; i++) {
        waiting_time[i] = burst_time[i - 1] + waiting_time[i - 1];
    }
}
// Function to find the turnaround time for all processes
void findTurnAroundTime(int processes[], int n, int burst_time[], int waiting_time[], int turnaround_time[]) {
    // Calculate turnaround time for each process
    for (int i = 0; i < n; i++) {
        turnaround_time[i] = burst_time[i] + waiting_time[i];
    }
}
// Function to calculate average waiting and turnaround times
void findAverageTime(int processes[], int n, int burst_time[]) {
    int waiting_time[n], turnaround_time[n];
    int total_waiting_time = 0, total_turnaround_time = 0;
    // Function to find waiting time for all processes
    findWaitingTime(processes, n, burst_time, waiting_time);
    // Function to find turnaround time for all processes
    findTurnAroundTime(processes, n, burst_time, waiting_time, turnaround_time);
    // Display processes along with burst time, waiting time, and turnaround time
    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];
        printf("P%d\t\t%d\t\t%d\t\t%d\n", processes[i], burst_time[i], waiting_time[i], turnaround_time[i]);
    }
    printf("\nAverage Waiting Time: %.2f", (float)total_waiting_time / n);
    printf("\nAverage Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
}
// Main function
int main() {
    int n;
    // Input the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    int processes[n], burst_time[n];
    // Input burst time for each process
    for (int i = 0; i < n; i++) {
        processes[i] = i + 1; // Process IDs are 1, 2, 3, etc.
        printf("Enter burst time for process P%d: ", i + 1);
        scanf("%d", &burst_time[i]);
    }
    // Call function to find average waiting and turnaround times
    findAverageTime(processes, n, burst_time);
    return 0;
}
