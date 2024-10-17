#ifndef SJF_H
#define SJF_H

#include <vector>
#include <utility>

#include "../process.h"

using namespace std;

class SJFScheduler {
private:
    vector<Process> processes;          // List of processes
    vector<pair<int, int>> ganttChart;  // Store process ID and end time
    int currentTime;                    // Current time in CPU

public:
    SJFScheduler();                             // Constructor to initialize SJF scheduler
    void addProcess(const Process& process);    // Add process to the list
    void execute();                             // Execute the scheduling algorithm
    void displayResults() const;                // Display results (waiting/turnaround time)
    void displayGanttChart() const;             // Display the Gantt chart
};

#endif