#include <stdio.h>

// Function to find the waiting time of all processes
void calculateWaitingTime(int n, int processes[], int burst_time[], int arrival_time[], int waiting_time[]) {
    int complete = 0, current_time = 0, shortest = 0, finish_time;
    int remaining_time[n];
    int min_time = 10000;
    int check = 0;

    // Initialize remaining time array with burst times
    for (int i = 0; i < n; i++) {
        remaining_time[i] = burst_time[i];
    }

    while (complete != n) {
        // Find process with shortest remaining time at the current time
        for (int i = 0; i < n; i++) {
            if ((arrival_time[i] <= current_time) && (remaining_time[i] < min_time) && remaining_time[i] > 0) {
                min_time = remaining_time[i];
                shortest = i;
                check = 1;
            }
        }

        // If no process is ready to execute, move forward in time
        if (check == 0) {
            current_time++;
            continue;
        }

        // Decrease the remaining time of the shortest process
        remaining_time[shortest]--;

        // Update the minimum time left
        min_time = remaining_time[shortest];
        if (min_time == 0)
            min_time = 10000;

        // If a process gets completely executed
        if (remaining_time[shortest] == 0) {
            complete++;
            check = 0;

            // Find finish time of the current process
            finish_time = current_time + 1;

            // Calculate waiting time
            waiting_time[shortest] = finish_time - burst_time[shortest] - arrival_time[shortest];

            // If waiting time is negative, set it to 0
            if (waiting_time[shortest] < 0)
                waiting_time[shortest] = 0;
        }
        current_time++;
    }
}

// Function to calculate turnaround time for each process
void calculateTurnaroundTime(int n, int burst_time[], int waiting_time[], int turnaround_time[]) {
    for (int i = 0; i < n; i++) {
        turnaround_time[i] = burst_time[i] + waiting_time[i];
    }
}

// Function to calculate and display average waiting and turnaround times
void calculateAverageTimes(int n, int processes[], int burst_time[], int arrival_time[]) {
    int waiting_time[n], turnaround_time[n];
    int total_waiting_time = 0, total_turnaround_time = 0;

    // Calculate waiting time for all processes
    calculateWaitingTime(n, processes, burst_time, arrival_time, waiting_time);

    // Calculate turnaround time for all processes
    calculateTurnaroundTime(n, burst_time, waiting_time, turnaround_time);

    // Display results
    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i], arrival_time[i], burst_time[i], waiting_time[i], turnaround_time[i]);
    }

    // Calculate and print average waiting time and average turnaround time
    printf("\nAverage Waiting Time: %.2f", (float)total_waiting_time / n);
    printf("\nAverage Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
}

int main() {
    int n;

    // Input the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int processes[n], burst_time[n], arrival_time[n];

    // Input arrival time and burst time for each process
    for (int i = 0; i < n; i++) {
        processes[i] = i + 1;  // Process IDs are P1, P2, P3, ...
        printf("Enter arrival time for process P%d: ", i + 1);
        scanf("%d", &arrival_time[i]);
        printf("Enter burst time for process P%d: ", i + 1);
        scanf("%d", &burst_time[i]);
    }

    // Call function to calculate and display average waiting and turnaround times
    calculateAverageTimes(n, processes, burst_time, arrival_time);

    return 0;
}
