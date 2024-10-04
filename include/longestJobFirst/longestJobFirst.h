#ifndef LJF_H
#define LJF_H

#include <vector>
#include <utility>

#include "../process.h"

using namespace std;

class LJFScheduler {
private:
    vector<Process> processes;                    // List of processes to schedule
    vector<pair<int, int>> ganttChart;            // Gantt chart (Process ID, end time)
    int currentTime;                              // Track the current time of the scheduler

public:
    LJFScheduler();                               // Constructor to initialize scheduler
    void addProcess(const Process& process);      // Add a process to the scheduling list
    void execute();                               // Execute the LJF scheduling algorithm
    void displayResults() const;                  // Display the results (waiting time, turnaround time)
    void displayGanttChart() const;               // Display the Gantt chart
};

#endif