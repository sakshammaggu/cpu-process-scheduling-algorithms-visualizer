#ifndef ROUND_ROBIN_H
#define ROUND_ROBIN_H

#include <vector>
#include <utility>

#include "../process.h"

using namespace std;

class RoundRobinScheduler {
private:
    int timeQuantum;                    // Time slice allocated to each process in one round
    vector<Process> processes;          // List of processes to be scheduled
    vector<pair<int, int>> ganttChart;  // Stores process ID and the end time of each process in the Gantt chart
    int currentTime;                    // Tracks the current time during execution

public:
    RoundRobinScheduler(int timeQuantum);      // Constructor to initialize the scheduler with a time quantum
    void addProcess(const Process& process);   // Adds a process to the scheduling queue
    void execute();                            // Executes the Round Robin scheduling algorithm
    void displayResults() const;               // Displays the results: waiting time, turnaround time, etc.
    void displayGanttChart() const;            // Displays the Gantt chart for process scheduling
};

#endif