#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
	int pid;
	int arrival_time;
	int burst_time;
	int completion_time;
	int turnaround_time;
	int waiting_time;
} Process;

void calculateTimes(Process processes[], int n) {
	int current_time = 0;

	for (int i = 0; i < n; i++) {
    	if (current_time < processes[i].arrival_time) {
        	current_time = processes[i].arrival_time;
    	}

    	current_time += processes[i].burst_time + 2; // Add I/O wait time
    	processes[i].completion_time = current_time;
    	processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
    	processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
   	 
    	// Generate next CPU burst randomly for the next execution
    	processes[i].burst_time = rand() % 10 + 1;
	}
}

void displayGanttChart(Process processes[], int n) {
	int current_time = 0;
	printf("Gantt Chart:\n");

	for (int i = 0; i < n; i++) {
    	if (current_time < processes[i].arrival_time) {
        	current_time = processes[i].arrival_time;
    	}
    	printf("| P%d ", processes[i].pid);
    	current_time += processes[i].burst_time + 2; // Add I/O wait time
	}
	printf("|\n");

	current_time = 0;
	for (int i = 0; i < n; i++) {
    	current_time += processes[i].burst_time + 2; // Add I/O wait time
    	printf("%d ", current_time);
	}
	printf("\n");
}

int main() {
	int n;

	printf("Enter number of processes: ");
	scanf("%d", &n);

	Process processes[n];
	srand(time(0));

	for (int i = 0; i < n; i++) {
    	processes[i].pid = i + 1;
    	printf("Enter arrival time and first CPU burst for process %d: ", i + 1);
    	scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
	}

	calculateTimes(processes, n);

	float total_turnaround_time = 0, total_waiting_time = 0;

	for (int i = 0; i < n; i++) {
    	total_turnaround_time += processes[i].turnaround_time;
    	total_waiting_time += processes[i].waiting_time;

    	printf("Process P%d: Turnaround Time = %d, Waiting Time = %d\n",
           	processes[i].pid, processes[i].turnaround_time, processes[i].waiting_time);
	}

	printf("Average Turnaround Time: %.2f\n", total_turnaround_time / n);
	printf("Average Waiting Time: %.2f\n", total_waiting_time / n);

	displayGanttChart(processes, n);

	return 0;
}

